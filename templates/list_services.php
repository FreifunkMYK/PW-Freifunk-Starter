<?php

if($input->urlSegment2) throw new Wire404Exception();

if($input->urlSegment1){
  switch($input->urlSegment1){
    case 'list':
      $services = $pages->find('template=service, sort=-subtitle');
      $table = '';

      foreach($services as $service){
        $status = ($service->online == 1 ? "alert success" : "alert danger");
        $table .="<tr class='$status'>
                  <td>$service->subtitle</td>
                  <td>$service->static_ip</td>
                  <td><a href='{$pages->get('/profile/')->httpUrl}{$service->operator->name}'>{$service->operator->name}</a></td>
                </tr>";
      }

      $page->table = $table;
      $content = renderPage();
      break;
    case 'ips':
        $useMain = false;
        $services = $pages->find("template=service");
        $service_serial = array();

        foreach($services as $service){
              if(!validateMac($service->title)) continue;
              $service_serial[] = array('mac' => strtolower(str_replace(":", "", $service->title)),
                                'staticip' => strtoupper($service->static_ip));
        }

        echo serialize($service_serial);
      break;
    case 'add':
      if(!wire('user')->isLoggedin()){
        $content = "<article><h2>Gesicherte Seite</h2>Bitte Anmelden oder Registrieren.</article>";
        $session->redirectUrl = $page->path."add/";
      } elseif(!$input->post->submit) {
        $content = renderPage('ip_registration');
      } else {
        //  Register Service
        $user = wire('user')->name;
        $parent = $pages->get($page->id);
        $operator = wire('user')->id;
        if($pages->get("template=services, title={$input->post->mac}") instanceof Nullpage){
          // Creat IP
          do {
            $ip = long2ip(rand(ip2long("{$pages->get('template=site-setting')->start_ip}"), ip2long("{$pages->get('template=site-setting')->end_ip}")));
          } while(!$pages->get("template=services, static_ip=$ip") instanceof NullPage);

          // Add new if not exist
          $mac = strtoupper($input->post->mac);
          $s = createPage('service', $parent, normalizeMac($mac));
          $s->subtitle = $input->post->title;
          $s->operator = $operator;
          $s->static_ip = $ip;
          $s->save();
        } else {
          // Update if exit
          $operator = wire('user')->id;
          $s = $pages->get("title={$input->post->mac}");
          $s->operator = $operator;
          $s->key = $input->post->key;
          $s->of(false);
          $s->save();
          $s->of(true);
        }

      	$content = "<h2>Node Hinzugefügt:</h2>
                    <p>
                    Titel: {$s->subtitle}<br>
                    MAC : {$s->title}<br>
                    IP : {$s->static_ip}<br>
                    Betreiber: {$users->get($s->operator)->name}
                    </p>";
        $session->remove('key');
        $session->remove('mac');
      }
      break;
    default:
      throw new Wire404Exception();
  }

} else {
  $userid = wire('user')->id;
  $services = $pages->find("operator=$userid, template=service, sort=-subtitle");
  $table = '';

  foreach($services as $service){

    $status = ($service->online == 1 ? "alert success" : "alert danger");
    $online = ($service->online == 1 ? "online" : "offline");
    $table .="<tr class='$status'>
              <td>$service->subtitle</td>
              <td>$service->static_ip</td>
              <td>{$service->operator->name}</td>
            </tr>";
  }

  $page->table = $table;
  $content = renderPage();
}

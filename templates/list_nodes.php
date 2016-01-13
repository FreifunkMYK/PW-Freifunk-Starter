<?php

if($input->urlSegment2) throw new Wire404Exception();

if($input->urlSegment1){
  switch($input->urlSegment1){
    case 'list':
      $nodes = $pages->find('template=node, sort=-subtitle');
      $table = '';

      foreach($nodes as $node){

        $status = ($node->online == 1 ? "alert success" : "alert danger");
        $table .="<tr class='$status'>
                  <td>$node->subtitle</td>
                  <td>$node->title</td>
                  <td>$node->latitude</td>
                  <td>$node->longitude</td>
                  <td>$node->online</td>
                  <td>{$node->parent->title}</td>
                </tr>";
      }

      $page->table = $table;
      $content = renderPage();
      break;
    case 'map':
      break;
    case 'add':
      if(!wire('user')->isLoggedin()){
        $content = "Pleas Login or Registrat";
        $session->redirectUrl = $page->path."add/";
        if(isset($input->get->mac)) $session->mac = $input->get->mac;
        if(isset($input->get->key)) $session->key = $input->get->key;
      } elseif(!$input->post->submit) {
        if(isset($input->get->mac)) $session->mac = $input->get->mac;
        if(isset($input->get->key)) $session->key = $input->get->key;
        $content = renderPage('node_registration');
      } else {
        //  Register Node
        $user = wire('user')->name;
        $parent = $pages->get("template=node_operator, title|name=$user");
        if($parent instanceof Nullpage) $parent = createPage('node_operator', 'node', $user);
        if($pages->get("title={$input->post->mac}") instanceof Nullpage){
          // Add new if not exist
          $n = createPage('node', $parent, $input->post->mac);
          $n->key = $input->post->key;
          $n->save();
        } else {
          // Update if exit
          $n = $pages->get("title={$input->post->mac}");
          $n->parent = $parent;
          $n->createdUser = wire('user')->id;
          $n->key = $input->post->key;
          $n->of(false);
          $n->save();
          $n->of(true);
        }

      	$content = "<h2>Node Hinzugefügt:</h2>
                    <p>
                    Titel: {$n->title}<br>
                    Key : {$n->key}<br>
                    Benutzer: {$n->parent->title}
                    </p>";
        $session->remove('key');
        $session->remove('mac');
      }
      break;
    default:
      throw new Wire404Exception();
  }

} else {
  $user = wire('user')->name;
  $parent = $pages->get("template=node_operator, title|name=$user");
  $nodes = $pages->find("parent=$parent, template=node, sort=-subtitle");
  $table = '';

  foreach($nodes as $node){

    $status = ($node->online == 1 ? "alert success" : "alert danger");
    $online = ($node->online == 1 ? "online" : "offline");
    $table .="<tr class='$status'>
              <td>$node->subtitle</td>
              <td>$node->title</td>
              <td>$node->latitude</td>
              <td>$node->longitude</td>
              <td>$online</td>
              <td>{$node->parent->title}</td>
            </tr>";
  }

  $page->table = $table;
  $content = renderPage();
}

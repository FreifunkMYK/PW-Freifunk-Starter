<?php

if($input->urlSegment2) throw new Wire404Exception();

if($input->urlSegment1){
  switch($input->urlSegment1){
    case 'list':
      $nodes = $pages->find('template=node');
      $table = '';

      foreach($nodes as $node){

        $status = ($node->online == 1 ? "alert success" : "alert danger");
        $table .="<tr class='$status'>
                  <td>$node->subtitle</td>
                  <td>$node->title</td>
                  <td>$node->latitude</td>
                  <td>$node->longitude</td>
                  <td>$node->online</td>
                  <td>$node->createdUser</td>
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
      } elseif(!$input->post->submit) {
        if(isset($input->get->mac)) $session->node = $input->get->mac;
        if(isset($input->get->key)) $session->key = $input->get->key;
        $content = renderPage('node_registration');
      } else {
        $user = wire('user')->name;
        $parent = $pages->get("template=node_operator, title|name=$user");
        if($parent instanceof Nullpage) $parent = createPage('node_operator', 'node', $user);
        $t = createPage('node', $parent, $input->post->mac);
        $t->key = $input->post->key;
        $t->save();

      	$content = "<h2>Node Hinzugefügt:</h2>
                    <p>
                    Titel: {$t->title}<br>
                    Key : {$t->key}<br>
                    Benutzer: {$t->parent->title}
                    </p>";
      }
      break;
    default:
      throw new Wire404Exception();
  }

} else {
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
              <td>$node->createdUser</td>
            </tr>";
  }

  $page->table = $table;
  $content = renderPage();
}

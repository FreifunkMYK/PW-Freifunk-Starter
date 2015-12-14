<?php

if($input->urlSegment2) throw new Wire404Exception();

switch($input->urlSegment1){
  case 'list':
    $nodes = $pages->find('template=node');
    $table = '';

    foreach($nodes as $node){
      $time = time() - 300;
      if($node->modyfied < setNodeData($node)) setNodeData($node);
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
      $content = renderPage('node_registration');
    } else {
      $parent = wire('user')->name;
      if($pages->get($parent) instanceof Nullpage) createPage('contributor');
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
    // Anything else? Throw a 404
    throw new Wire404Exception();
}

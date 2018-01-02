<?php

function pagesToJSON(PageArray $items) {
 $a = array();
 foreach($items as $item) {
   if($item->template == "router"){
     $a[] = routerToArray($item);
   } else {
     $a[] = pageToArray($item);
   }
 }
 return json_encode($a);
}

function pagesToXml(PageArray $items) {
  $a = array();
  foreach($items as $item){
    if($item->template == "router"){
      $a[] = routerToArray($item);
    } else {
      $a[] = pageToArray($item);
    }
  }

  $xml_data = new SimpleXMLElement('<?xml version="1.0"?><data></data>');

  return arrayToXml($a, $xml_data);
}

function pageToYaml(PageArray $item){
  $a = array();
  foreach($items as $item){
    if($item->template == "router"){
      $a[] = routerToArray($item);
    } else {
      $a[] = pageToArray($item);
    }
  }

  return yaml_emit($a);
}

function arrayToXml($data, &$xml_data){
  foreach($data as $key => $value){
      if(is_array($value)) {
          if( is_numeric($key) ){
              $key = 'item'.$key; //dealing with <0/>..<n/> issues
          }
          $subnode = $xml_data->addChild($key);
          arrayToXml($value, $subnode);
      } else {
          $xml_data->addChild("$key",htmlspecialchars("$value"));
      }
   }
   return $xml_data;
}

function routerToArray(Page $page){
  $outputFormatting = $page->outputFormatting;
  $page->setOutputFormatting(false);

  $data = array(
    "$page->title" => array(
        'hersteller' => $page->parent->title,
        'name' => $page->name,
        'status' => $page->status,
        'outdatet' => false,
        'parent' => $page->parent->path,
        'modified' => $page->modified,
        'image' => ($page->image->first() ? array(
          'data' => $page->image->first()->httpUrl,
          'description' => $page->image->first()->description,
          'modified' => $page->image->first()->modified,
          'created' => $page->image->first()->created
        ) : array()),
        'data' => array(
            'title' => $page->title,
            'description' => $page->body,
            'images' => array(),
            'hardware' => array(
              'ram' => $page->ram,
              'flash' => $page->flash,
              'cpu' => "",
              'price' => ""
              ),
            'features' => array(),
            'infoBlocks' => array(),
          ),
      ),
    );

  foreach($page->info_blocks as $block) {
    if(empty($block->title)) continue;
    $data[$page->title]['data']['infoBlocks'][$block->id] = array(
      'title' => $block->title,
      'body' => $block->body
    );
  }

  $i = 0;
  foreach($page->images as $image){
    $data[$page->title]['data']['images'][$i] = array(
      'data' => $image->httpUrl,
      'description' => $image->description,
      'modified' => $image->modified,
      'created' => $image->created
    );
    $i++;
  }

  foreach($page->features as $feature){
    array_push($data[$page->title]['data']['features'], $feature->name);
  }

  $page->setOutputFormatting($outputFormatting);

  return $data;
}

function pageToArray(Page $page) {

 $outputFormatting = $page->outputFormatting;
 $page->setOutputFormatting(false);

 $data = array(
   'id' => $page->id,
   'parent_id' => $page->parent_id,
   'hersteller' => $page->parent->title,
   'name' => $page->name,
   'status' => $page->status,
   'sort' => $page->sort,
   'sortfield' => $page->sortfield,
   'numChildren' => $page->numChildren,
   'template' => $page->template->name,
   'parent' => $page->parent->path,
   'data' => array(),
   );

 foreach($page->template->fieldgroup as $field) {
   if($field->type instanceof FieldtypeFieldsetOpen) continue;
   $value = $page->get($field->name);
   $data['data'][$field->name] = $field->type->sleepValue($page, $field, $value);
 }

 $page->setOutputFormatting($outputFormatting);

 return $data;
}

$routers = $pages->find("template=router, sort=title");

if($input->urlSegment1 == "json"){

  $useMain = false;
  header("Content-type: application/json");
  echo pagesToJSON($routers);

} else if ($input->urlSegment1 == "yaml"){

  $useMain = false;
  echo pageToYaml($routers);

} else {
  $output = '';
  #include_once('scripts/import.inc');
  #$today = strtotime('-1 day', $today);
  #$h = $pages->find("template=hersteller");

  #foreach($h as $p){
  #  $pages->delete($p, true);
  #  echo "Delete: $p->name <br>";
  #}


  foreach($routers as $router){
    $title = $router->title;
    $image = (count($router->image) ? $router->image->first()->size(300,300)->url : 'https://placehold.it/300x300');
    $features = getTag($router->features, 2);

    $output .= "<a href='{$router->httpUrl}'>
                  <article id='article-{$router->id}' class='large-3 small-6 columns'>
                    <img class='img-responsive panel-thumbnail' src='$image'></img>
                    <div class='panel thumb-body'>
                      <h5>$title</h5>
                      <ul class='inline-list'>
                        $features
                      </ul>
                    </div>
                  </article><!-- #article-7 -->
                </a>";

  }

  $sidebar = renderSidebarFilter();
  $content = "<div id='article' class='large-10 columns'>
                <div class='row'>
                  $output
                </div><!--# row -->
              </div><!-- #article -->
              $sidebar";
}

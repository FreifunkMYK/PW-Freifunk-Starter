<?php

$useMain = false;

echo pagesToJson($pages->find("template=node"));

function pageToArray(Page $page) {

 $outputFormatting = $page->outputFormatting;
 $page->setOutputFormatting(false);

 $data = array(
   'name' => $page->name,
   'status' => $page->subtitle,
   'firmware' => $page->node_firmware,
   'hardware' => $page->node_hardware,
   'operator' => array(
     'name' => $page->operator->name,
      'e-mail' => $page->operator->email,
    ),
   );

 $page->setOutputFormatting($outputFormatting);

 return $data;
}

function pagesToJSON(PageArray $items) {
 $a = array();
 foreach($items as $item) {
   if($item->template == "node"){
     $a[] = routerToArray($item);
   } else {
     $a[] = pageToArray($item);
   }
 }
 return json_encode($a);
}

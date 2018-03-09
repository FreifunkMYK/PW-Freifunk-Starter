<?php
$config->styles->add($config->urls->templates.'css/leaflet.css');
$config->scripts->add($config->urls->templates.'js/leaflet-src.js');

$latitude = str_replace(',','.',$page->latitude);
$longitude = str_replace(',','.',$page->longitude);

/**
 * Nodes aus der nähe anzeigen
 */
$nearnodes = umkreissuche("node", $page->latitude, $page->longitude, 5);

$marker = '';
if($nearnodes){
  foreach($nearnodes as $node){
    $marker .= "L.circle([".str_replace(',','.',$node->latitude).",".str_replace(',','.',$node->longitude)."], 10,{
                  color:'blue',
                  fillColor:".($page->online == 1 ? "'green'" : "'red'"). "
                }).addTo(map)
                  .bindPopup('<a href=\"".$node->httpUrl."\">{$node->subtitle}</a><br>".getDistance($node->dist)." entfernt');";
  }
}

$script = "<script>
            var map = L.map('map').setView([{$latitude}, {$longitude}], 16);

            L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
              maxZoom: 19,
              attribution: '&copy; <a href=\"http://www.openstreetmap.org/copyright\">OpenStreetMap</a>'
            }).addTo(map);

            L.circle([$latitude, $longitude], 10, {
              color:".($page->online == 1 ? "'green'" : "'red'").",
              fillColor: ".($page->online == 1 ? "'green'" : "'red'")."
            }).addTo(map);

            $marker

            map.invalidateSize();
          </script>";


$page->losttime = time_elapsed_string($page->getUnformatted('lastseen'));
$content = renderPage();
if($input->post->delete && !$input->post->cancle){
  deleteNode($page);
  $content = "Der Node wurde erfolgreich gelöscht. <a href='{$pages->get('/node/')->httpUrl}'>Zurück</a>";
}

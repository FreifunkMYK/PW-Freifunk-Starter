<?php
$routers = $pages->find("template=router, sort=title");

$table_tr = "";
foreach ($routers as $router) {
  $companyRouter = strtolower($router->parent->title) ."-". strtolower($router->title);
  $firmwareList = json_decode(file_get_contents("http://firmware.freifunk-myk.de/.static/filter/?filter={$companyRouter}&branch[]=stable&branch[]=beta&output=json"));
  foreach ($firmwareList as $key => $firmware) {
    $template = new TemplateFile($config->paths->templates . "markup/router_firmware_table_tr.inc");
    $template->set('version', $firmware->version);
    //$template->set('builddate', $firmware->builddate);
    $template->set('community', $firmware->community);
    $template->set('release', $firmware->release);
    $template->set('hash', ($firmware->hash ? $firmware->hash->md5 : ""));
    $template->set('filename', $firmware->filename);
    $template->set('url', "http://firmware.freifunk-myk.de". $key);

    $table_tr .= $template->render();
  }
  $template = new TemplateFile($config->paths->templates . "markup/router_firmware_table.inc");
  $template->set('table', $table_tr);
  $firmwareTable = $template->render();

  $content .= "<h2>{$router->title}</h2>$firmwareTable";
}

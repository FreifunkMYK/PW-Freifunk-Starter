<?php

$companyRouter = strtolower($page->parent->title) ."-". strtolower($page->title);
$page->set('firmwareList', json_decode(file_get_contents("http://firmware.freifunk-myk.de/.static/filter/?filter={$companyRouter}&branch[]=stable&branch[]=beta&output=json")));


$stableSysupgrade = "";
$stableFactory = "";
$betaFactory = "";
$betaSysupgrade = "";
foreach ($page->firmwareList as $key => $firmware) {
  $template = new TemplateFile($config->paths->templates . "markup/router_firmware_table_tr.inc");
  $template->set('version', $firmware->version);
  //$template->set('builddate', $firmware->builddate);
  $template->set('community', $firmware->community);
  $template->set('release', $firmware->release);
  $template->set('hash', ($firmware->hash ? $firmware->hash->md5 : ""));
  $template->set('filename', $firmware->filename);
  $template->set('url', "http://firmware.freifunk-myk.de". $key);

  if($firmware->sysupgrade){
    if($firmware->branch == "stable"){
      $stableSysupgrade .= $template->render();
    } else if ($firmware->branch == "beta"){
      $betaSysupgrade .= $template->render();
    }
  } else {
    if($firmware->branch == "stable"){
      $stableFactory .= $template->render();
    } else if ($firmware->branch == "beta") {
      $betaFactory .= $template->render();
    }
  }
}

$table = new TemplateFile($config->paths->templates . "markup/router_firmware_accordion.inc");
$table->set('stableSysupgrade', $stableSysupgrade);
$table->set('stableFactory', $stableFactory);
$table->set('betaSysupgrade', $betaSysupgrade);
$table->set('betaFactory', $betaFactory);

$page->set('firmwareTable', $table->render());

$page->set('headline', $page->parent->title ." ". $page->title);

$content = renderPage();

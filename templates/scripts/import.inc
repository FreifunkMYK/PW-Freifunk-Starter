<?php
###############
# Importscript Article
##############

include_once('import_functions.inc');

$template = 'router';
$parent = '';
$lines = file($core_path.'/gluon_list2.txt');

// Array abarbeiten
foreach($lines as $line_num => $line){
        #preg_match("/gluon-ffmyk-([\d\.]+)-(\w+)-((\d{4})-(\d{2})-(\d{2}))-([\w\-]+).bin/", $line, $router);
        #preg_match("/gluon-ffmyk-([\d\.]+)-(\w+)-((\d{4})-(\d{2})-(\d{2}))-([\w\-\.]+)(.bin|.img|.vmdk|.vdi|.img.gz)/", $line, $output_array);
				preg_match("/gluon-ffmyk-([\d\.]+)-(\w+)-((\d{4})-(\d{2})-(\d{2}))-((tp-link|d-link|linksys|netgear|ubiquiti|x86|buffalo)-([\w\-.]+))(.bin|.img|.vmdk|.vdi|.img.gz)/", $line, $output_array);
        $router[$line_num] = $output_array;
        #echo "Line $line_num = $line <br>/n";
}


foreach($router as $router_line => $routerarray){
	if(empty($routerarray)) continue; // überspringe wenn array leer.

  // Initzalisierung der Variablen
	$hersteller = renderPageName($routerarray[8]);
	$model = renderPageName($routerarray[9]);
	$hersteller_title = ucwords($routerarray[9]);
	$model_title = strtoupper($routerarray[9]);

	$m = $pages->get("template=router, name|title=$model");
	if(!$m instanceof NullPage) continue; // Wenn der Router schon existiert abbrechen!

	$h = $pages->get("template=hersteller, name|title=$hersteller");
	if($h instanceof NullPage) $h = createPage("hersteller", "router", $hersteller_title); // Wenn es den Hersteller noch nicht gibt, anlegen.

	$m = createPage("router", $h, $model_title);
	echo "Router Angelegt: {$h->title} - {$m->title} <br>";
}

<?php
$core_path=dirname(__FILE__);

// Read the CSV file and get an array of rows
function readCSV($file){
	$lines = array();
	foreach(file($file, FILE_IGNORE_NEW_LINES) as $line){
		$lines[] = str_getcsv($line);
	}
	return $lines;
}


/***********************
 * Render
 **********************/
// Render a Page Title
function renderPageName($title){
	$sanitizer = wire('sanitizer');
	$string = iconv("UTF-8", "ASCII//TRANSLIT", $title);
	$string = preg_replace ( '/[^a-z0-9-]/', '', $string ); // Entfernen der Sonderzeichen
	$string = preg_replace("/\s+/", " ", $string);  // Überflüssige Leerzeichen entfernen
	$string = trim($string); // Leerzeichen am Anfang und Ende entfernen
	$string = $sanitizer->pageName($string);

	return $string;
}

function cleanupSummary($summary){
	$summary = strip_tags($summary, '');
	return $summary;
}

function cleanupBody($body){
	// Remove empty <p></p> from the Body
	$body = preg_replace("/<p[^>]*><\\/p[^>]*>/", '', $body);
	// Make shure only one <br> </br> is used
	$body = preg_replace('#<br[^>]*>(\s*<br[^>]*>)+#', '<br />', $body);
  // Remove <br> zwischen </p>	<p>
	$body = preg_replace('#<\\/p[^>]*><br[^>]*><p[^>]*>#', '</p><p>', $body);
	// Remove Drupal views Gallery and set the new Gallery
	$body = preg_replace('/\[\[\{(.*)\}\]\]/', '[[entfernt]]', $body);

	return $body;
}

/**********************
 * getter or maker
 *********************/
// make Tags-Array
function makeArray($list){
	$array = explode(", ",$list);
	// Leere Elemente entfernen
	foreach($array as $key => $value) {
	   if($value == '') {
	  	unset($array[$key]);
  	}
	}
	return $array;
}

// check Page for Pagetyp field
function pageField($field, $title){

}

/**********************
 * Creators
 ********************/
// Create Page
function createPage($template, $parent, $page){
	if(!$parent instanceof Page) $parent = wire('pages')->get("/$parent/"); // Wenn keine Seite übergeben wird suche eine raus.

	$pageName = renderPageName($page);

	$t = new Page();
	$t->template = $template;
	$t->parent = $parent;
	$t->name = $pageName;
	$t->title = $page;
	$t->save();

	return $t;
}

// Creat User
function createUser($user){
	$u = new User();
	$u->name = $user;
	$u->addRole("author");
	$u->addRole("guest");
	$u->save();

	return $u;
}

function getUserImage($imagepath){
	$image = preg_replace('/.*src=\"/', '', $imagepath);
	$image = preg_replace('/\?itok.*/', '', $image);

	return $image;
}

########################################
# Get an Array with the Files to Import
# Key = filepath
# Value = filetype
#
# The fucntion check if the file is supported
# and with field support this file, the image
# or the file field?
########################################
function getFiles($filelist){
	$files = array();
	foreach($filelist as $filepath){
		$explode_path = explode(".", $filepath);
		$type	= strtolower($explode_path[3]);

		$datatype = array(	"jpg"=>"image",
											"png"=>"image",
											"jpeg"=>"image",
											"gif"=>"image",
											"pdf"=>"file",
											"doc"=>"file",
											"docx"=>"file",
											"xls"=>"file",
											"xlsx"=>"file",
											"zip"=>"file",
											"ppt"=>"file",
											"pptx"=>"file",
											"pps"=>"file",
											"ppsx"=>"file",
											"odt"=>"file",
											"mp3"=>"file",
											"m4a"=>"file",
											"ogg"=>"file",
											"wav"=>"file",
											"mp4"=>"file",
											"mov"=>"file",
											"wmv"=>"file",
											"avi"=>"file",
											"mpg"=>"file",
											"ogv"=>"file",
											"3gp"=>"file",
											"m4v"=>"file",
											);

		if(array_key_exists($type,$datatype)) $files[$filepath] = $datatype[$type];
		}

		return $files;
}

##############################################
# This function checked if the file is alrady
# includet or not.
# Parameter:
# $fileType // image or file
# $file // The complete file path
# $title // PageTitle or Name
#
# Return
# true or false
###############################################
function fileExists($fileType, $file, $title){
	$explode_path = explode("/", $file);
	$fileName = end($explode_path);
	$field = $fileType.'s';

	// Search for Pages with the file fildname and file name and title
	$pageWithFile = wire('pages')->get("$field=$fileName, title|name=$title");

	// Have Page an ID than return true so the file exists!
	if($pageWithFile->id != "") return true;

	return false;
}

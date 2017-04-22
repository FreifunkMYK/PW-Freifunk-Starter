<?php
/**********************************************
* Create a markdown documentation file for your
* Processwire Projekt with Links to API and
* official Dokumentation.
*
* Author: kreativmonkey
* version: 0.1
***********************************************/

foreach($templates as $template){
  foreach($template->fields as $field){
    echo "<p>";
    echo "Field: {$field->name}<br />";
    echo "Type: {$field->type}<br />";
    echo "</p>";
  }
}
/* Get all fields from a Page
foreach($page->fields as $field) {
 echo "<p>";
 echo "Field: {$field->name}<br />";
 echo "Type: {$field->type}<br />";
 echo "Value: " . $page->get($field->name);
 echo "</p>";
}*/

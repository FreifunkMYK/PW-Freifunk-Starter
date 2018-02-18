<?php
  /**
   * Folder Filter Foo
   * @author Florian "adlerweb" Knodt <adlerweb@adlerweb.info>


Inline-Doku oder sowas:

URL: http://firmware.freifunk-myk.de/.static/filter/

Parameter:

filter: Textsuche, z.B. Hardware-ID.
	Default: Kein Filter

branch[]: wo gesucht werden soll.
	Mögliche Werte: stable, beta, nightly
	Kann mehrfach angegeben werden
	Default: Alle Branches

output: Ausgabeart
	html -> Webseite mit Ergebnissen
	json
	serialized -> PHP-Array via serialize
	raw -> var_dump (zum debuggen)

Beispiel für eine URL:

http://firmware.freifunk-myk.de/.static/filter/?filter=tp-link-tl-wr841n-nd&branch[]=stable&branch[]=beta&output=json

(Alle Firmwares mit dem Text "tp-link-tl-wr841n-nd" aus Stable und Beta als JSON)

Bei allen Datentypen außer HTML ist die Ausgabe ein assoziatives, rekursives Array. Als Index dient die relative URL zur Datei. Pro Eintrag sind folgende Infos verfügbar:

    ["filename"]=>
    string(77) "gluon-ffmyk-2016.1.3-stable-2016-05-24-tp-link-tl-wr841n-nd-v7-sysupgrade.bin"
    ["release"]=>
    string(8) "2016.1.3"
    ["branch"]=>
    string(6) "stable"
    ["builddate"]=>
    string(10) "2016-05-24"
    ["hardware"]=>
    string(20) "tp-link-tl-wr841n-nd"
    ["version"]=>
    string(2) "v7"
    ["sysupgrade"]=>
    bool(true)
    ["extension"]=>
    string(3) "bin"
    ["hash"]=>
    array(3) {
      ["md5"]=>
      string(32) "d7e536858acb15753f71ab102b4241d7"
      ["sha1"]=>
      string(40) "a8b2adf357d91b6b0ce33f768c237b1d1aea0c64"
      ["sha256"]=>
      string(64) "8bc6fdf7ee287d9d069f11a2d6a7ac6161b5f06a5ba9e51a0859d84d140375a7"
    }

--
Mit freundlichen Grüßen   ||   Sincerely yours
Florian Knodt ·· www.adlerweb.info · @adlerweb


   **/

   $htmlstart = '<!DOCTYPE html>
   <html>
   <head>
   <meta charset="UTF-8">
   <title>Firmware List</title>
   <meta name="viewport" content="width=device-width, user-scalable=yes">
   <style>
   footer h1, ul {
     margin: 0;
     padding: 0;
   }

   footer h1, footer ul, footer ul li {
     display: inline-block;
     font-size: 10pt;
   }

   footer h1, footer ul li a {
     padding: 0.5em;
   }

   footer ul {
     list-style: none;
     padding: 0;
   }

   footer {
     background: #333;
     color: #fefefe;
     position: fixed;
     bottom: 0;
     width: 100%;
     z-index: 999;
   }

   footer a {
     text-decoration: none;
     color: #FFCC01;
   }

   footer a:hover {
     background: #C83771;
     text-decoration: underline;
   }

   footer h1 a:hover {
     background:transparent;
   }


   .active {
     background: #FFCC01;
     color: #333;
   }


   footer h1 a {
     color: #FFFFFF;
   }




   body {
   background-color: #cccccc;
   font-family: "Roboto", helvetica, arial, sans-serif;
   font-size: 16px;
   font-weight: 400;
   text-rendering: optimizeLegibility;
   margin: 0;
   padding: 0;
   margin-bottom: 1em;
   }

   div.table-title {
   display: block;
   margin: auto;
   width: 80%;
   padding:5px;
   }

   .table-title h3 {
   color: #fafafa;
   font-size: 30px;
   font-weight: 400;
   font-style:normal;
   font-family: "Roboto", helvetica, arial, sans-serif;
   text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1);
   text-transform:uppercase;
   }


   /*** Table Styles **/

   .table-fill {
   background: white;
   border-radius:3px;
   border-collapse: collapse;
   height: 320px;
   margin: auto;
   padding:5px;
   width: 80%;
   box-shadow: 0 5px 10px rgba(0, 0, 0, 0.1);
   animation: float 5s infinite;
   }

   th {
   color:#D5DDE5;;
   background:#1b1e24;
   border-bottom:4px solid #9ea7af;
   border-right: 1px solid #343a45;
   font-size:23px;
   font-weight: 100;
   padding:24px;
   text-align:left;
   text-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);
   vertical-align:middle;
   }

   th:first-child {
   border-top-left-radius:3px;
   }

   th:last-child {
   border-top-right-radius:3px;
   border-right:none;
   }

   tr {
   border-top: 1px solid #C1C3D1;
   border-bottom-: 1px solid #C1C3D1;
   color:#666B85;
   font-size:16px;
   font-weight:normal;
   text-shadow: 0 1px 1px rgba(256, 256, 256, 0.1);
   }

   tr:hover td {
   background:#4E5066;
   color:#FFFFFF;
   border-top: 1px solid #22262e;
   border-bottom: 1px solid #22262e;
   }

   tr:first-child {
   border-top:none;
   }

   tr:last-child {
   border-bottom:none;
   }

   tr:nth-child(odd) td {
   background:#EBEBEB;
   }

   tr:nth-child(odd):hover td {
   background:#4E5066;
   }

   tr:last-child td:first-child {
   border-bottom-left-radius:3px;
   }

   tr:last-child td:last-child {
   border-bottom-right-radius:3px;
   }

   td {
   background:#FFFFFF;
   padding:20px;
   text-align:left;
   vertical-align:middle;
   font-weight:300;
   font-size:18px;
   text-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1);
   border-right: 1px solid #C1C3D1;
   }

   td:last-child {
   border-right: 0px;
   }

   th.text-left {
   text-align: left;
   }

   th.text-center {
   text-align: center;
   }

   th.text-right {
   text-align: right;
   }

   td.text-left {
   text-align: left;
   }

   td.text-center {
   text-align: center;
   }

   td.text-right {
   text-align: right;
   }

   .fwlink {
     font-size: 60%;
   }

   </style>
   <script src="sorttable.js"></script>
   </head>
   <body>
   <footer>
     <h1><a href="http://www.freifunk-myk.de/" id="sitelink">freifunk-myk.de</a></h1>
     <ul>
       <li><a href="http://wiki.freifunk-myk.de/">Wiki</a></li>
       <li><a href="http://pad.freifunk-myk.de/">Pad</a></li>
       <li><a href="http://map.freifunk-myk.de/">Karte</a></li>
       <!--<li><a href="http://status.freifunk-myk.de/traffic.html">Traffic</a></li>-->
       <li><a class="active" href="http://firmware.freifunk-myk.de">Firmware</a></li>
       <li><a href="http://register.freifunk-myk.de">Knotenverwaltung</a></li>
     </ul>
   </footer>';

/** Outputformat **/
$output_allowed = array('feelinglucky', 'raw', 'html', 'json', 'serialized', 'form');
$output = 'form';
if(isset($_REQUEST['output']) && in_array(strtolower($_REQUEST['output']), $output_allowed)) {
  $output = strtolower($_REQUEST['output']);
}

################################
# Filters
################################
$communitys = array(
  'aw' => 'ffaw',
  'coc' => 'ffcoc',
  'ems' => 'ffems',
  'ko' => 'ffko',
  'my' => 'ffmy',
  'sim' => 'ffsim',
);

$ignore = array(
  'modules'
);

$branch = array(
  'stable' => 'stable',
  'beta' => 'beta',
  'nightly' => 'nightly/NORMAL/images'
);

$filter = '';
if(isset($_REQUEST['filter']) && isset($_REQUEST['output']) && $_REQUEST['output'] == 'feelinglucky') {
    $filter = strtolower(str_replace(array(' ', '/'), '-', $_REQUEST['filter']));
    if(!preg_match('/^[\w\-\_\d]+$/', $filter)) die();
}
if(isset($_REQUEST['filter']) && preg_match('/^[\w\-\_\d]+$/', $_REQUEST['filter'])) $filter = $_REQUEST['filter'];

if(isset($_REQUEST['branch']) && is_array($_REQUEST['branch'])) {
  $clean = true;
  $newdoread = array();
  foreach($_REQUEST['branch'] as $check) {
    if(!isset($branch[strtolower($check)])) {
      $clean = false;
    }else{
      $newdoread[strtolower($check)] = $branch[strtolower($check)];
    }
  }

  if($clean) $branch = $newdoread;
}

$fulllist = array();
$curhash = false;

foreach($branch as $typestr => $type) {
  foreach($communitys as $community => $name){
    $out[$typestr] = recursiveRead($typestr, '../../'.$name.'/'.$type);
  }
}

switch($output) {
  case 'form':
    echo $htmlstart.'
  <div class="table-title">
<h3>Firmware List</h3>
</div>
<table class="table-fill">
<th class="text-left">Suchwort</th>
<th class="text-left">Branch</th>
<th class="text-left">Ausgabe</th>
<th class="text-left">Suche</th>
</tr>
</thead>
<tbody class="table-hover">
<tr>
  <form method="get" action="./">
    <td class="text-left"><input type="text" name="filter"></td>
    <td class="text-left"><select name="branch[]">
        <option value="">Alle</option>
        <option>Stable</option>
        <option>Beta</option>
        <option>Nightly</option>
      </select></td>
    <td class="text-left"><select name="output">
        <option>HTML</option>
        <option>JSON</option>
        <option>Serialized</option>
        <option>RAW</option>
        <option>feelinglucky</option>
      </select></td>
    <td class="text-left"><input type="submit" value="Suche"></td>
  </form>
  </tr></tbody>
</table>
  </body>
</html>company
';
    break;
  case 'html':
    echo $htmlstart.'
    <div class="table-title">
      <h3>Firmware List</h3>
    </div>
    <table class="table-fill sortable">
      <thead>
        <tr>
          <th class="text-left"><span title="Stable == Stabile Version · Beta == Testversion, mehr Funktionen, neuere Hardware, ggf. mehr Fehler · Nightly == Direkt aus den Quellen, ungetestet">Branch</span></th>
          <th class="text-left"><span title="Als Basis dienende Gluon-Version">Release</span></th>
          <th class="text-left"><span title="Release für den Raum">Community</span></th>
          <!-- <th class="text-left"><span title="Erstelldatum der Firmware">Datum</span></th> -->
          <th class="text-left"><span title="Vorgesehenes Routermodell">Hardware</span></th>
          <th class="text-left"><span title="Versionsnummer der Routerhardware">HW-Rev.</span></th>
          <th class="text-left"><span title="factory == Für Router mit Herstellerfirmware · Sysupgrade = Zum aktualisieren älterer Freifunk-Firmware oder Wechsel von anderen OpenWRT-Systemen">Typ</span></th>
          <th class="text-left">Download</th>
        </tr>
      </thead>
      <tbody class="table-hover">
';

foreach($fulllist as $url=>$firmware) {
  echo '
        <tr>
          <td class="text-left">'.htmlentities($firmware['branch']).'</td>
          <td class="text-left">'.htmlentities($firmware['release']).'</td>
          <td class="text-left">'.htmlentities($firmware['community']).'</td>
          <td class="text-left">'.htmlentities($firmware['hardware']).'</td>
          <td class="text-left">'.htmlentities($firmware['version']).'</td>
          <td class="text-left">'.(($firmware['sysupgrade']) ? 'sysupgade' : 'factory').'</td>
          <td class="text-left"><a href="'.htmlentities($url).'" title="';
          foreach($firmware['hash'] as $htype => $hval) echo $htype.': '.$hval."\n";
          echo '" class="fwlink">'.htmlentities($firmware['filename']).'</a></td>
        </tr>';
}

echo '
      </tbody>
    </table>
  </body>
</html>
';
    break;
  case 'json':
    echo json_encode($fulllist);
    break;
  case 'serialized':
    echo serialize($fulllist);
    break;
  case 'feelinglucky':
    $curdate = 0;
    $fw = '';
    foreach($fulllist as $path => $fwinfo) {
        if($fwinfo['sysupgrade']) {
            if(strtotime($fwinfo['builddate']) >= $curdate) {
                $fw = array($path, $fwinfo['release'].'-'.$fwinfo['branch'].'-'.$fwinfo['builddate']);
                if(isset($fwinfo['hash']['md5'])) $fw[] = $fwinfo['hash']['md5'];
                $curdate = strtotime($fwinfo['builddate']);
            }
        }
    }
    if($fw != '') {
        echo 'http://firmware.freifunk-myk.de'.implode("\n", $fw);
    }
    break;
  case 'raw':
  default:
    echo '<pre>';
    var_dump($fulllist);
}


function parsehashes($dir) {
  global $curhash;
  if(file_exists($dir.'/md5sums.txt')) {
    $start = microtime(true);
    $temp = file_get_contents($dir.'/md5sums.txt');
    preg_match_all('/([a-f0-9]+)\s+.+?(gluon-ffmyk-[^\/\s]+)/', $temp, $match);
    unset($temp);
    for($i=0; $i<count($match[0]); $i++) {
      $curhash[$match[2][$i]]['md5'] = $match[1][$i];
    }
  }
  if(file_exists($dir.'/sha1sums.txt')) {
    $temp = file_get_contents($dir.'/sha1sums.txt');
    preg_match_all('/([a-f0-9]+)\s+.+?(gluon-ffmyk-[^\/\s]+)/', $temp, $match);
    unset($temp);
    for($i=0; $i<count($match[0]); $i++) {
      $curhash[$match[2][$i]]['sha1'] = $match[1][$i];
    }
  }
  if(file_exists($dir.'/sha256sums.txt')) {
    $temp = file_get_contents($dir.'/sha256sums.txt');
    preg_match_all('/([a-f0-9]+)\s+.+?(gluon-ffmyk-[^\/\s]+)/', $temp, $match);
    unset($temp);
    for($i=0; $i<count($match[0]); $i++) {
      $curhash[$match[2][$i]]['sha256'] = $match[1][$i];
    }
  }
}


function recursiveRead($branch, $startdir) {
  global $ignore, $filter, $fulllist, $curhash, $communitys;

  $out = array();

  $dir = opendir($startdir);

  if(!$dir) {
    trigger_error('Internal Server Error - Can not open folder '.$startdir, E_USER_WARNING);
    return $out;
  }

  while (false !== ($entry = readdir($dir))) {
    if($entry != '.' && $entry != '..' && !in_array($entry, $ignore)) {
      if(is_dir($startdir.'/'.$entry)) {
        parsehashes($startdir.'/'.$entry);
        $out[$entry] = recursiveRead($branch, $startdir.'/'.$entry);
      }else{
        if($filter == '' || preg_match('/'.$filter.'/', $entry)) {
          if(preg_match('/gluon-ff([\w]+)-([\d\.]+)-([\w\d\-]+?)(\-?(v[\d\.]+))?(-(sysupgrade))?\.(\w+)/', $entry, $match)) {
            $out[$entry] = $entry;

            $hash = array();
            if(isset($curhash[$match[0]]['md5'])) $hash['md5'] = $curhash[$match[0]]['md5'];
            if(isset($curhash[$match[0]]['sha1'])) $hash['sha1'] = $curhash[$match[0]]['sha1'];
            if(isset($curhash[$match[0]]['sha256'])) $hash['sha256'] = $curhash[$match[0]]['sha256'];

            $fulllist[str_replace('//', '/', str_replace('../', '/', $startdir)).'/'.$entry] = array(
                'filename' => $match[0], // Full name of the file
                'release' => $match[2], // Versionnumber
                'community' => $communitys[$match[1]], // Name of the community
                'branch' => $branch,
                'builddate' => '', // Existiert derzeit nicht!!!
                'hardware' => $match[3],
                'version' => $match[5],
                'sysupgrade' => (($match[7] == 'sysupgrade') ? true : false),
                'extension' => $match[8],
                'hash' => $hash
            );
          }
        }
      }
    }
  }

  return $out;
}


?>

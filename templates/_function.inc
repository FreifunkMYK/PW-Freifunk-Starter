<?php
/***************************************************************************************
 * _functions.inc
 *
 * The following defined here so that they can be used by multiple template files.
 * This file contains various "render" functions that generate markups specific
 * to the site profile (theme).
 *
 * What's Here:
 *
 * getTag() - Render a Tag List.
 * renderOnPageBlocks() - Render on-page blocks.
 * renderInfoBlocks() - Render Info blocks.
 * renderCopyrights(Page $page) - Render site copyrights content
 * getReferences() - Render testimonial/references
 * renderSidebar() - Return sidebar item as html markup
 * renderGoogleLocationMap() - Render google map locations
 * getContactUsForm() - Render contact form
 *
 *
 */

 /**
  * renderCopyrights(Page $page) - Render site copyrights content
  * You can find site copyrights content under Admin > Pages > Home edit page and find Global site settings.
  *
  * @param Page $page - instance of the page.
  * @return String - html markup string of copyright statement
  */

setlocale(LC_NUMERIC, 'en_US.UTF-8');

#########################################################
# getter
#########################################################
 /**
  * getTag()
  *
  * @param  PageArray $tags - instance of PageArray
  * @param  int $limit - limit of the output
  * @return string - html markup string of Tag list elements.
  */
function getTag(PageArray $tags, $limit = 0){
  $list = "";
  $count = "0";
  foreach($tags as $tag){
    $count++;
    if($count > $limit && $limit != 0) break;
    $title = $tag->title;
    $list .= "<li>$title</li>";
  }
  return $list;
}

function getPageArray($posts){
  // Erzeuge ein Array aus $posts
  if(!$posts instanceof PageArray){
    if($posts instanceof Page){
      $post = $posts;
      $posts = new PageArray();
      $posts->add($post);
    } else if(empty($posts)){
      $post = wire('page');
      $posts = new PageArray();
      $posts->add($post);
    } else if(is_string($posts)){
      // selector string
      $selector = $posts;
      $posts = wire('pages')->find("$selector");
    }
  }
  return $posts;
}

###################################################
# Render
####################################################
function renderPage($template = "") {
  if(empty($template)) $template = wire('page')->template;
  $config = wire('config');

  //Create delegate template
  $template = new TemplateFile($config->paths->templates . "markup/$template.inc");

  //Get the output and save it on $out.
  return $template->render();
}

/* Alternative zur obigen Lösung:
function renderPage($posts = "", $small = false){
  if(!$posts instanceof PageArray){
    if($posts instanceof Page){
      $post = $posts;
      $posts = new PageArray();
      $posts->add($post);
    } else if(empty($posts)){
      $post = wire('page');
      $posts = new PageArray();
      $posts->add($post);
    } else if(is_string($posts)){
      // selector string
      $selector = $posts;
      $posts = wire('pages')->find("$selector");
    }
  }

  $out = '';
  foreach ($posts as $p) {
    switch($p->template){
      case 'post':
        $out .= renderPost($p, $small);
        break;
      case 'node':
        $out .= renderEvent($p, $small);
        break;
      case 'router':
        $out .= renderRouter($p, $small);
        break;
      case 'profile':
        $out .= renderProfile($p, $small);
        break;
    }
  }

  if($posts->getLimit() < $posts->getTotal()) $out .= $posts->renderPager(array(
    'nextItemLabel' => "Ältere Artikel",
    'previousItemLabel' => "Neure Artikel",
  ));

  return $out;
}
*/

function renderCopyrights(Page $page) {

    if (!$page->summary) return '';

    $text = str_replace(
        // find these:
        array('{year}'),
        // and replace with these:
        array(date('Y')),
        // in the copyright_text text
        $page->summary);

    return $text;
}

function renderTimeline($timeline){
  // Überprüfe ob $timeline von der richtigen Instants ist
  if(!$timeline instanceof PageArray) {
    if($timeline instanceof Page){
      //single page
      $post = $timeline;
      $timeline = new PageArray();
      $timeline->add($post);
    } else if(is_string($timeline)) {
      // selector string
      $selector = $timeline;
      $timeline = wire('pages')->find("template=post, sort=-date, $selector");
    } else {
      throw new WireException('getTimeline requires a PageArray, Page or selector string');
    }
  }


  // Count for the while Schleife
  $count = 0;
  $timeline_blocks = '';
  $config = wire('config');

  foreach($timeline as $post){
    $image = $post->images->first();
    $t = new TemplateFile($config->paths->templates . "markup/timeline_block.inc");
    $t->set('title', $post->date);
    $t->set('subtitle', $post->title);
    $t->set('summary', $post->summary);
    $t->set('image', $post->images->first()->size(156,156)->url);
    $t->set('image_description', $image->description);
    $t->set('readmore', $post->httpUrl);
    $t->set('leftright', ($count % 2 != 0 ? "" : "class='timeline-inverted'"));

    $timeline_blocks .= $t->render();

    $count++;
  }

  $t = new TemplateFile($config->paths->templates . "markup/timeline.inc");
  $t->set('timeline_blocks', $timeline_blocks);

  return $t->render();

}

/* Vorbereitung für Landingpages einzelner Communitys */
function renderOnPageBlocks() {

    // Get the current page instance from global scope.
    $page = wire('page');
    // Get the config instance from global scope.
    $config = wire('config');

    if (!count($page->on_page_blocks)) return '';

    /* Get on-page blocks */
    $pageBlocks = $page->on_page_blocks;

    $out = '';

    foreach ($pageBlocks as $block) {

        //Create delegate template
        $template = new TemplateFile($config->paths->templates . "markup/page-block-type-{$block->render_option}.inc");
        //Assign the rendered view to content variable to show up on page-block-type-x.inc
        $template->set('image', $block->image);

        $content = str_replace(
            // find these:
            array('<ul>','<!-- pagebreak -->'),
            // and replace with these:
            array('<ul class="default-list-square">', '<br/>'),
            // in the $block->body text
            $block->body
        );

        //Assign the rendered view to content variables to show up on page-block-type-x.inc
        $template->set('content', $content);
        $template->set('headline', $block->get('headline|title'));

        //Get the output and save it on $out.
        $out .= $template->render();
    }

    return $out;
}

/* Rendern der Infoblocks von Router */
function renderInfoBlocks() {

    // Get the current page instance from global scope.
    $page = wire('page');
    // Get the config instance from global scope.
    $config = wire('config');

    if (!count($page->info_blocks)) return '';

    /* Get Info blocks */
    $infoBlocks = $page->info_blocks;

    $out = '';

    foreach ($infoBlocks as $block) {

        //Create delegate template
        $template = new TemplateFile($config->paths->templates . "markup/info-block.inc");

        $content = str_replace(
            // find these:
            array('<ul>','<!-- pagebreak -->'),
            // and replace with these:
            array('<ul class="default-list-square">', '<br/>'),
            // in the $block->body text
            $block->body
        );

        //Assign the rendered view to content variables to show up on page-block-type-x.inc
        $template->set('content', $content);
        $template->set('headline', $block->get('title'));

        //Get the output and save it on $out.
        $out .= $template->render();
    }

    return $out;
}

function renderSidebarFilter(){
  $hersteller = listPages(wire('pages')->find("template=hersteller"));
  $features = listPages(wire('pages')->find("template=features"));

  $output = "<div id='sidebar' class='large-2 columns'>
                <h3>Filter</h3>
                <h5>Hersteller</h5>
                <ul class='filter'>
                  $hersteller
                </ul>

                <h5>Features</h5>
                <ul class='filter'>
                  $features
                </ul>
              </div><!-- #sidebar-->";

  return $output;
}

// Render a Page Title
function renderPageName($title){
	$sanitizer = wire('sanitizer');
	$string = iconv("UTF-8", "ASCII//TRANSLIT", $title);
	$string = preg_replace("/\s+/", " ", $string);  // Überflüssige Leerzeichen entfernen
	$string = trim($string); // Leerzeichen am Anfang und Ende entfernen
	$string = $sanitizer->pageName($string);

	return $string;
}

function renderNewNodesList(){
  $nodes = wire('pages')->find("template=node, sort=-created, limit=10");
  $list = "";
  foreach($nodes as $node){
    $color = ($node->online ? "green" : "red");
    $alt = ($node->online ? "Online" : "Offline");
    $list .= "<li><i class='fa fa-wifi' style='color:$color' alt='$alt'></i> <a href='{$node->httpUrl}'>{$node->get('subtitle|title')}</a>";
    $list .= ($node->address ? "<br/><span class='node-address'><i class='fa fa-fw'></i> {$node->address}</span></li>" : "");
  }
  $output = "<h4>Neuste Nodes</h4><ul class='node-list'>$list</ul>";
  return $output;
}

#########################################################
# Mac Address Handling
#########################################################
function validateMac($mac){
  // trim
  $mac = trim($mac);
  // 01:23:45:67:89:ab
  if (preg_match('/^([a-fA-F0-9]{2}:){5}[a-fA-F0-9]{2}$/', $mac))
    return true;
  // 01_23_45_67_89_ab
  if (preg_match('/^([a-fA-F0-9]{2}_){5}[a-fA-F0-9]{2}$/', $mac))
  // 01-23-45-67-89-ab
  if (preg_match('/^([a-fA-F0-9]{2}\-){5}[a-fA-F0-9]{2}$/', $mac))
    return true;
  // 0123456789ab
  else if (preg_match('/^[a-fA-F0-9]{12}$/', $mac))
    return true;
  // 0123.4567.89ab
  else if (preg_match('/^([a-fA-F0-9]{4}\.){2}[a-fA-F0-9]{4}$/', $mac))
    return true;
  else
    return false;
}

function normalizeMac($mac){
  // trim
  $mac = trim($mac);

  // remove any dots
  $mac =  str_replace(".", ":", $mac);

  // remove any underscore
  $mac = str_replace("_", ":", $mac);

  // replace dashes with colons
  $mac =  str_replace("-", ":", $mac);

  // counting colons
  $colon_count = substr_count ($mac , ":");

  // insert enough colons if none exist
  if ($colon_count == 0)
  {
    $mac =  substr_replace($mac, ":", 2, 0);
    $mac =  substr_replace($mac, ":", 5, 0);
    $mac =  substr_replace($mac, ":", 8, 0);
    $mac =  substr_replace($mac, ":", 11, 0);
    $mac =  substr_replace($mac, ":", 14, 0);
  }

  // uppercase
  $mac = strtoupper($mac);

  // DE:AD:BE:EF:10:24
  return $mac;
}

function serializeMac($serialize){
  $serialize = getPageArray($serialize);
  $serialize_array = array();

  foreach($serialize as $one){
        $serialize_array[] = array('mac' => strtolower(str_replace(":", "", $one->title)),
                          'staticip' => strtoupper($one->static_ip));
  }

  return serialize($serialize_array);
}

##########################################################
# Page and User handling
#########################################################
function listPages(PageArray $pages){
  $output = "";
  foreach($pages as $page){
    $output .= "<li><a href='{$page->httpUrl}'>{$page->title}</a></li>";
  }
  return $output;
}


/**
 * Function to Create Processwire Pages
 *
 * @param  string $template     the template for the new page
 * @param  Page/string $parent  parent Page can be a Page or string
 * @param  string $title        Title of the new Page
 * @return PageArray            The new Page
 */
function createPage($template, $parent, $title){
	if(!$parent instanceof Page) $parent = wire('pages')->get("/$parent/"); // Wenn keine Seite übergeben wird suche eine raus.

	$pageName = renderPageName($title);

	$t = new Page();
	$t->template = $template;
	$t->parent = $parent;
	$t->name = $pageName;
	$t->title = $title;
	$t->save();

	return $t;
}

/**
 * Fucntion to handle Node registration
 *
 * @param string $mac     the MAC Address from the Node
 * @param string $key     the Node PublicKey for the VPN connection_status
 * @return int            -1 = Existiert bereits; 0 = Fehler; 1 = true; 2 = aktualisiert
 */
function registerNode($mac, $key){
  if(empty($mac) || empty($key)) return 0;
  // Definiere Systemvariablen
  $page = wire('page');
  $node = wire('pages')->get("template=node, title=$mac");
  $parent = wire('pages')->get($page->id);
  $operator = wire('user')->id;
  // Existiert der Node bereits?
  if($node instanceof Nullpage){
    $titlemac = strtoupper($mac);
    $n = createPage('node', $parent, $titlemac);
    $fehlercode = 1;
  } elseif($node->operator->id != $operator) {
    // Checke ob der Node vom Besitzer geändert wird.
    wire('log')->save('node', "Node $mac existiert bereits!");
    return -1;
  } else {
    $n = $node;
    $fehlercode = 2;
  }

  $n->key = $key;
  $n->operator = $operator;
  $n->of(false);
  $n->save();
  $n->of(true);

  // Remove key and mac from the session!
  wire('session')->remove('key');
  wire('session')->remove('mac');

  return $fehlercode;
}

/**
 * deleteNode deletes one ore more nodes.
 */
function deleteNode($posts){
  // Erzeuge ein Array aus $posts
  if(!$posts instanceof PageArray){
    if($posts instanceof Page){
      $post = $posts;
      $posts = new PageArray();
      $posts->add($post);
    } else if(empty($posts)){
      $post = wire('page');
      $posts = new PageArray();
      $posts->add($post);
    } else if(is_string($posts)){
      // selector string
      $selector = $posts;
      $posts = wire('pages')->find("$selector");
    }
  }

  foreach($posts as $post){
    if($post->template != "node") break; // Only for nodes
    $pages = wire('pages');
    $user = wire('user');

    wire("log")->save('delete', "$post->title was Deleted by $user->name");
    $pages->delete($post, true);
  }

  return true;
}

function registerUser($u){
  // inizialisation ldapHelper Module for Ldap Registration
  $ldapHelper = wire('modules')->get("ldapHelper");

  if(!wire('users')->get($u["username"]) instanceof NullPage) return "<div data-alert class='alert-box alert'>Der Benutzer mit dem Namen {$u["username"]} existiert bereits.</div>";
  if(!wire('users')->get("email={$u["email"]}") instanceof NullPage) return "<div data-alert class='alert-box alert'>Die E-Mail {$u["email"]} wird bereits verwendet.</div>";

  if(!$ldapHelper->ldapHelperRegistradeUser($u)) return "<div data-alert class='alert-box alert'>Das Anlegen eines LDAP Users hat leider nicht funktioniert. Bitte versuche es zu einem späteren Zeitpunkt noch einmal.</div> ";

  $new_user = new User();
  $new_user->of(false);
  $new_user->name = $u["username"];
  $new_user->email = $u["email"];
  $new_user->pass = $u["password"];
  $new_user->addRole("user");
  $new_user->firstname = $u["firstname"];
  $new_user->lastname = $u["lastname"];
  $new_user->admin_theme = "AdminThemeReno";
  $new_user->authkey = getToken();
  $new_user->save();
  $new_user->of(true);

  $aktivierungslink = wire('page')->httpUrl ."?authkey=". $new_user->authkey ."&user=". $new_user->name;
  $mail = wireMail();
  $mail->to($u["email"])->from('registration@ffmyk.de');
  $mail->subject("Account Aktivierung");
  $mail->body("===== Account Aktivierung ===== \n\n
  mit dieser E-Mail kannst du deinen soeben eingerichteten Account bei Freifunk-Myk aktivieren.\n
  $aktivierungslink \n
  Sollte der Link nicht anklickbar sein, kopiere ihn und füge ihn in die Adresszeile deines Browsers ein.");
  if($mail->send()) wire('log')->message('Send Mail: Account Aktivierung') ;

  $session = wire('session');
  $session->remove('username');
  $session->remove('email');
  $session->remove('firstname');
  $session->remove('lastname');

  return "<div data-alert class='alert-box success radius'>Die Registrierung war erfolgreich, du erhälst nun eine E-Mail mit einem Aktivierungslink.</div>";
}
#################################################
# secret
#################################################
function authorize($auth_user, $secret){
  if($auth_user->authkey === $secret && $auth_user->authsuccess != true){
    $auth_user->of(false);
    $auth_user->authsuccess = true;
    $auth_user->save();
    $auth_user->of(true);

    $mail = wireMail();
    $mail->to($auth_user->email)->from('registration@ffmyk.de');
    $mail->subject("Herzlich Wilkommen");
    $mail->body("===== Wilkommen bei Freifunk-Myk ===== \n\n
    Wir freuen uns dich bei Freifunk-Myk begrüßen zu dürfen. Im Folgenden erklären wir dir die Besonderheiten deines Accounts. \n\n
    === Mehr als nur ein Account === \n
    Mit deinem Account bei Freifunk-Myk kannst du dich nicht nur auf unserer Webseite, sondern bei vielen weiteren Diensten im Freifunk-Myk einloggen.\n
    Ob Router registrieren, Wiki editieren oder dich im Jabber zu unterhalten. Alles mit einem Account.\n\n
    === Jabber ===\n
    Jabber ist ein föderalisiertes Chatsystem. Es stehten Clients für Computer, Smartphones und andere Geräte bereit.
    Du besitzt mit der Registrierung auf Freifunk-Myk direkt einen Jabber Account mit der folgenden ID: {$auth_user->name}@ffmyk.de und deinem Passwort.
    Wenn du dich einloggst findest du in deiner Kontaktliste direkt eine Liste der Administratoren und kannst dich mit ihnen unterhalten.\n\n
    Das Freifunk-Myk Team wünscht dir viel Spaß und freut sich auf deine Mitarbeit.");
    if($mail->send()) wire('log')->message("Send Mail: Welcome to {$auth_user->email} ") ;

    return "<div data-alert class='alert-box success radius'>
    Dein Account ist erfolgreich Aktiviert. Wir senden dir noch eine Wilkommens E-Mail in der du wichtige Informationen zu unseren Diensten und zu deinem Account findest.
    </div>";
  } else {
    return "<div data-alert class='alert-box alert'>
      Dein Account wurde bereits Aktiviert.
    </div>";
  }
}

function crypto_rand_secure($min, $max) {
        $range = $max - $min;
        if ($range < 0) return $min; // not so random...
        $log = log($range, 2);
        $bytes = (int) ($log / 8) + 1; // length in bytes
        $bits = (int) $log + 1; // length in bits
        $filter = (int) (1 << $bits) - 1; // set all lower bits to 1
        do {
            $rnd = hexdec(bin2hex(openssl_random_pseudo_bytes($bytes)));
            $rnd = $rnd & $filter; // discard irrelevant bits
        } while ($rnd >= $range);
        return $min + $rnd;
}

function getToken($length=32){
    $token = "";
    $codeAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    $codeAlphabet.= "abcdefghijklmnopqrstuvwxyz";
    $codeAlphabet.= "0123456789";
    for($i=0;$i<$length;$i++){
        $token .= $codeAlphabet[crypto_rand_secure(0,strlen($codeAlphabet))];
    }
    return $token;
}

/**
 * Return a Page from searched Router
 *
 * return Page
 */
function getRouter($search){
  $pages = wire('pages');
  $sanitizer = wire('sanitizer');
  $search = explode(" ",$search);

  foreach($search as $string){
    $result = $pages->get("template=router, name|title={$sanitizer->pageName($string)}");
    if($result->id) break;
  }

  if($result instanceof NullPage) return false;

  return $result;
}

/**
 * Umkreissuche für Nodes
 * read: https://www.tutorials.de/threads/umkreis-um-eine-koordinate-berechnen-und-alle-koordinaten-in-db-suchen.217768/
 *
 * String latitude
 * String longitude
 * Int    dist      Distance
 *
 * return String Processwire Selector
 */
function umkreissuche($template, $latitude, $longitude, $dist = 5, $sort = true){
  // Return if the Template dosn't exists
  if(!wire('templates')->get("$template")) return;
  $t = wire('templates')->get("$template");
  // Return if Template didn't has latitude or longitude field!
  if(!$t->hasField('latitude')) return;

  $ursprungsbreite = str_replace(",", ".", $latitude);
  $ursprungslaenge = str_replace(",", ".", $longitude);

  $alpha = 180*$dist/(6371*3.14159);

  $geo1 = $ursprungsbreite-$alpha;
  $geo2 = $ursprungsbreite+$alpha;
  $geo3 = $ursprungslaenge-$alpha;
  $geo4 = $ursprungslaenge+$alpha;

  // Ungenaue suche
  $search = wire('pages')->find("template=$template, latitude>=$geo1, latitude<=$geo2, longitude>=$geo3, longitude<=$geo4");

  $result = new PageArray();

  $a = $ursprungsbreite/180*3.14159;
  $b = $ursprungslaenge/180*3.14159;

  $z = 1;
  foreach($search as $value){
    $c = str_replace(',','.',$value->latitude);
    $d = str_replace(',','.',$value->longitude);
    $c = $c/180*3.14159;
    $d = $d/180*3.14159;

    $e = sin($a)*sin($c);
    $f = cos($a)*cos($c)*cos($d-$b);
    $g = acos($e + $f);
    $h = $g * 6378.137;
    $ausgabe = sprintf("%01.3f", $h);
    if($ausgabe > $dist || $h == 0) {
      continue;
    }

    $value->set('dist', $ausgabe);
    $result->add($value);
  }

  if($sort){
    $result = $result->sort('dist');
  }
  return $result;
}

function getDistance($dist){
  $a = array( 'km'  => 1,
              'm'   => 0.001);

  foreach ($a as $metric => $key) {
    $b = $dist / $key;
    if (intval($b) >= 1){
      $b = round($b, 2);
      $ausgabe = "$b $metric";
      break;
    } else {
      $ausgabe = "> 1 m";
    }
  }

  return $ausgabe;
}

/**
 * Author : Ayman Hussein
 * http://stackoverflow.com/questions/1416697/converting-timestamp-to-time-ago-in-php-e-g-1-day-ago-2-days-ago
 */
function time_elapsed_string($ptime){
    $etime = time() - $ptime;

    if ($etime < 1){
        return '0 seconds';
    }

    $a = array( 365 * 24 * 60 * 60  =>  'year',
                 30 * 24 * 60 * 60  =>  'month',
                      24 * 60 * 60  =>  'day',
                           60 * 60  =>  'hour',
                                60  =>  'minute',
                                 1  =>  'second'
                );
    $a_plural = array( 'year'   => 'Jahre',
                       'month'  => 'Monate',
                       'day'    => 'Tage',
                       'hour'   => 'Stunden',
                       'minute' => 'Minuten',
                       'second' => 'Sekunden'
                );

    foreach ($a as $secs => $str){
        $d = $etime / $secs;
        if ($d >= 1){
            $r = round($d);
            return 'seit '. $r . ' ' . ($r > 1 ? $a_plural[$str] : $str);
        }
    }
}


/**
 * Find the progblem of deleted Nodes
 */
$this->pages->addHookBefore('deleted', $this, 'deletedNode');

function deletedNode() {
  $page = wire('page');
  $user = wire('user');

  wire('log')->save('delete', "$page wurde gelöscht $user");
}

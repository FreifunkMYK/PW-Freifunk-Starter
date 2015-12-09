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

 /**
  * getTag()
  *
  * @param  Tags $tags - instance of PageArray
  *         Limit $limit - limit of the output
  * @return String - html markup string of Tag list elements.
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
  $output = '';

  foreach($timeline as $post){
    $title = $post->date;
    $subheading = $post->title;
    $summary = $post->summary;
    $image = $post->images->first();
    $readmore = $post->httpUrl;
    $leftright = ($count % 2 != 0 ? "" : "class='timeline-inverted'");

    $output .= "<li $leftright>
                  <div class='timeline-image'>
                    <img class='img-circle img-responsive' src='{$image->size(156,156)->url}' alt='{$image->description}'>
                  </div>
                  <div class='timeline-panel'>
                    <div class='timeline-heading'>
                      <h4>$title</h4>
                      <h4 class='subheading'>$subheading</h4>
                    </div>
                    <div class='timeline-body'>
                      <p class='text-muted'>
                        $summary <a href='{$readmore}'>Weiterlesen</a>
                      </p>
                    </div>
                  </div>
                </li>";

      $count++;
  }

  return  "<section id='timeline' data-magellan-destination='timeline' class='info container'>
                <div class='row'>
                  <div class='columns large-12 text-center'>
                    <h2 class='section-heading'>Timeline</h2>
                    <h3 class='subheader'><small>Unser Weg zum freien Netz.</small></h3>
                  </div>
                </div>
                <div class='row'>
                  <div class='large-12 columns'>
                    <ul class='timeline'>
                      $output
                      <li class='timeline-inverted'>
                        <div class='timeline-image'>
                          <h4>Werde
                            <br>Teil unserer
                            <br>Community!</h4>
                          </div>
                        </li>
                      </ul><!-- #timelines -->
                    </div>
                  </div>
                </div>
              </section><!-- #timeline -->";

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

function listPages(PageArray $pages){
  $output = "";
  foreach($pages as $page){
    $output .= "<li><a href='{$page->httpUrl}'>{$page->title}</a></li>";
  }
  return $output;
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

/**********************************************
 * LDAP Helper functions
 * Soll in Zukunft zu in ein Module ausgegliedert werden
 *********************************************/

function make_ssha_password($password){
  mt_srand((double)microtime()*1000000);
  $salt = pack("CCCC", mt_rand(), mt_rand(), mt_rand(), mt_rand());
  $hash = "{SSHA}" . base64_encode(pack("H*", sha1($password . $salt)) . $salt);
  return $hash;
}

function ldap_helper_connect(){
  if(wire('config')->ldapDebugMode) ldap_set_option(NULL, LDAP_OPT_DEBUG_LEVEL, 7); // LDAP DebugMode
  $connection = ldap_connect(wire('config')->ldapHost, wire('config')->ldapPort); // Annahme: der LDAP Server befindet sich auf diesem Host
  if(wire('config')->ldapV3) ldap_set_option($connection, LDAP_OPT_PROTOCOL_VERSION, 3); // Set LDAP_PROTOCOL_VERSION
  return $connection;
}

function ldap_helper_root($connection){
  return ldap_bind($connection,"cn=".wire('config')->ldapMain.",dc=".wire('config')->ldapDOMAIN.",dc=".wire('config')->ldapDC, wire('config')->ldapPass);
}

function ldap_helper_registrade_user(Array $nuser){

  $username = $nuser["username"];

  // LDAP user anlegen
  $info["objectclass"][0] = "top";
  $info["objectclass"][1] = "person";
  $info["objectclass"][2] = "organizationalPerson";
  $info["objectclass"][3] = "inetorgperson";
  $info["cn"] = $nuser["firstname"];
  $info["sn"] = $nuser["lastname"];
  $info["givenName"] = $nuser["username"];
  $info["description"] = "ffmyk";

  $password = make_ssha_password($nuser["password"]);

  // If you have the plain text password instead, you could use:
  $info['userPassword'] = $password;

  $connect = ldap_helper_connect(); // Connect to LDAP Server
  if(!$connect) return false; // Connection Failed

  // bind mit passendem dn für aktulisierenden Zugriff
  $r= ldap_helper_root($connect);
  // Add User to the Database
  $ou = wire('config')->ldapOU;
  $dom = wire('config')->ldapDOMAIN;
  $dc = wire('config')->ldapDC;
  $r=ldap_add($connect, "uid=$username,ou=$ou,dc=$dom,dc=$dc", $info);

  // Verbindung schließen
  ldap_close($connect);

  // Registrierung erfolgreich
  return true;
}

<?php
include_once('scripts/node_migration.php');

/*$ffinfo = $modules->get('ffNodeInfo');
$e = new HookEvent;
$ffinfo->set_nodeinfo($e);*/

if($input->urlSegment2) throw new Wire404Exception(); // sobald mehr als ein urlSegment eingegeben wird 404!

if($input->urlSegment1){
  switch($input->urlSegment1){
    /**
     * list gibt eine Liste aller Nodes aus.
     */
    case 'list':
      // Finde und speichere alle Nodes sortiert nach dem subtitle
      $nodes = $pages->find('template=node, sort=-subtitle');

      // Init variable $tablerow for the Node Table.
      $tablerow = '';

      // Save each Node in a Row of the table
      foreach($nodes as $node){
        $tablerow .="<tr class='".($node->online == 1 ? "alert success" : "alert danger")."'>
                  <td><a href='$node->httpUrl'>$node->subtitle</a></td>
                  <td>$node->title</td>
                  <td>$node->latitude</td>
                  <td>$node->longitude</td>
                  <td>".($node->online == 1 ? "<span style='color:green'>online</span>" : "<span style='color:red'>offline</a>")."</td>
                  <td><a href='{$pages->get('/profile/')->httpUrl}{$node->operator->name}'>{$node->operator->name}</a></td>
                </tr>";
      }

      // Save the tablerow to the page Variable table.
      $page->table = $tablerow;

      // renderPage markup/list_node.inc
      $content = renderPage();
      break;
    /**
     * map shows a map from all nodes
     *
     * Aktuell außer Funktion!
     */
    case 'map':
      // Site settings
      $config->styles->add($config->urls->templates.'css/leaflet.css');
      $config->scripts->add($config->urls->templates.'js/leaflet-src.js');
      $fullwidth = true;

      $content= "<div id='map' style='width:100%' class='map'></div>";

      // Find all nodes with coordinate
      $nodes = $pages->find("template=node, latitude!=''");
      $marker = '';

      // create the node markers
      foreach($nodes as $node){
        $marker .= "L.circle([".str_replace(',','.',$node->latitude).", ".str_replace(',','.',$node->longitude)."], 10, {
                                  color:".($node->online == 1 ? "'blue'" : "'red'").",
                                  fillColor: ".($node->online == 1 ? "'blue'" : "'red'")."
                    }).addTo(map)
                      .bindPopup('{$node->subtitle}');";
      }

      // create the Map with Markers
      $script = "<script>
                var map = L.map('map').setView([50.3588, 7.48407], 10);
                var besuch = new Date().getHours();

                if (besuch < 22 || besuch > 6) {
                  // Tagesansicht
                  L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
                    maxZoom: 19,
                    attribution: '&copy; <a href=\"http://www.openstreetmap.org/copyright\">OpenStreetMap</a>'
                  }).addTo(map);
                } else {
                  // Nachtansicht
                  L.tileLayer('http://{s}.tiles.wmflabs.org/bw-mapnik/{z}/{x}/{y}.png', {
                    maxZoom: 19,
                    attribution: '&copy; <a href=\"http://www.openstreetmap.org/copyright\">OpenStreetMap</a>'
                  }).addTo(map);
                }

                // Geolokalisierung
                map.locate({setView: true, maxZoom: 16});

                // Zoom to current possition
                function onLocationFound(e) {
                  var radius = e.accuracy / 2;

                  L.circle(e.latlng, radius).addTo(map)
                      .bindPopup(\"You are within \" + radius + \" meters from this point\").openPopup();

                  L.circle(e.latlng, radius).addTo(map);
                }

                // sobald coordinaten gefunden wurden
                map.on('locationfound', onLocationFound);


                $marker

                map.on('click', function(e){
                  alert('Geoposition = ' + e.latlng);
                })
                $('#map').height($(window).height() - 205).width($(window).width());
                  map.invalidateSize();
                </script>";

      break;
    /**
     * add Nodes
     *
     * input:
     * 		mac  string  Macadresse eines Nodes
     * 		key  string  Key des Nodes
     */
    case 'add':
      // Speichere MAC und Key in der Session wenn vorhanden;
      if(isset($input->get->mac)) $session->mac = $input->get->mac;
      if(isset($input->get->key)) $session->key = $input->get->key;

      // Checken ob der Nutzer eingeloggt ist
      if(wire('user')->isLoggedin()){
        // Wurde das Formular abgesendet?
        if($input->post->submit){
          // Registriere den neuen Node
          switch (registerNode($input->post->mac, $input->post->key)) {
            case '-1':
              $content = "Der Node existiert bereits und du hast keine Rechte ihn zu ändern";
              break;
            case '0':
              $content = "Es ist ein Fehler aufgetreten, der Administrator wurde Informiet. Bitte versuche es zu einem späteren Zeitpunkt noch einmal.";
              break;
            case '1':
              // Zurück zur Privaten Routerliste
              $session->redirect($pages->get('/node/')->httpUrl, false);
              break;
            case '2':
              $content = "Dein Node wurde erfolgreich aktualisiert.";
              break;
            default:
              $content = "Es ist ein allgemeiner Fehler aufgetreten";
              break;
          }
        } else {
          // Gebe das Formular aus
          $content = renderPage('node_registration');
        }
      } else {
        $content = "<article><h2>Gesicherte Seite</h2>Bitte Anmelden oder Registrieren.</article>";
        // Speicher die URL um auf diese Seite zurück zu kehren!
        $session->redirect($session->redirectUrl, false);
      }
      break;
      /**
       * keys
       *
       * Serialisierte Ausgabe der Keys von registrierten Nodes
       */
      case 'keys':
          //if(!autorized($input->secret)) throw new Wire404Exception();
          $useMain = false;
          // Find all nodes and store the MAC and PublicKey to an array
          $router_new = $pages->find("template=node, key!=''")->explode(function($item) {
                          return array(
                            'MAC' => $item->title,
                            'PublicKey' => strtoupper($item->key)
                          );
                        });
          // get and merge the old and new keylist
          $router_old = file_get_contents("http://register.freifunk-myk.de/srvapi.php");
          $router_old = unserialize($router_old);
          $list = array_merge($router_old, $router_new);
          // create the output
          $router = array();
          $router = array_map("unserialize", array_unique(array_map("serialize", $list)));

          echo serialize($router);
        break;
        /**
         * import
         *
         * nur zur Migration der alten Node Datenbank. Kann gelöscht werden wenn alle Nodes migriert wurden.
         */
        case 'import':
          if(!wire('user')->isLoggedin()){
            $content = "<article><h2>Gesicherte Seite</h2>Bitte Anmelden oder Registrieren.</article>";
          } elseif (!wire('user')->authsuccess) {
            $content = "<article><h2>Authorisiere deinen Account</h2><p>Um deine Nodes zu importieren musst du deine E-Mail Adresse verifizieren.</p></article>";
          } else {
            $query = new mysqlMigrate();
            $nodes = $query->searchNodes(wire('user')->email);
            if(empty($nodes)) {
              $content= "<article>
                        <h2>Keine Nodes gefunden</h2>
                        <p>Es konnten keine Nodes gefunden werden.
                        Die Nodes werden mit Hilfe deiner E-Mail Adresse gesucht.
                        Bitte überprüfe das deine E-Mail Adresse die selbe wie
                        im alten System ist. Sollten weiterhin Probleme sein
                        dann sprich einfach einen der Administratoren an.</p>
                        </article>";
              break;
            }
            foreach($nodes as $node){
              $content .= registerNode($node['MAC'], $node['PublicKey']);
            }
            $content = "<h2>Nodes Hinzufügen</h2><ul>$content</ul>";
          }
        break;
        /**
         * update
         *
         * führt die Aktuallisierung der Node Daten aus dem Node JSON aus.
         *
         * Benötigt: Module ffNodeInfo
         */
        case 'update':
          if($input->get->key != "nre7u97ea") throw new WirePermissionException; // Without or with wrong key no Excption
          $useMain = false;
          $update = $modules->get('ffNodeInfo');
          $update->set_nodeinfo(new HookEvent);
          echo "Node Info Updated";
        break;
        /**
         * move
         *
         * Erste Version zum verschieben von Nodes von einem zum anderem Account.
         * Später auslagern in das Node module.
         */
        case 'move':
          function moveNodes($from, $to, $search, $do = false){
            $error = "";
            $return = "";
            // wenn es den Nutzer from nicht gibt
            if(!wire('users')->get("name|id=$from")) $error .= "Nutzer $from nicht vorhanden!<br>";
            // wenn es das Ziel nicht gibt
            if(!wire('users')->get("name|id=$to")) $error .= "Ziehl $to nicht vorhanden!<br>";
            // wenn es errors gibt dann return!
            if(!empty($error)) return $error;
            $from = wire('users')->get("name|id=$from");
            $to = wire('users')->get("name|id=$to");

            $moveNodes = wire('pages')->find("template=node, operator=$from->name, $search, sort=subtitle");

            // first check if the right Nodes are choosed
            $return .= "<h2>Folgende Nodes werden zu $to->name (ID: $to->id) übertragen:</h2>";
            foreach($moveNodes as $node){
              $return .= "$node->subtitle - $node->title - {$node->operator->name} <br>";
            }

            // confirm to move nodes
            if($do){
              $return .= "<br> Übertragung zu $to->name <br>";
              foreach ($moveNodes as $node) {
                $node->of(false);
                $node->operator = $to->id;
                $node->save();
                $node->of(true);
                $return .= "$node->subtitle gehört nun zu {$node->operator->name}<br>";
              }
              return "$return <p>Die Nodes sind erfolgreich Übretragen.</p>";
            }

            return "$return <p>Wenn diese Auflistung korrekt ist hänge ein \"&do=true\" an die URL.</p>";
          }

          $from = $sanitizer->name($input->get->from);
          $to = $sanitizer->name($input->get->to);
          $title = ( isset($input->get->title) ? $sanitizer->text($input->get->title) : "");
          $mac = ( isset($input->get->mac) ? $sanitizer->text($input->get->mac) : "");
          //$useMain = false;

          if(!wire('user')->isLoggedin() && !wire('user')->hasRole('manager|superuser')){
            $content = "Du hast nicht die notwendigen rechte!";
          } else {
            $filter = "";
            if(!empty($title)) $filter .= "subtitle*=$title";
            if(!empty($mac)) $filter .= (empty($filter) ? "mac=$mac" : ", mac=$mac");
            $content = moveNodes($from, $to, $filter);
            if($sanitizer->text($input->get->do) == "true") {
              $content = moveNodes($from, $to, $filter, true);
            }
          }

        break;
    default:
      // Alle nicht vorhandenen Segmente führen zu einem 404!
      throw new Wire404Exception();
  }

} else {
  $user = wire('user')->id;
  $nodes = $pages->find("operator=$user, template=node, sort=-subtitle");
  $table = '';

  foreach($nodes as $node){

    $table .="<tr class='".($node->online == 1 ? "alert success" : "alert danger")."'>
              <td><a href='$node->httpUrl'>$node->subtitle</a></td>
              <td>$node->title</td>
              <td>$node->node_firmware</td>
              <td>".($node->online == 1 ? "<span style='color:green'>online</span>" : "<span style='color:red'>offline</a>")."</td>
              <td>{$node->operator->name}</td>
            </tr>";
  }

  $page->table = $table;
  $content = renderPage('list_nodes_private');
}

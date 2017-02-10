<?php
function makeTable(PageArray $pages, $tableArray, $status = false){
  $tableHead = '';
  $tableBody = '';

  // Head
  foreach($tableArray as $key => $value){
    $tableHead .= "<th>$key</th>";
  }

  // Body
  foreach($pages as $p){
    $tableBody .= ($status ? "<tr class='".($p->online == 1 ? "alert success" : "alert danger")."'>" : "<tr>") ;
    foreach($tableArray as $value){
      $tableBody .= "<td>{$p->get($value)}</td>";
    }
    $tableBody .= "</tr>";
  }

  // Structur
  $table = "<table>
              <thead>
                <tr>
                $tableHead
                </tr>
              </thead>
                <tbody>
                $tableBody
                </tbody>
              </table>";

  return $table;
}

if($input->urlSegment1 == "pwreset") {
  //if(wire('user')->isLoggedin()) throw new WirePermissionException();
  include_once('passwordreset.php');
}

// Wenn inputsegment 1 nicht gesetzt ist dann leite auf den aktuellen Benutzer weiter.
// Nur eingeloggte User können Benutzerkonten ansehen
if(!wire('user')->isLoggedin() && $input->urlSegment1 != "pwreset") throw new Wire404Exception();
if(!$input->urlSegment1) $session->redirect("{$pages->get('/profile/')->url}{$user->name}");


if($input->urlSegment2 == "edit"){
  if($input->urlSegment1 != $user->name) $session->redirect("{$pages->get('/profile/')->url}{$user->name}/edit");
  // Get User Objekt from current User
  $u = $users->get("name={$user->name}");

  $t = new TemplateFile($config->paths->templates ."markup/profile_edit.inc");
  $t->set('firstname', $u->firstname);
  $t->set('lastname', $u->lastname);
  $t->set('email', $u->email);
  $t->set('publicKey', $u->public_key);

  $content = $t->render();
} else {

  #if($input->urlSegment3) throw new Wire404Exception();
  $u = $users->get("name={$sanitizer->name($input->urlSegment1)}");
  $page->title = "{$page->title} {$u->name}";
  $page->userID = $u->id;

  if($user instanceof NullPage) throw new Wire404Exception();

  // Nodes
  $page->nodes = $pages->find("template=node, operator={$u->id}");

  // IPs
  $page->ips = $pages->find("template=staticip, operator={$u->id}");

  $liste = "";
  $userlist = $users->find("start=0, name!='guest'");
  foreach($userlist as $uli){
    $liste .= "<li><a href='{$pages->get('/profile/')->httpUrl}{$uli->name}'>$uli->name</a></li>";
  }
  $page->userlist = "<ul>$liste</ul>";

  if(empty($content)) $content = ($user->id === $u->id ? renderPage('profile_private') : renderPage());

}

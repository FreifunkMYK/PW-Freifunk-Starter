<?php
function isActive(Page $page, Page $nav){
  if($page->id === $nav->id){
    return true;
  } else {
    // Check if Page is a Children from the Navpage
    $parents = $page->parents;
    foreach($parents as $parent){
      if($parent->id === $nav->id && $parent->id != 1){
        return true;
      }
    }
  }
  return false;
}
?>

<nav class="top-bar" data-topbar role="navigation">
  <ul class="title-area">
    <li class="name">
      <h2>
        <a href="<?=$homepage->httpUrl?>">
          <?php if($homepage->logo){ ?> <img src="<?php echo $homepage->logo->size(35,35)->url ?>"/> <?php } ?>
          <?=$homepage->headline?>
        </a>
      </h2>
    </li>
    <!-- Remove the class "menu-icon" to get rid of menu icon. Take out "Menu" to just have icon alone -->
    <li class="toggle-topbar menu-icon"><a href="#"><span>Menu</span></a></li>
  </ul>

  <section class="top-bar-section">
    <!-- Right Nav Section -->
    <ul class="right">
      <li <?php echo ( $page->id == 1 ? "class='active'" : ""); ?> >
        <a href="<?=$homepage->httpUrl?>">Home</a>
      </li>
      <li <?php echo (isActive($page, $pages->get("/blog/")) ? "class='active'" : ""); ?> >
        <a href="<?=$pages->get("/blog/")->url?>">Blog</a>
      </li>
      <li><a href="https://wiki.freifunk-myk.de">Wiki</a></li>
      <li <?php echo (isActive($page, $pages->get("/router/")) ? "class='active'" : "class=''"); ?>>
        <a href="<?=$pages->get("/router/")->url?>">Router</a>
      </li>
      <li><a href="https://status.freifunk-myk.de">Karte</a></li>
      <li><a href="https://wiki.freifunk-myk.de/wiki/anleitung">Anleitungen</a></li>
      <li class="has-dropdown">
        <?php if(!wire('user')->isLoggedin()){ ?>
          <a href="#" data-dropdown="signin">Anmelden</a>
        <?php }else{ ?>
          <a href="#">Benutzer</a>
          <ul class="dropdown">
            <li>
              <a href="<?= $pages->get('/profile/')->httpURL ?><?= $user->name ?>"><i class='fa fa-user'></i> Profil</a>
            </li>
            <li>
              <a href="<?= $pages->get("/node/")->httpURL ?>"><i class='fa fa-wifi'></i> Nodes</a>
            </li>
            <li>
              <a href="<?= $pages->get('/services/')->httpURL ?>"><i class='fa fa-server'></i> Services</a>
            </li>
            <?php if(wire('user')->hasPermission('page-create')) { ?>
              <li>
                <a href="<?=$pages->get(1)->httpUrl?>processwire/page/add/?parent_id=1025"><i class='fa fa-plus'></i> Neuer Blogpost</a>
              </li>
            <?php  } ?>
            <?php if(wire('user')->hasRole('superuser') || wire('user')->hasRole('admin') || wire('user')->hasRole('manager')){ ?>
              <li>
                <a href="<?=$pages->get(1)->httpUrl?>processwire"><i class='fa fa-cogs'></i> Admin</a>
              </li>
            <?php }
            //if($page->createdUser->id == wire('user')->id) {
            if($page->editable()) {?>
              <li>
                <a href="<?=$pages->get(1)->httpUrl?>processwire/page/edit/?id=<?=$page->id?>"><i class='fa fa-pencil'></i> Edit Page</a>
              </li>
            <?php  } ?>
            <li>
              <?php // Handle logouts
                    if($input->get->logout == 1) {
                      $session->logout();
	                    $session->redirect($page->path);
                    } ?>
              <a href="?logout=1"><i class='fa fa-lock'></i> Logout</a>
            </li>
          </ul>
        <?php } ?>
      </li>
    </ul>
  </section>
</nav>
<?php if(!wire('user')->isLoggedin()){ ?>
<div id="signin" class="f-dropdown small content" data-dropdown-content aria-autoclose="false">
    <form id="formLogin" action='./' method='post'>
      <div >
        <input name="user" id="user" placeholder="Benutzername" type="text" />
        <input name="pass" id="pass" placeholder="Passwort" type="password" />
      </div>
      <div >
        <button type="submit" id="btnLogin" name='submit' value='Login' class="btn btn-default">Login</button>
        <button type="submit" id="btnRegister" formaction="<?php echo $pages->get("/registration/")->httpUrl; ?>" class="btn btn-default">Registrieren</button>
      </div>
    </form>
    <a href="<?=$pages->get("template=password-reset")->url?>">Password vergessen?</a>
</div>
<?php } ?>

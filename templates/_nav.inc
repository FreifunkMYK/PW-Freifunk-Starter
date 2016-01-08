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
      <h2><a href="<?=$homepage->httpUrl?>">Freifunk-MYK</a></h2>
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
      <li><a href="#">Wiki</a></li>
      <li <?php echo (isActive($page, $pages->get("/router/")) ? "class='active has-dropdown'" : "class='has-dropdown'"); ?>>
        <a href="<?=$pages->get("/router/")->url?>">Router</a>
        <ul class="dropdown">
          <li><a href="<?=$pages->get("/router/")->url?>">Firmware</a></li>
        </ul>
      </li>
      <li><a href="#">Karte</a></li>
      <li class="has-dropdown">
        <?php if(!wire('user')->isLoggedin()){ ?>
          <a href="#" data-dropdown="signin">Anmelden</a>
        <?php }else{ ?>
          <a href="#">Benutzer</a>
          <ul class="dropdown">
            <li>
              <a href="<?= $pages->get(8544)->httpURL ?>"><i class='fa fa-user'></i> Profil</a>
            </li>
            <li>
              <a href="<?= $pages->get(8544)->httpURL ?>"><i class='fa fa-code-fork'></i> Entwürfe</a>
            </li>
            <li>
              <a href="<?= $pages->get('title|name=lesezeichen')->httpURL ?>"><i class='fa fa-bookmark'></i> Lesezeichen</a>
            </li>
            <?php if(wire('user')->hasRole('superuser') || wire('user')->hasRole('manager')){ ?>
              <li>
                <a href="<?=$pages->get(1)->httpUrl?>processwire"><i class='fa fa-cogs'></i> Admin</a>
              </li>
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
        <a href="<?php $homepage ?>/registration/"><button type="button" id="btnRegister" class="btn btn-default">Registrieren</button></a>
      </div>
    </form>
    <a href="<?=$pages->get("template=password-reset")->url?>">Password vergessen?</a>
</div>
<?php } ?>

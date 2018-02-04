<?php

if(!$useMain) return;

// Set Hompage to use in Theme
$homepage = $pages->get('/');

// Set settings to use in Theme
$settings = $page->get('template=site-setting');

// determine what the ever important browser <title> tag should be
if($page->brower_title) $browserTitle = $page->browser_title;
  else if($page === $homepage) $browserTitle = $page->headline;
  else $browserTitle = $page->title . '&bull;' . $homepage->headline;

// add our stylesheet
#$config->styles->add($config->urls->templates . 'stylesheets/app.css');
$config->styles->add($config->urls->templates.'css/app.css');
#$config->styles->add('https://cdnjs.cloudflare.com/ajax/libs/foundicons/3.0.0/foundation-icons.css');
#$config->styles->add('https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css');

// add our javascripts
$config->scripts->add($config->urls->templates.'js/app-dist.js');

/********************************
* Hendle Login
*******************************/
if(!wire('user')->isLoggedin()){
	if($input->post->user && $input->post->pass) {
		$u = $sanitizer->username($input->post->user);
		$pass = $input->post->pass;

		if($session->login($u, $pass)) {
			// login successful
			if($session->redirectUrl){
        $session->redirect($session->redirectUrl, false);
        $session->remove('redirectUrl');
      } else {
			   $session->redirect($page->path, false);
       }
      if($session->countlogintry){
        $session->remove('countlogintry');
        $session->remove('logintrytime');
      }
		}  else {
      // count try for logging in!
      $logintrynumber = ($session->countlogintry ? $session->countlogintry + 1 : 1);
      $session->set("logintrytime", time());
      $session->set("countlogintry", $logintrynumber);
			$session->login_error = '<strong>Login fehlgeschlagen!</strong> Bitte versuche es noch einmal oder benutze die \'Passwort vergessen\' Funktion.';
		}
	}
}

?>

<!doctype html>
<html class="no-js" lang="de">
<head>
  <?php
    if($modules->isInstalled("AllInOneMinify")){
      foreach($config->styles as $key => $file) $stylesheets[] = $file;
      ?>
      <link rel="stylesheet" href="<?php echo AllInOneMinify::CSS($stylesheets); ?>"> <?php
    } else {
      // Include the style Files
      foreach($config->styles as $key => $file) echo "\n\t<link rel='stylesheet' type='text/css' href='$file'>";
    }
  ?>
  <title><?php echo $page->get('headline|title') . " &middot; " . $homepage->headline; ?></title>

  <link rel="icon" type="image/png" href='<?= $config->urls->templates. 'img/favicon.png' ?>'>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0">

</head>
<body>
  <header id="header" class="fixed contain-to-grid">
    <?php include_once('_nav.inc'); ?>
  </header><!-- #sticky -->

  <?php if($page->id != 1){ ?>
  <div class="contain-breadcrumbs">
    <ul class="breadcrumbs">
      <?php
        foreach($page->parents("template!=home")->append($page) as $parent) {
            echo ($page->id === $parent->id ? "<li class='current'><a href='{$parent->url}'>{$parent->title}</a></li>" : "<li><a href='{$parent->url}'>{$parent->title}</a></li>");
        }
        ?>
    </ul>
  </div>
  <?php } ?>

  <main id="container" class="<?php echo $page->template .' id-'. $id; ?>">
    <?php
      if($input->post->user && $input->post->pass) {
        echo "<div class='alert-box warning' data-alert>" . $session->login_error . "<a href='#' class='close'>&times;</a></div>";
        }
      ?>
    <?php
    // Homepage (Landingpage) wird direkt im container
    echo ($page->id === 1 || $fullwidth == true ? $content :   '<div id="content" class="row">'.$content.'</div>');
    ?>
  </main>

  <footer id="footer" class="footer">
    <div class="row">
      <div class="small-12 medium-4 medium-push-8 columns">
        <ul class="inline-list social">
          <li><a href="https://twitter.com/freifunkmyk"><i class="fa fa-2x fa-twitter-square"></i></a></li>
          <li><a href="https://github.com/FreifunkMYK"><i class="fa fa-2x fa-github-square"></i></a></li>
          <li><a href="https://www.youtube.com/channel/UC551zNU8hsG5mBRN5LUuqtg"><i class="fa fa-2x fa-youtube-square"></i></a></li>
	  <li><a href="<?=$pages->get("/kontakt/")->url?>"><i class="fa fa-2x fa-envelope"></i></a></li>
        </ul>
        <p class="copywrite">&copy; <?=date("Y")?> <?=$homepage->headline?></p>
      </div>
      <div class="small-12 medium-8 medium-pull-4 columns">
        <p>
          <?php //if($user->id == $page->createdUser->id){ echo "true";}?>
        </p>
        <ul class="inline-list">
          <li><a href="<?=$homepage->httpUrl?>">Home</a></li>
          <li><a href="<?=$pages->get("/blog/")->url?>">Blog</a></li>
          <li><a href="<?=$pages->get("/about/")->url?>">About</a></li>
          <li><a href="https://wiki.freifunk-myk.de/wiki/faq">Faq</a></li>
          <li><a href="<?=$pages->get("/kontakt/")->url?>">Kontakt</a></li>
        </ul>
        <p class="copywrite">Erstellt mit <a href="http://de.processwire.com/">ProcessWire</a> und <a href="http://foundation.zurb.com/">Foundation Zurb</a>. Zu finden auf <a href="https://github.com/FreifunkMYK/PW-Freifunk-Starter">GitHub</a>.
      </div>
    </div>
    <div class="row">
      <div class="small-12 medium-2 medium-push-10 columns">
      </div>
      <div class="small-12 medium-10 medium-pull-2 columns">
      </div>
    </div>
  </footer>

  <?php
	 #if($modules->isInstalled("AllInOneMinify")){
	 	if(false){
		foreach($config->scripts as $key => $file) $scriptfiles[] = str_replace($config->urls->templates, "", $file);
      	print_r($scriptfiles);?>
      		<script src="<?php echo AIOM::JS($scriptfiles); ?>"> </script><?php
    	} else {
      		// Include the style Files
      		foreach($config->scripts as $file) echo "\n\t<script src='$file'></script>";
    }
  ?>
  <script>
    /*(function() {
      var s = document.createElement('script');
      s.type = 'text/javascript';
      s.src = '<?=$config->urls->templates?>js/app-dist.js';
      var x = document.getElementsByTagName('script')[0];
      x.parentNode.insertBefore(s, x);
    })();

    function loadCSS(href){
      var ss = window.document.createElement('link'),
          ref = window.document.getElementsByTagName('head')[0];

      ss.rel = 'stylesheet';
      ss.href = href;

      // temporarily, set media to something non-matching to ensure it'll
      // fetch without blocking render
      ss.media = 'only x';

      ref.insertBefore(ss, ref.firstChild);

      setTimeout( function(){
        // set media back to `all` so that the stylesheet applies once it loads
        ss.media = 'all';
      },0);
    }
    loadCSS('<?php echo $config->urls->templates.'css/app.css'; ?>'); */

  	// Foundation JavaScript
  	// Documentation can be found at: http://foundation.zurb.com/docs
  	$(document).foundation();
  </script>
  <?=(isset($script) ? $script : "")?>
  <noscript>
    <script src="<?=$config->urls->templates?>js/app-dist.js"></script>
    <link rel="stylesheet" href="<?php echo $config->urls->templates.'css/app.css';?>">
  </noscript>
</body>
</html>

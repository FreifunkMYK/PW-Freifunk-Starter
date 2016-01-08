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
$config->styles->add($config->urls->templates.'stylesheets/app.css');
$config->styles->add('https://cdnjs.cloudflare.com/ajax/libs/foundicons/3.0.0/foundation-icons.css');
$config->styles->add('https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css');

// add our javascripts
$config->scripts->prepend($config->urls->templates.'bower_components/modernizr/modernizr.js');
$config->scripts->add($config->urls->templates.'bower_components/jquery/dist/jquery.min.js');
$config->scripts->add($config->urls->templates.'bower_components/foundation/js/foundation.min.js');
$config->scripts->add($config->urls->templates.'js/app.js');

/********************************
* Hendle Login
*******************************/
if(!wire('user')->isLoggedin()){
	if($input->post->user && $input->post->pass) {
		$u = $sanitizer->username($input->post->user);
		$pass = $input->post->pass;

		if($session->login($u, $pass)) {
			// login successful
			$session->redirect($page->path);
		}  else {
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

  <link rel="icon" type="image/png" href='<?= $config->urls->templates. 'img/favicon.png' ?>'>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0">

</head>
<body>
  <header class="fixed contain-to-grid">
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

  <section id="container" class="<?php echo $page->template .' id-'. $id; ?>">
    <?php
      if($input->post->user && $input->post->pass) {
        echo "<div class='alert-box warning' data-alert>" . $session->login_error . "<a href='#' class='close'>&times;</a></div>";
        }
      ?>
    <?php
    // Homepage (Landingpage) wird direkt im container
    echo ($page->id === 1 ? $content :   '<div id="content" class="row">'.$content.'</div>');
    ?>
  </section>

  
  <footer class="footer">
    <div class="row">
      <div class="small-12 medium-4 medium-push-8 columns">
        <ul class="inline-list social">
          <li><a href="https://twitter.com/freifunkmyk"><i class="fa fa-twitter"></i></a></li>
          <li><a mailto="info@freifunk-myk.de"><i class="fa fa-envelope"></i></a></li>
          <li><a href="https://github.com/FreifunkMYK"><i class="fa fa-github"></i></a></li>
        </ul>
        <p class="copywrite">Design by kreativmonkey with foundation</p>
      </div>
      <div class="small-12 medium-8 medium-pull-4 columns">
        <a class="ff-logo regular" href="<?=$pages->get("/")->httpUrl?>">Freifunk-Myk</a>
        <ul class="inline-list">
          <li><a href="#">Home</a></li>
          <li><a href="#">Blog</a></li>
          <li><a href="#">About</a></li>
          <li><a href="#">Faq</a></li>
          <li><a href="#">Kontakt</a></li>
        </ul>
        <p class="copywrite">Copywrite not copywrite © <?=date("Y")?></p>
      </div>
    </div>
  </footer>

  <?php
	 #if($modules->isInstalled("AllInOneMinify")){
      	if(false){
		foreach($config->scripts as $key => $file) $scriptfiles[] = str_replace($config->urls->templates, "", $file);
      	print_r($scriptfiles);?>
      		<script src="<?php echo AIOM::JS($scriptfiles); ?>"> <?php
    	} else {
      		// Include the style Files
      		foreach($config->scripts as $file) echo "\n\t<script src='$file'></script>";
    }
  ?>

</body>
</html>

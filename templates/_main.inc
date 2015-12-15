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
$config->styles->add($config->urls->templates . 'stylesheets/app.css');
$config->styles->add('https://cdnjs.cloudflare.com/ajax/libs/foundicons/3.0.0/foundation-icons.css');
$config->styles->add('https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css');

// add our javascripts
$config->scripts->prepend($config->urls->templates . 'bower_components/modernizr/modernizr.js');
$config->scripts->add($config->urls->templates . 'bower_components/jquery/dist/jquery.min.js');
$config->scripts->add($config->urls->templates . 'bower_components/foundation/js/foundation.min.js');
$config->scripts->add($config->urls->templates . 'js/app.js');
$config->scripts->add($config->urls->templates . 'js/foundation/foundation.magellan.js');


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
      foreach($config->styles as $key => $file) $stylearray[] = $file;
      ?>
      <link rel="stylesheet" href="<?php echo AllInOneMinify::CSS(
            $stylearray
        ); ?>"> <?php
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
  </header><!--#sticky-->

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
    // Homepage (Landingpage) wird direkt im container
    echo ($page->id === 1 ? $content :   '<div id="content" class="row">'.$content.'</div>');
    ?>
  </section>

  <footer class="footer">
    <div class="row">
      <div class="small-12 medium-6 medium-push-6 columns">
        <p class="logo show-for-small-only"><i class="fi-target"></i> FIGHT CLUB</p>
        <form class="footer-form">
          <div class="row">
            <div class="medium-9 medium-push-3 columns">
              <label>
                <label for="email" class="contact">Contact Us</label>
                <input type="email" id="email" placeholder="Email Address" />
              </label><br/>
              <label>
                <textarea rows="5" id="message" placeholder="Message"></textarea>
              </label><br/>
              <button class="submit" type="submit" value="Submit">Send</button>
            </div>
          </div>
        </form>
      </div>
      <div class="small-12 medium-6 medium-pull-6 columns">
        <p class="logo hide-for-small-only"><i class="fi-target"></i> Freifunk-Myk</p>
        <p class="footer-links">
          <a href="#">Home</a>
          <a href="#">Blog</a>
          <a href="#">Pricing</a>
          <a href="#">About</a>
          <a href="#">Faq</a>
          <a href="#">Contact</a>
        </p>
        <p class="copywrite">Copywrite not copywrite © 2015</p>
      </div>
    </div>
  </footer>

  <?php
  // Render Scriptfiles
  foreach($config->scripts as $file) echo "<script src='$file'></script>";
  ?>

</body>
</html>

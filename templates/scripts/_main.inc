<?php

if(!useMain) return;

// Set Hompage to use in Theme
$homepage = $page->get('/');

// Set settings to use in Theme
$settings = $page->get('template=site-setting');

// determine what the ever important browser <title> tag should be
if($page->brower_title) $browserTitle = $page->browser_title;
  else if($page === $homepage) $browserTitle = $page->headline;
  else $browserTitle = $page->title . '&bull;' . $homepage->headline;

// add our stylesheet
$config->styles->add($config->urls->templates . 'stylesheets/app.css');
$config->styles->add('http://cdnjs.cloudflare.com/ajax/libs/foundicons/3.0.0/foundation-icons.css');
$config->styles->add('https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css');

// add our javascripts
$config->scripts->prepend($config->urls->templates . 'bower_components/modernizr/modernizr.js');
$config->scripts->add($config->urls->templates . 'bower_components/jquery/dist/jquery.min.js');
$config->scripts->add($config->urls->templates . 'bower_components/foundation/js/foundation.min.js');
$config->scripts->add($config->urls->templates . 'js/app.js');


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
    // Include the style Files
    foreach($config->styles as $key => $file) echo "\n\t<link rel='stylesheet' type='text/css' href='$file'>";
  ?>

  <link rel="icon" type="image/png" href='<?= $config->urls->templates. 'img/favicon.png' ?>'>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0">

</head>
<body>

  <header class="sticky contain-to-grid">
    <nav class="top-bar" data-topbar role="navigation">
      <ul class="title-area">
        <li class="name">
          <h2><a href="<?=$hompage->httpUrl?>">Freifunk-MYK</a></h2>
        </li>
        <!-- Remove the class "menu-icon" to get rid of menu icon. Take out "Menu" to just have icon alone -->
        <li class="toggle-topbar menu-icon"><a href="#"><span>Menu</span></a></li>
      </ul>

      <section class="top-bar-section">
        <!-- Right Nav Section -->
        <ul class="right">
          <li class="active">
            <a href="<?=$homepage->httpUrl?>">Home</a>
          </li>
          <li><a href="blog-list.html">Blog</a></li>
          <li><a href="#">Wiki</a></li>
          <li class="has-dropdown"><a href="router-liste.html">Router</a>
            <ul class="dropdown">
              <li><a href="#">Firmware</a></li>
            </ul>
          </li>
          <li><a href="#">Karte</a></li>
          <li class="has-dropdown">
            <a href="#">Benutzer</a>
            <ul class="dropdown">
              <li><a href="#">First link in dropdown</a></li>
              <li class="active"><a href="#">Active link in dropdown</a></li>
            </ul>
          </li>
        </ul>
      </section>
    </nav>
  </header><!--#sticky-->

  <div id="container" class="<?=$page->template?> <?=$id?>">
    <?php
    echo $content;
    ?>
  </div>

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

  <!-- Zur Optimierung werden diese scripte und CSS files später hier geladen!
  <link href="http://cdnjs.cloudflare.com/ajax/libs/foundicons/3.0.0/foundation-icons.css" rel="stylesheet">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css">

  <script src="bower_components/jquery/dist/jquery.min.js"></script>
  <script src="bower_components/foundation/js/foundation.min.js"></script>
  <script src="js/app.js"></script>
  -->

</body>
</html>

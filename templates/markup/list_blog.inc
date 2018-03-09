<?php
/*******************
 * List Posts in Blog
 *******************/
 ?>
<div id='article' class='blog-list large-9 columns'>
  <?=$posts?>
</div><!-- #article -->
<div id='sidebar' class='large-3 columns'>
  <div class='panel'>
    <h5>Mitmachen</h5>
    <p>
      Unterstütze Freifunk und stelle deinen eigenen Freifunk-Router
      auf um das Netz zu erweitern.
    </p>
    <a href="<?=$pages->get('/')->httpUrl?>#mitmachen" class='button expand'>Informier dich jetzt!</a>
  </div>
  <?php echo renderNewNodesList(); ?>
</div>

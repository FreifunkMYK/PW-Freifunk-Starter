<?php
/*******************
 * Post Page Markup to Render posts
 *******************/
 $image = (count($page->images) ? "<img class='responsive' src='{$page->images->first()->size(300,200)->url}'></img>" : "");
 ?>
<div id='article' class='blog-list large-9 columns'>
  <article id='article-<?=$page->id?>' class='row article'>
    <div class='medium-3 columns'>
      <?=$image?>
    </div>
    <div class='medium-9 columns'>
      <h4 class='tobheader'><small><?php echo strftime('%d %b %Y', $page->getUnformatted('date'))?></small></h4>
      <h1><?=$page->title?></h1>
      <p>
        <?=$page->get('body|summary')?>
      </p>
      <hr />
      <span class="author"><i class="fa fa-user"></i> <a href="<?=$page->authorURL?>"><?=$page->authorName?></a></span>
    </div>
  </article><!-- #article-7 -->
</div><!-- #article -->
<div id='sidebar' class='large-3 columns'>
  <div class='panel'>
    <h5>Mitmachen</h5>
    <p>
      Unterstütze Freifunk und stelle deinen eigenen Freifunk-Router
      auf um das Netz zu erweitern.
    </p>
    <a href='<?=$pages->get('/')->httpUrl ?>#mitmachen' class='button expand'>Informier dich jetzt!</a>
  </div>
  <?php echo renderNewNodesList(); ?>
</div>

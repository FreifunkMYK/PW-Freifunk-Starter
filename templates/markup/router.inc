<article id='article' class='large-12 columns'>
  <div class='row'>
    <div class='large-9 columns'>
      <h1><?=$page->parent->title?> <?=$page->title?></h1>
      <p>
      <?=$page->body?>
      </p>
      <hr>
      <?=renderInfoBlocks();?>
      <h2>Firmware</h2>
      <p>
        Im Folgenden findest du die Firmware zum Router. Für den produktiven - also möglichst ausfallsicheren - Betrieb solltest du die Stable Firmware nutzen. Diese wird vor der Veröffentlichung getestet und enthält meistens keine Fehler mehr.
      </p>
      <?=$this->firmware?>
    </div><!-- #columns large-9 -->
    <div id='router-infobox' class='large-3 columns'>
      <div class='panel'>
        <img class='responsive' src='<?php echo (count($page->image) ? $page->image->first()->size(250,250)->url : 'https://placehold.it/250x250?text=No Image'); ?>'> </img>

        <hr>
        Hersteller: <a href='<?=$page->parent->website?>'><?=$page->parent->title?></a><br/>
        OpenWrt: <a href='https://wiki.openwrt.org/toh/<?=$page->parent->name?>/<?=$page->name?>"><?=$page->title?></a><br/>
        <hr>
        <h4>Features</h4>
        <ul class='features'>
          <?php echo getTag($page->features); ?>
        </ul>
      </div><!-- #panel -->
    </div><!-- #router-infobox -->
  </div><!-- #row -->
</article><!-- #article -->

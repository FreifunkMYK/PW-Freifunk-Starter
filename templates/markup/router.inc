<article id='article' class='large-12 columns'>
  <div class='row'>
    <div class='large-9 columns'>
      <h1><?=$page->get('headline|title')?></h1>
      <?php if(wire('user')->hasPermission('page-edit', $page)){ ?>
        <a class="edit" href="<?=$pages->get(1)->httpUrl?>processwire/page/edit/?id=<?=$page->id?>"><i class="fa fa-pencil"></i></a>
      <?php } ?>
      <p>
      <?=$page->body?>
      </p>
      <hr>
      <?=renderInfoBlocks();?>
      <h2>Firmware</h2>
      <p>
        Im Folgenden findest du die Firmware zum Router.
        Für den produktiven - also möglichst ausfallsicheren - Betrieb solltest du die Stable Firmware nutzen.
        Diese wird vor der Veröffentlichung getestet und enthält meistens keine Fehler mehr.
        Eine Anleitung zum Flashen findest du in unserem <a href="https://wiki.freifunk-myk.de/wiki/anleitung">Wiki</a>.
      </p>
      <?=$page->firmwareTable?>
    </div><!-- #columns large-9 -->
    <div id='router-infobox' class='large-3 columns'>
      <div class='panel'>
        <img class='responsive' src='<?php echo (count($page->image) ? $page->image->first()->size(250,250)->url : 'https://placehold.it/250x250?text=No Image'); ?>'> </img>

        <hr>
        Hersteller: <?php if($page->parent->website){ ?>
                      <a href='<?=$page->parent->website?>'><?=$page->parent->title?></a>
                    <?php } else { ?>
                      <?=$page->parent->title?>
                    <?php } ?><br/>
        OpenWrt: <a href="https://wiki.openwrt.org/toh/<?=strtolower($page->parent->title)?>/<?=strtolower($page->title)?>"><?=$page->title?></a><br />
        <hr>
        <h4>Hardware</h4>
        <?=($page->ram ? "RAM: {$page->ram} <br/>" : "")?>
        <?=($page->flash ? "Flash: {$page->flash} <br />" : "")?>
        <hr>
        <h4>Features</h4>
        <ul class='features'>
          <?php echo getTag($page->features); ?>
        </ul>
      </div><!-- #panel -->
    </div><!-- #router-infobox -->
  </div><!-- #row -->
</article><!-- #article -->

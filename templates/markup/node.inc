<article id='article' class='large-9 columns'>
  <h1><?=$page->get('subtitle|title')?></h1>
  <table style="width:100%">
    <tr>
      <th>Name</th>
      <td><?=$page->subtitle?></td>
      <?php if($page->createdUser == $user && $input->get->delete){ ?>
        <div class="panel alert"> Bist du sicher das du diesen Node löschen möchtest? Dies kannst du nicht rückgängig machen.
          <form action="./" method="post">
            <input type="checkbox" name="delete" value="node"> Ich möchte den Node <?=$page->get('subtitle|title')?> löschen.<br>
            <button class="btn alert" type="submit" value="submit">Unwiederruflich Löschen</button>
            <button class="btn secondary" type="cancle" value="cancle">Abbrechen</button>
          </form>
        </div>
      <?php } ?>
    </tr>
    <tr>
      <th>MAC</th>
      <td><?=$page->title?></td>
    </tr>
    <tr>
      <th>IPv6</th>
      <td><a href="http://[<?=$page->ipv6?>]/"><?=$page->ipv6?></a></td>
    </tr>
    <tr>
      <th>Hardware</th>
      <td>
        <?php
          $router = getRouter($page->node_hardware);
          if($router){
            echo "<a href='{$router->httpUrl}'>$page->node_hardware</a>";
          } else {
            echo $page->node_hardware;
          }
        ?>
      </td>
    </tr>
    <tr>
      <th>Firmware</th>
      <td><?=$page->node_firmware?></td>
    </tr>
    <tr>
      <th>Status</th>
      <td><?=($page->online ? "<span style='color:green'>online</span>" : "<span style='color:red'>offline</span> $page->losttime")?></td>
    </tr>
    <tr>
      <th>Map</th>
      <td><a href='http://status.freifunk-myk.de/#!v:m;n:<?=strtolower(str_replace(":", "", $page->title))?>'><?=$page->address?></a></td>
    </tr>
    <?php if(wire('user')->isLoggedin()){ ?>
    <tr>
      <th>Betreiber</th>
      <td><a href='<?=$page->createdUser->httpUrl?>'><?=$page->createdUser->get('name|title')?></a></td>
    </tr>
    <?php } ?>
  </table>
  <div id='map' style='width:100%; height:200px' class='map'></div>

  <?php if($page->createdUser == $user){ ?>
    <a href="?delete=true""><button class="btn alert"><i class="fa fa-close"></i> Delete</button></a>
  <?php } ?>

</article><!-- #article -->
<aside id="sidebar" class="large-3 columns">
  <h4>Nodes in der Nähe (2km)</h4>
  <ul class='node-list'>
    <?php   $nearnodes = umkreissuche("node", $page->latitude, $page->longitude, 2);
            if($nearnodes){
              foreach ($nearnodes as $node) { ?>
            <li>
              <i class='fa fa-wifi' style='color:<?=($node->online ? 'green' : 'red')?>'></i> <a href='<?=$node->httpUrl?>'><?=$node->get('subtitle|title')?> </a><br>
              <span class='node-address'><i class='fa fa-fw'></i> <?=getDistance($node->dist)?> entfernt</span>
            </li>
    <?php  } } else { ?>
            <p>Keine Nodes gefunden!</p>
    <?php }  ?>
  </ul>

  <?php echo renderNewNodesList(); ?>
</aside>

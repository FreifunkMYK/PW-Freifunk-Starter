<article id='article' class='medium-8 small-12 columns'>
  <h1><?=$page->title?>s <a title="Node hinzufügen" class="right" href="<?=$pages->get('/node/')->httpUrl?>add"><i class='fa fa-plus-circle'></i></a></h1>
  <table class='node-list'>
    <thead>
      <tr>
        <th>Name</th>
        <th>MAC</th>
        <th>Firmware</th>
        <th>Kommentar</th>
        <th>Status</th>
        <th>Option</th>
      </tr>
    </thead>
    <tbody>
      <?=$page->table?>
    </tbody>
  </table>
  <p>Wenn du deine Nodes aus vom Alten Noderegister übernehmen möchtest rufe bitte folgende Seite auf: <a href="<?=$pages->get('/node/')->httpUrl?>import">https://www.ffmyk.de/node/import</a></p>
</article><!-- #article -->

<article id='article' class='medium-8 small-12 columns'>
  <h1><?=$page->title?> <a title="Node hinzufügen" class="right" href="<?=$pages->get('/static-ip/')->httpUrl?>add"><i class='fa fa-plus-circle'></i></a></h1>
  <table class='node-list'>
    <thead>
      <tr>
        <th>Name</th>
        <th>IP</th>
        <th>User</th>
      </tr>
    </thead>
    <tbody>
      <?=$page->table?>
    </tbody>
  </table>
</article><!-- #article -->

<article id='article' class='large-12 columns'>
  <h1>Add Node</h1>
  <p>
    Füge den Node zu deinem Profil hinzu damit er sich mit unseren Servern verbinden kann.
    Nach ca. 5 Minuten erscheint dein Node mit allen Informationen in der <a href="<?=$page->httpUrl?>list/">Node Liste</a>.
  </p>
    <p>Wenn du deine Nodes aus vom Alten Noderegister übernehmen möchtest rufe bitte folgende Seite auf: <a href="<?=$pages->get('/node/')->httpUrl?>import">https://www.ffmyk.de/node/import</a></p>

  <form class='omb_nodeAdd' data-abide action='./add' accept-charset='UTF-8' autocomplete='off' method='post'>
      <div class='row collapse'>
        <div class='small-6 columns'>
          <input type='text' class='form-control' required pattern='([0-9A-Fa-f]{2}[:]){5}([0-9A-Fa-f]{2})' name='mac' placeholder='Example: E8:DD:08:9C:A7:78' <?php if($session->mac) echo "value='$session->mac'"?>>
          <small class='error'>Bitte beachte die Konvention!</small>
        </div>
        <div class='small-6 columns'>
          <input type='text' class='form-control' name='key' required pattern='([A-Za-z0-9]{64})' placeholder='Public Key' <?php if($session->key) echo "value='$session->key'"?>>
          <small class='error'>Der PublicKey ist ein Pflichtfeld.</small>
        </div>
      </div>

      <button class='button' type='submit' name='submit' value='add'>Hinzufügen</button>
  </form>
</article>

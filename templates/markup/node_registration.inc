<article id='article' class='large-12 columns'>
  <h1>Add Node</h1>
  <p>
    Füge den Node zu deinem Profil hinzu damit er sich mit unseren Servern verbinden kann.
    Nach ca. 5 Minuten erscheint dein Node mit allen Informationen in der <a href="<?=$page->httpUrl?>list/">Node Liste</a>.
  </p>
  <form class='omb_nodeAdd' data-abide action='./add' accept-charset='UTF-8' autocomplete='off' method='post'>
      <div class='row collapse'>
        <div class='small-6 columns'>
          <input type='text' class='form-control' required pattern='([0-9A-Z]{2}[:]){5}([0-9A-Z]{2})' name='mac' placeholder='Example: E8:DD:08:9C:X7:78'>
          <small class='error'>Bitte beachte die Konvention! Nur Großbuchstaben inklusive :</small>
        </div>
        <div class='small-6 columns'>
          <input type='text' class='form-control' name='key' required placeholder='Public Key'>
          <small class='error'>Der Vorname ist ein Pflichtfeld.</small>
        </div>
      </div>

      <button class='button' type='submit' name='submit' value='add'>Hinzufügen</button>
  </form>
</article>

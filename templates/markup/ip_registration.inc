<article id='article' class='large-12 columns'>
  <h1>IP Registrieren</h1>
  <p>
    Hier kannst du deinem Rechner im Freifunknetz eine Statische IP zuweisen.
  </p>
  <form class='omb_nodeAdd' data-abide action='./add' accept-charset='UTF-8' autocomplete='off' method='post'>
      <div class='row collapse'>
        <div class='small-6 columns'>
          <input type='text' class='form-control' name='title' placeholder='Rechnername'>
          <small class='error'>Der Rechnername ist ein Pflichtfeld.</small>
        </div>
        <div class='small-6 columns'>
          <input type='text' class='form-control' required pattern='([0-9A-Fa-f]{2}[:]){5}([0-9A-Fa-f]{2})' name='mac' placeholder='Example: E8:DD:08:9C:57:78'>
          <small class='error'>Bitte beachte die Konvention!</small>
        </div>
      </div>

      <button class='button' type='submit' name='submit' value='add'>Hinzufügen</button>
  </form>
</article>

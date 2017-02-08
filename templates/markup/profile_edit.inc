<article id='article' class='medium-9 small-12 columns'>
  <h1>Profil <?=$page->title?></h1>

  <form action="senden.html" id="form_2" method="post">
    <label id="h2" form="form_2">Einstellungen</label>
    <label for="firstname">Vorname</label>
    <input type="text" id="firstname" maxlength="30" value="<?=$firstname?>">
    <label for="lastname">Nachname</label>
    <input type="text" id="lastname" maxlength="30" value="<?=$lastname?>">
    <label for="email">E-Mail</label>
    <input type="text" id="email" maxlength="40" value="<?=$email?>">
    <label for="publicKey">SSH Public Key</label>
    <input type="text" id="publicKey" value="<?=$publicKey?>">
    <label for="currentPw">Aktuelles Passwort</label>
    <input type="password" id="currentPw">
    <button type="submit">Speichern</button>
  </form>
</article>
<aside id="sidebar" class="medium-3 small-12 columns">
  <?=$page->userlist?>
</aside>

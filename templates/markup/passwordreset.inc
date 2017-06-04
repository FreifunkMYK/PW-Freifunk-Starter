<article id='article' class='medium-9 small-12 columns'>
  <h1>Profil <?=$page->title?></h1>

  <form action="./" id="form_2" method="post">
    <label for="firstname">Benutzer</label>
    <input type="text" id="firstname" maxlength="30" value="<?=$username?>" name="user" readonly="readonly">
    <label for="newPw">Neues Passwort</label>
    <input type="password" id="newPw" name="newpw">
    <label for="repeatPw">Wiederhole Passwort</label>
    <input type="password" id="repeatPw" name="repeatpw">
    <button type="submit" name="submit" value="submit">Speichern</button>
  </form>
</article>
<aside id="sidebar" class="medium-3 small-12 columns">
  <?=$page->userlist?>
</aside>

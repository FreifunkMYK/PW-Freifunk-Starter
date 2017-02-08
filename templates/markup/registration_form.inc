<div class='large-6 columns'>
    <h2>Registrierung</h2>
    <form class='omb_loginForm' data-abide action='./' accept-charset='UTF-8' autocomplete='off' method='post'>

        <div class='row collapse'>
          <div class='small-1 columns'>
            <span class='prefix'><i class='fa fa-user'></i> *</span>
          </div>
          <div class='small-11 columns'>
            <input type='text' class='form-control' required pattern='[a-z0-9-_.]+' name='username' placeholder='Benutzername (auch Login)' <?php if($session->get('username')) echo "value='{$session->get('username')}'"; ?> >
            <small class='error'>Benutzername ist ein Pflichtfeld und darf aus a-z 0-9 sowie -_. bestehen.</small>
          </div>
        </div>

        <div class='row collapse'>
          <div class='small-1 columns'>
            <span class='prefix'><i class='fa fa-user'></i></span>
          </div>
          <div class='small-12 medium-5 columns'>
            <input type='text' class='form-control' name='firstname' placeholder='Vorname' <?php if($session->get('firstname')) echo "value='{$session->get('firstname')}'"; ?>>
          </div>
          <div class='small-12 medium-6 columns'>
            <input type='text' class='form-control' name='lastname' placeholder='Nachname' <?php if($session->get('lastname')) echo "value='{$session->get('lastname')}'"; ?>>
          </div>
        </div>

         <div class='row collapse'>
          <div class='small-1 columns'>
            <span class='prefix'><i class='fa fa-envelope'></i> *</span>
          </div>
          <div class='small-11 columns'>
            <input type='text' class='form-control' name='email' required placeholder='Email' <?php if($session->get('email')) echo "value='{$session->get('email')}'"; ?>>
            <small class='error'>Die E-Mail Adresse ist ein Pflichtfeld.</small>
          </div>
        </div>

        <div class='row collapse'>
          <div class='small-1 columns'>
            <span class='prefix'><i class='fa fa-lock'></i> *</span>
          </div>
          <div class='small-11 columns'>
            <input  type='password' class='form-control' name='password' required pattern='((?=.*[a-z])(?=.*[A-Z])(?=.*[0-9-_!@#$%?+-]).)' placeholder='Passwort'>
            <small class='error'>Das Passwort muss einen Groß und Kleinbuchstaben sowie eine Zahl oder Sonderzeichen (_!@#$%?+-) enthalten.</small>
          </div>
        </div>
        <span class='help-block'></span>

        <button class='button' type='submit' name='submit' value='register'>Register</button>
    </form>
</div>
<div class='large-6 columns'>
  <h2>Datenschutz</h2>
  <p>Die Betreiber dieser Seiten nehmen den Schutz Ihrer persönlichen Daten sehr ernst. Wir behandeln Ihre personenbezogenen Daten vertraulich und entsprechend der gesetzlichen Datenschutzvorschriften sowie dieser Datenschutzerklärung.</p>
  <p>Die Nutzung unserer Webseite ist in der Regel ohne Angabe personenbezogener Daten möglich. Soweit auf unseren Seiten personenbezogene Daten (beispielsweise Name, Anschrift oder E-Mail-Adressen) erhoben werden, erfolgt dies, soweit möglich, stets auf freiwilliger Basis. Diese Daten werden ohne Ihre ausdrückliche Zustimmung nicht an Dritte weitergegeben.</p>
  <p>Wir weisen darauf hin, dass die Datenübertragung im Internet (z.B. bei der Kommunikation per E-Mail) Sicherheitslücken aufweisen kann. Ein lückenloser Schutz der Daten vor dem Zugriff durch Dritte ist nicht möglich.</p><br />
  <h3>Auskunft, Löschung, Sperrung</h3>
  <p>Sie haben jederzeit das Recht auf unentgeltliche Auskunft über Ihre gespeicherten personenbezogenen Daten, deren Herkunft und Empfänger und den Zweck der Datenverarbeitung sowie ein Recht auf Berichtigung, Sperrung oder Löschung dieser Daten. Hierzu sowie zu weiteren Fragen zum Thema personenbezogene Daten können Sie sich jederzeit unter der im Impressum angegebenen Adresse an uns wenden.</p>
  <br />
  <h3>Server-Log-Files</h3>
  <p>Der Provider der Seiten erhebt und speichert automatisch Informationen in so genannten Server-Log Files, die Ihr Browser automatisch an uns übermittelt. Dies sind:</p>
  <ul>
  <li>Browsertyp/ Browserversion</li>
  <li>verwendetes Betriebssystem</li>
  <li>Referrer URL</li>
  <li>Hostname des zugreifenden Rechners</li>
  <li>Uhrzeit der Serveranfrage</li>
  </ul>
  <p><br />Diese Daten sind nicht bestimmten Personen zuordenbar. Eine Zusammenführung dieser Daten mit anderen Datenquellen wird nicht vorgenommen. Wir behalten uns vor, diese Daten nachträglich zu prüfen, wenn uns konkrete Anhaltspunkte für eine rechtswidrige Nutzung bekannt werden.</p><br />
  <h3>Cookies</h3>
  <p>Die Internetseiten verwenden teilweise so genannte Cookies. Cookies richten auf Ihrem Rechner keinen Schaden an und enthalten keine Viren. Cookies dienen dazu, unser Angebot nutzerfreundlicher, effektiver und sicherer zu machen. Cookies sind kleine Textdateien, die auf Ihrem Rechner abgelegt werden und die Ihr Browser speichert.</p>
  <p>Die meisten der von uns verwendeten Cookies sind so genannte „Session-Cookies“. Sie werden nach Ende Ihres Besuchs automatisch gelöscht. Andere Cookies bleiben auf Ihrem Endgerät gespeichert, bis Sie diese löschen. Diese Cookies ermöglichen es uns, Ihren Browser beim nächsten Besuch wiederzuerkennen.</p>
  <p>Sie können Ihren Browser so einstellen, dass Sie über das Setzen von Cookies informiert werden und Cookies nur im Einzelfall erlauben, die Annahme von Cookies für bestimmte Fälle oder generell ausschließen sowie das automatische Löschen der Cookies beim Schließen des Browser aktivieren. Bei der Deaktivierung von Cookies kann die Funktionalität dieser Website eingeschränkt sein.</p><br />
  <h3>Kontaktformular</h3>
  <p>Wenn Sie uns per Kontaktformular Anfragen zukommen lassen, werden Ihre Angaben aus dem Anfrageformular inklusive der von Ihnen dort angegebenen Kontaktdaten zwecks Bearbeitung der Anfrage und für den Fall von Anschlussfragen bei uns gespeichert. Diese Daten geben wir nicht ohne Ihre Einwilligung weiter.</p><br />
  <h3>Widerspruch Werbe-Mails</h3>
  <p>Der Nutzung von im Rahmen der Impressumspflicht veröffentlichten Kontaktdaten zur Übersendung von nicht ausdrücklich angeforderter Werbung und Informationsmaterialien wird hiermit widersprochen. Die Betreiber der Seiten behalten sich ausdrücklich rechtliche Schritte im Falle der unverlangten Zusendung von Werbeinformationen, etwa durch Spam-E-Mails, vor.</p><br />
  <h3>Newsletterdaten</h3>
  <p>Wenn Sie den auf der Webseite angebotenen Newsletter beziehen möchten, benötigen wir von Ihnen eine E-Mail-Adresse sowie Informationen, welche uns die Überprüfung gestatten, dass Sie der Inhaber der angegebenen E-Mail-Adresse sind und mit dem Empfang des Newsletters einverstanden sind. Weitere Daten werden nicht erhoben. Diese Daten verwenden wir ausschließlich für den Versand der angeforderten Informationen und geben sie nicht an Dritte weiter.</p>
  <p>Die erteilte Einwilligung zur Speicherung der Daten, der E-Mail-Adresse sowie deren Nutzung zum Versand des Newsletters können Sie jederzeit widerrufen , etwa über den „Austragen“-Link im Newsletter.</p><br />
  <p><i>Quellenangabe: <a rel='nofollow' href='http://www.e-recht24.de/muster-datenschutzerklaerung.html' target='_blank'>eRecht24</a></i></p>
</div>

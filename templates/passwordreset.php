<?php

// Password reset funktion
if($input->get->token){
  $token = $sanitizer->text($input->get->token);
  $username = $sanitizer->name($input->get->user);
  $u = wire('users')->get("name=$username");

    if($token == $u->authkey){
      $t = new TemplateFile($config->paths->templates ."markup/passwordreset.inc");
      $t->set('username', $u->name);
    }
  } else {
  $t = new TemplateFile($config->paths->templates ."markup/passwordreset_request.inc");
}

$content = $t->render();

// Nach dem Speichern eines Formulars
if($input->post->submit || $input->get->submit){

  // Wenn ein neues Password gesetzt wurde
  if($input->post->newpw){
    $ldap = wire('modules')->get("ldapHelper");

    $username = $sanitizer->name($input->post->user);
    $change['newpassword'] = $sanitizer->text($input->post->newpw);

    if($ldap->modifyUser($username, $change)){
      $content = "Password gespeichert, du kannst dich nun einloggen.";
      $u = wire('users')->get("name=$username");
      $u->authkey = "";
    } else {
      $content = "{$input->post->user}: Es ist ein fehler aufgetreten, versuche es zu einem Späteren Zeitpunkt noch einmal!";
    }
  }

  // Wenn ein Request gesendet wird
  if($input->get->email){
    $email = $sanitizer->email($input->get->email);
    $u = wire('users')->get("email=$email");

    $u->of(false);
    $u->authkey = getToken();
    $u->save();
    $u->of(true);

    $reseturl = wire('page')->httpUrl ."/pwreset?token=". $u->authkey ."&user=". $u->name;
    $mail = wireMail();
    $mail->to($u->email)->from('reset@ffmyk.de');
    $mail->subject("Reset Password");
    $mail->body("===== Password Zurücksetzen ===== \n\n
    mit dieser E-Mail kannst du dein Password zurücksetzen.\n
    $reseturl \n
    Sollte der Link nicht anklickbar sein, kopiere ihn und füge ihn in die Adresszeile deines Browsers ein.");
    if($mail->send()) wire('log')->message('Send Mail: Password Reset') ;

    $content = "Du erhälst eine E-Mail mit einem Link, falls keine E-Mail ankommt versuche es später noch einmal.";
  }
}

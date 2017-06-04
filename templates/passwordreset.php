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

// Nach dem Speichesrn eines Formulars
if($input->post->submit || $input->get->submit){

  // Wenn ein neues Password gesetzt wurde
  if($input->post->newpw){
    $ldap = wire('modules')->get("ldapHelper");

    $username = $sanitizer->name($input->post->user);

    if($ldap->ldapHelperChangePw($username, $sanitizer->text($input->post->newpw), $sanitizer->text($input->post->repeatpw))){
      $content = $ldap->message;
      $u = wire('users')->get("name=$username");
      $u->authkey = "";
      $u->of(false);
      $u->save();
      $u->of(true);
    } else {
      $content = "Ein fehler ist aufgetreten: <br /> {$ldap->message}";
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

    $reseturl = wire('page')->httpUrl ."?token=". $u->authkey ."&user=". $u->name;
    $mail = wireMail();
    $mail->to($u->email)->from('reset@ffmyk.de');
    $mail->subject("Reset Password");
    $mail->body("===== Password Zurücksetzen ===== \n\n
    mit dieser E-Mail kannst du dein Password zurücksetzen.\n
    $reseturl \n
    Sollte der Link nicht anklickbar sein, kopiere ihn und füge ihn in die Adresszeile deines Browsers ein.");
    if($mail->send()) wire('log')->message('Send Mail: Password Reset') ;

    $t = new TemplateFile($config->paths->templates ."markup/passwordreset_mail.inc");
    $content = $t->render();
  }
}

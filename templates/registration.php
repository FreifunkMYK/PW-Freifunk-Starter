<?php
$error = false;
$content = '';

// form was submitted so we process the form
if($input->post->submit) {

         //Sanatize and assign variables data before creating user.
        $nuser["username"] = $sanitizer->username($input->post->username);
        $nuser["email"] = $sanitizer->email($input->post->email);
        $nuser["password"] = $sanitizer->text($input->post->password);
        $nuser["firstname"] = $sanitizer->text($input->post->firstname);
        $nuser["lastname"] = $sanitizer->text($input->post->lastname);

        $content .= registerUser($nuser);

} elseif($input->get->authkey) {
  $auth_user = $users->get($input->get->user);
  $content .= authorize($auth_user, $input->get->authkey);
}


if(!wire('user')->isLoggedin() && !wire('input')->post->submit || !wire('user')->isLoggedin() && !wire('input')->get->authkey){
  $content .= renderPage('registration_form');
} elseif(!wire('input')->post->submit || !wire('input')->get->authkey) {
  $content .= "<div data-alert class='alert-box alert'>
    Du bist eingeloggt!
  </div> ";

  //$aktivierungslink = wire('page')->httpUrl ."?authkey=". $user->authkey ."&user=". $user->name;
  //wireMail("{$user->email}", 'registration@ffmyk.de', 'Activierung', "Aktivierungs Link: \n $aktivierungslink");
}

$content = "<div id='article' class='row'> $content </div>";

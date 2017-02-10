<?php 

$name = $_POST["name"];
$email = $_POST["email"];
$message = $_POST["message"];

$msg = "

Name: $name
E-Mail: $email
Nachricht: $message

";

$to="sebastian.preisner@gmail.com";
$subject="Anfrage Webformular";
$message= $msg;
$headers= 'From: info@freifunk-myk.de' . "\r\n" .
    'Reply-To: ' . $email .",mayen-koblenz@freifunk.net". "\r\n" .
    'X-Mailer: PHP/';
mail($to,$subject,$message,$headers);

?>

<?php

$ldap = $modules->get("ldaphelper");

if($input->get->username){
  $ldapuser['username'] = $input->get->username;
  if(isset($input->get->oldpassword)) $ldapuser['oldPassword'] = $input->get->oldpassword;
  $ldapuser['newPassword'] = $input->get->newpassword;
  $ldap->save($ldapuser);
}


?>

<form class="form-horizontal" method="post" action='./'>
<fieldset>

<!-- Form Name -->
<legend>Edit Profile</legend>

<!-- Text input-->
<div class="form-group">
  <label class="col-md-4 control-label" for="username">Benutzername</label>
  <div class="col-md-4">
  <input id="username" name="username" type="text" placeholder="<?$user->name?>" class="form-control input-md" required="">

  </div>
</div>

<!-- Password input-->
<div class="form-group">
  <label class="col-md-4 control-label" for="oldpw">Old Password</label>
  <div class="col-md-4">
    <input id="oldpw" name="oldpw" type="password" placeholder="" class="form-control input-md" required="">

  </div>
</div>

<!-- Password input-->
<div class="form-group">
  <label class="col-md-4 control-label" for="newpw">New Password</label>
  <div class="col-md-4">
    <input id="newpw" name="newpw" type="password" placeholder="" class="form-control input-md" required="">

  </div>
</div>

<!-- Password input-->
<div class="form-group">
  <label class="col-md-4 control-label" for="newpw2">Repeat Password</label>
  <div class="col-md-4">
    <input id="newpw2" name="newpw2" type="password" placeholder="" class="form-control input-md" required="">

  </div>
</div>

<!-- Button (Double) -->
<div class="form-group">
  <label class="col-md-4 control-label" for="success"></label>
  <div class="col-md-8">
    <button id="success" name="success" class="btn btn-success">Success</button>
    <button id="delete" name="delete" class="btn btn-danger">Delete</button>
  </div>
</div>

</fieldset>
</form>

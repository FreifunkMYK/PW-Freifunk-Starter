<?php
class mysqlMigrate {

  private $pdo, $user;

  public function __construct() {
    $serv='dd33236.kasserver.com';
    $datb='d01ca9b7';
    $user='d01ca9b7';
    $pass='MBWsAxDec9C4yV4L';

    $this->pdo = new PDO("mysql:host=$serv;dbname=$datb;", "$user", "$pass");
  }

  public function getUserID($email){
    $sql = sprintf("SELECT * FROM User WHERE EMail = '%s' LIMIT 1", stripslashes($email));
    $user = $this->pdo->query($sql);
    foreach ($user as $row){
      $userid = $row['UserID'];
    }
    return $userid;
  }

  public function searchNodes($email){
    $userid = $this->getUserID($email);
    /* Wenn nicht vorhanden */
    //if(empty($user)) return false;

    $sql = sprintf("SELECT * FROM Nodekeys WHERE UserID = %s", $userid);
    $nodes = $this->pdo->query($sql);

    /* Wenn keine nodes return */
    //if(empty($nodes)) return false;

    return $nodes;
  }

  public function deleteNode($mac){
    $statement = $this->pdo->prepare("DELETE FROM Nodekeys WHERE MAC = ?");
    $statement->execute(array($mac));
    return true;
  }

  public function deleteUser($email){
    $userid = $this->getUserID($email);

    $statement = $this->pdo->prepare("DELETE FROM User WHERE UserID = ?");
    $statement->execute(array($userid));
    return true;
  }
}

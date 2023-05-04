<!DOCTYPE html>
<html>
<head>
   <meta charset="utf-8">
   <title></title>
</head>
<body>
   <?php
   session_start();
   // $host = 'localhost';
   // $user = '';
   // $pw = '';
   // $db_name = '';
      // $mysqli = new mysqli($host, $user, $pw, $db_name); //db 연결
      
      //login.php에서 입력받은 id, password
      $username = $_POST['id'];
      $userpass = $_POST['pw'];
      
      // $q = "SELECT * FROM member WHERE id = '$username' AND pass = '$userpass'";
      // $result = $mysqli->query($q);
      // $row = $result->fetch_array(MYSQLI_ASSOC);
      
      //결과가 존재하면 세션 생성
      if ($username == 'webserv' && $userpass == 'no' || ($_COOKIE['session_id'] == 'webserv-Jacob')) {
         $_SESSION['username'] = $username;
         $_SESSION['name'] = 'Jacob';
         echo "<script>location.replace('index.php');</script>";
         exit;
      }
      else if ($username == 'irc' && $userpass == 'yes') {
         $_SESSION['username'] = $username;
         $_SESSION['name'] = 'Daniel';
         echo "<script>location.replace('index.php');</script>";
         exit;
      }
      else {
         echo "<script>alert('Invalid username or password')</script>";
         echo "<script>location.replace('login.php');</script>";
         exit;
      }
      ?>
   </body>
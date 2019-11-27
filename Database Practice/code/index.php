<?php
    session_start();
    if (isset($_SESSION['isLogin']) && $_SESSION['isLogin'] === 1) {
	header('Location: ./adminFrame.php');
      exit;
    }else{
        header('Location: ./login.php');
        exit;
    }
?>
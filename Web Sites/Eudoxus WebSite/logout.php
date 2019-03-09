<?php
session_start();
session_destroy();
header('Location: /Eudoxus/index.php');
?>

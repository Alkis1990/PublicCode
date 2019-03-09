<?php
session_start();
$servername = "localhost";
$username = "alkis";
$password = "1";
$databaseName = "eudoxus";

// Create connection
$conn = new mysqli($servername, $username, $password, $databaseName);
$conn->query('set names utf8');
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}


?>

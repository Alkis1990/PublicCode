<?php

$room_id = @$_POST['room_id'];
if(!$room_id){
    $response = array();
    $response['success'] = false;
    $response['message'] = "You have to specify a room";
    echo json_encode($response);
}

$servername = "localhost";
$username = "alkis";
$password = "1";
$databaseName = "wda_db";

// Create connection
$conn = new mysqli($servername, $username, $password, $databaseName);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$conn->query('SET NAMES utf8');

$q_fav = "SELECT * FROM favorites WHERE room_id=" . $room_id . " AND user_id=1";
$res = $conn->query($q_fav);
if($res->num_rows > 0){
    $q = "DELETE FROM favorites WHERE room_id=".$room_id . " AND user_id=1";
}
else{
    $q = "INSERT INTO favorites(date_created, user_id, room_id) VALUES('" . date('Y-m-d H:i:s') . "', 1, " . $room_id . ")";
}


$res_2 = $conn->query($q);
if($res_2){
    $response = array();
    $response['success'] = true;
    if($res->num_rows > 0){
        $response['message'] = "<input style='width: 100%;padding: 10px;' type='button' value='Add to Favorites' onclick='toggle_to_favorites(". $room_id .");'>";
    }
    else{
        $response['message'] = "<input style='background: #0f0; color: #fff;width: 100%;padding: 10px; ' type='button' value='Remove from Favorites' onclick='toggle_to_favorites(" .$room_id  . ");'>";
    }
    echo json_encode($response);
}
else{
    $response['success'] = false;
    $response['message'] = mysqli_error($conn);
    echo json_encode($response);
}


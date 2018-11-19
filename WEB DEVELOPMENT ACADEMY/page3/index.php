<?php

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

$q_user = "SELECT * FROM user WHERE user_id=1";
$res_u = $conn->query($q_user);
while($u = $res_u->fetch_object()){
    $users = $u->username;
}

$q_bookings = "SELECT * FROM bookings LEFT JOIN room ON room.room_id=bookings.room_id 
                LEFT JOIN room_type ON room_type.id=room.room_type WHERE user_id=1 ORDER BY check_in_date ASC";
$res_b = $conn->query($q_bookings);
$bookings = array();
while($b = $res_b->fetch_object()){
    $b->num_days = (strtotime($b->check_out_date) - strtotime($b->check_in_date))/(60*60*24);
    $b->num_days = round($b->num_days) - 1;
    $bookings[] = $b;
    
}

$q_reviews = "SELECT * FROM reviews LEFT JOIN room ON reviews.room_id=room.room_id WHERE user_id=1";
$reviews = array();
$res_re = $conn->query($q_reviews);
while($re = $res_re->fetch_object()){
    
    $reviews[] = $re;
}
$q_favorites = "SELECT * FROM favorites LEFT JOIN room ON favorites.room_id=room.room_id WHERE user_id=1";
$favorites = array();
$fav_re = $conn->query($q_favorites);
while($re = $fav_re->fetch_object()){
    
    $favorites[] = $re;
}




?>
<!DOCTYPE html>
<html lang="en-US">

<head>
    <meta charset="UTF-8">
    <meta name="description" content="An example demonstrating HTML5 forms.">
    <meta name="keywords" content="HTML5,form">
    <meta name="author" content="Alkis Kotsas">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.5.0/css/all.css" integrity="sha384-B4dIYHKNBt8Bc12p+WXckhzcICo0wtJAoU8YZTY5qE0Id1GSseTk6S+L3BlXeVIU"
        crossorigin="anonymous">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO"
        crossorigin="anonymous" id="bootstrap-css">
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy"
        crossorigin="anonymous"></script>
    <script src="//code.jquery.com/jquery-1.11.1.min.js"></script>
    <link rel="stylesheet" href="https://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css" media="screen">
    <script src="https://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js"></script>
    <link rel="stylesheet" type="text/css" href="./styles.css">

    <title>Euro-Tripper</title>



</head>

<body>
    <header data-position="fixed">
        <a href="../page1/index.php" data-ajax="false">
            <div class="logo"><img src="./assets/logo.png" alt=logo class="responsive"></div>
        </a>
        <div class="profile">
            <i class="fas fa-user"></i>
            <a href="../page3/index.php" data-ajax="false"><span>
                    <?php echo $users; ?></span></a>
        </div>
    </header>
    <main id="main">
        <div class="ui-grid-a ui-responsive">
            <div class="ui-block-a">
                <h2>Favorites</h2>
                <hr>
                <ol>
                    <?php foreach ($favorites as $f) {
                        ?>
                    <li><a data-ajax="false" href="../page4/index.php?room_id=<?php echo $f->room_id; ?>">
                            <?php echo $f->name;?></a></li>
                    <?php } ?>
                </ol>
                <h2>Reviews</h2>
                <hr>
                <ol>
                    <?php 
                    foreach ($reviews as $r){ 
                    ?>
                    <p>
                        <?php echo $r->name; ?>
                    </p>
                    <span class="fa fa-star <?php echo $r->rate >= 1 ? 'checked' : ''; ?>"></span>
                    <span class="fa fa-star <?php echo $r->rate >= 2 ? 'checked' : ''; ?>"></span>
                    <span class="fa fa-star <?php echo $r->rate >= 3 ? 'checked' : ''; ?>"></span>
                    <span class="fa fa-star <?php echo $r->rate >= 4 ? 'checked' : ''; ?>"></span>
                    <span class="fa fa-star <?php echo $r->rate >= 5 ? 'checked' : ''; ?>"></span>
                    <?php
                    }
                    ?>
                </ol>
            </div>

            <div class="ui-block-b">
                <div class="panel panel-default">
                    <div class="panel-heading">
                        <h1>My Bookings</h1>
                        <hr>
                    </div>
                    <ul class="all-bookings">
                        <?php 
                        foreach($bookings as $b){
                        ?>
                        <li class="hotel-details">
                            <div class="flex">
                                <div class="hotel-img">
                                    <img src="../rooms/<?php echo $b->photo; ?>" alt=hotel-image class="hotel-img">
                                </div>
                                <div class="vertical-row"></div>
                                <div>
                                    <div class="hotel-name">
                                        <h3>
                                            <?php echo $b->name; ?>
                                        </h3>
                                        <p>
                                            <?php echo $b->short_description; ?>
                                        </p>
                                    </div>
                                    <div class="hotel-place">
                                        <h5>
                                            <?php echo $b->city; ?>
                                        </h5>
                                        <h5>
                                            <?php echo $b->area; ?>
                                        </h5>
                                    </div>
                                    <div class="room-view-button">
                                        <a href="../page4/index.php?room_id=<?php echo $r->room_id; ?>" data-ajax="false">
                                            <input type="button" class="room_overview" value="Room Overview"></a>
                                    </div>
                                </div>
                            </div>
                            <div class="ui-grid-c" id="card-box">
                                <div class="ui-block-a">
                                    <div class="ui-bar ui-bar-a">Stay from :
                                        <?php echo date('d-m-Y', strtotime($b->check_in_date)); ?>
                                    </div>
                                </div>
                                <div class="ui-block-b">
                                    <div class="ui-bar ui-bar-a">Leave on:
                                        <?php echo date('d-m-Y', strtotime($b->check_out_date)); ?>
                                    </div>
                                </div>
                                <div class="ui-block-c">
                                    <div class="ui-bar ui-bar-a">Total cost:
                                        <?php echo $b->price * $b->num_days; ?>&euro;</div>
                                </div>
                                <div class="ui-block-d">
                                    <div class="ui-bar ui-bar-a">Room type:
                                        <?php echo $b->room_type; ?>
                                    </div>
                                </div>
                            </div>
                            <hr>
                        </li>
                        <?php
                        }
                        ?>
                        <ul>
                </div>
            </div>
    </main>

    <div data-role="footer" data-position="fixed" data-tap-toggle="false">
        <span class="coded_by">
            <p>Coded by Alkis kotsas </p>
        </span>
        <span class="copyrights">
            &middot; &copy;Euro-Tripper 2018
        </span>
        <span class="footer_Href">
            <a href="../about_us/index.php" data-ajax="false">About Us</a>
            <span>|</span>
            <a href="../contact_us/index.php" data-ajax="false">Contact Us</a>
        </span>
    </div>
    </div>

</body>

</html>
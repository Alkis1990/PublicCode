<?php
session_start();
if(isset($_POST['city']) || isset($_POST['type']) || isset($_POST['date_from']) || isset($_POST['date_to'])){
    $city = @$_POST['city'];
    $price_min = @$_POST['price_min'];
    $price_max = @$_POST['price_max'];
    $type = @$_POST['type'];
    $date_from = @$_POST['date_from'];
    $date_to = @$_POST['date_to'];
    $_SESSION['city'] = $city;
    $_SESSION['type'] = $type;
    $_SESSION['date_from'] = $date_from;
    $_SESSION['date_to'] = $date_to;
    $_SESSION['price_min'] = $price_min;
    $_SESSION['price_max'] = $price_max;
}
else if(isset($_SESSION['city']) || isset($_SESSION['type']) || isset($_SESSION['date_from']) || isset($_SESSION['date_to'])){
    $city = @$_SESSION['city'];
    $type = @$_SESSION['type'];
    $date_from = @$_SESSION['date_from'];
    $date_to = @$_SESSION['date_to'];
    $price_min = @$_SESSION['price_min'];
    $price_max = @$_SESSION['price_max'];
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

$q_prices = "SELECT MIN(price) as mp, MAX(price) as mmp FROM room";
$res_prices = $conn->query($q_prices);
$mp = 0;
$mmp = 0;
$pps = $res_prices->fetch_object();
$mp = $pps->mp;
$mmp = $pps->mmp;

$q_cities = "SELECT DISTINCT city FROM room";
$res_c = $conn->query($q_cities);
$cities = array();
while($c = $res_c->fetch_object()){
    $cities[] = $c->city;
}
$q_types = "SELECT * FROM room_type";
$types = array();
$res_t = $conn->query($q_types);
while($t = $res_t->fetch_object()){
    $types[] = $t;
}

$q_user = "SELECT * FROM user";
$res_u = $conn->query($q_user);
while($u = $res_u->fetch_object()){
    $users = $u->username;
}



$q_rooms = "SELECT * FROM room LEFT JOIN room_type ON room.room_type=room_type.id WHERE 1 ";

if($city){
    $q_rooms .= " AND city='" . $city . "' ";
}


if($type){
    $q_rooms .= " AND room.room_type=" . $type . " ";
}

if($price_min){
    $q_rooms .= " AND room.price>=" . $price_min . " ";
}


if($price_max){
    $q_rooms .= " AND room.price<=" . $price_max . " ";
}

$d_start = date_create_from_format('d-m-Y', $date_from);
$date_start = date_format($d_start, 'Y-m-d');

$d_end = date_create_from_format('d-m-Y', $date_from);
$date_end = date_format($d_end, 'Y-m-d');

$q_rooms .= " AND NOT EXISTS (SELECT * FROM bookings WHERE bookings.room_id = room.room_id AND
                ('" . $date_start . "' BETWEEN check_in_date AND check_out_date) OR 
                ('" . $date_end . "' BETWEEN check_in_date AND check_out_date))";


$res_r = $conn->query($q_rooms);
$rooms = array();
while($r = $res_r->fetch_object()){
    $rooms[] = $r;
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
    <link rel="stylesheet" type="text/css" href="styles.css">
    <link rel="stylesheet" href='../css/bootstrap-datepicker.css' />
    <script src="../js/bootstrap-datepicker.js"></script>
    <title>Euro-Tripper</title>



</head>

<body>
    <header>
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
                <section>
                    <form method="post" action="" data-ajax="false">
                        <div>
                            <select class="roomtype" id="roomtype" name="type">
                                <option value="" disabled selected>Room Type</option>
                                <?php
                            foreach($types as $t){
                                ?>
                                <option value="<?php echo $t->id; ?>" <?php echo intval($t->id) === intval($type) ?
                                    'selected' : '' ?> >
                                    <?php echo $t->room_type; ?>
                                </option>
                                <?php
                            }
                            ?>
                            </select>
                        </div>
                        <div>
                            <select class="city" id="city" name="city">
                                <option value="" disabled selected>City</option>
                                <?php
                            foreach($cities as $c){
                                ?>
                                <option value="<?php echo $c; ?>" <?php echo $c===$city ? 'selected' : '' ; ?>>
                                    <?php echo $c; ?>
                                </option>
                                <?php
                            }
                            ?>
                            </select>
                            <div data-role="range">
                                <div data-role="main" class="ui-content">
                                    <div data-role="rangeslider">
                                        <label for="price-min">Price:</label>
                                        <input type="range" name="price_min" id="price-min" value="<?php echo $price_min; ?>"
                                            min="<?php echo $mp; ?>" max="<?php echo $mmp; ?>">
                                        <label for="price-max">Price:</label>
                                        <input type="range" name="price_max" id="price-max" value="<?php echo $price_max; ?>"
                                            min="<?php echo $mp; ?>" max="<?php echo $mmp; ?>">
                                    </div>
                                    <div class="datesin">
                                        <input placeholder="Arrive" class="form-control datepicker" type="text" id="Arrive"
                                            name="date_from" value="<?php echo $date_from ?>" />
                                    </div>
                                    <div class="dateout">
                                        <input placeholder="Leave" class="form-control datepicker" type="text" id="Leave"
                                            name="date_to" value="<?php echo $date_to ?>" />
                                    </div>
                                    <input type="submit" data-inline="true" value="Search">
                                </div>
                            </div>
                        </div>
                    </form>
                </section>
            </div>

            <div class="ui-block-b">
                <div class="panel panel-default">
                    <div class="panel-heading">
                        <h1>Search Results</h1>
                        <hr>
                    </div>
                    <ul class="all-results">
                        <?php
                        if(count($rooms) === 0){
                            echo "We do not have any rooms that match your criteria.";
                        }
                    foreach($rooms as $r){
                    ?>
                        <li class="hotel-details">
                            <div class="flex">
                                <div class="hotel-img">
                                    <img src="../rooms/<?php echo $r->photo ?>" alt=hotel-image class="hotel-img">
                                </div>
                                <div class="vertical-row"></div>
                                <div>
                                    <div class="hotel-name">
                                        <h3>
                                            <?php echo $r->name; ?>
                                        </h3>
                                        <p>
                                            <?php echo $r->short_description; ?>
                                        </p>
                                    </div>
                                    <div class="hotel-place">
                                        <h5>
                                            <?php echo $r->city; ?>
                                        </h5>
                                        <h5>
                                            <?php echo $r->area; ?>
                                        </h5>
                                    </div>
                                    <div class="room-view-button">
                                        <a href="../page4/index.php?room_id=<?php echo $r->room_id; ?>" data-ajax="false">
                                        <input type="button" class="room_overview" value="Room Overview"></a>
                                    </div>
                                </div>
                            </div>
                            <div class="ui-grid-b" id="card-box">
                                <div class="ui-block-a" id="bl">Price per night:
                                    <?php echo $r->price; ?>&euro;</div>
                                <div class="ui-block-b" id="bl">Count of guests:
                                    <?php echo $r->count_of_guests; ?>
                                </div>
                                <div class="ui-block-c" id="bl">Room type:
                                    <?php echo $r->room_type; ?>
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

    <script>
        $('.datepicker').datepicker({
            format: 'dd-mm-yyyy'
        });
    </script>
</body>

</html>
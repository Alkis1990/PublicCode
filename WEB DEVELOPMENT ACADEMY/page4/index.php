<?php
session_start();
$room_id = @$_GET['room_id'];
if(!$room_id){
    header('Location: ../page2/index.php');
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

if(@$_POST['submitting_review']){
    $stars = @$_POST['star_rating'];
    $comment = @$_POST['rating_comment'];
    $q = "INSERT INTO reviews(rate, text, date_created, user_id, room_id) ";
    $q .= " VALUES (" . intval($stars) . ", '" . trim($conn->real_escape_string($comment)) . "',";
    $q .= " '" . date('Y-m-d H:i:s') . "', 1, " . intval($room_id) . ")";
    $res = $conn->query($q);
    if($res === false){
        die("Could not add your rating");
    }
}

if(@$_POST['booking_r']){
    $d_from = @$_POST['date_from'];
    $d_to = @$_POST['date_to'];
    if(!$d_to || !$d_from){
        $error_message = "You have to input the dates you want to book";
    }
    else{
        
        $t_to = date_create_from_format('d-m-Y', $d_to);
        $t_from = date_create_from_format('d-m-Y', $d_from);
        $date_to = date_format($t_to, 'Y-m-d');
        $date_from = date_format($t_from, 'Y-m-d');
        if(strtotime($date_from) >= strtotime($date_to)){
            $error_message = "Arrival time has to be prior departure time";
        }
        else{
            $q_exists = "SELECT * FROM bookings WHERE bookings.room_id = " . $room_id . " AND
            ('" . $date_from . "' BETWEEN check_in_date AND check_out_date) OR 
            ('" . $date_to . "' BETWEEN check_in_date AND check_out_date)";
           
            $res_check = $conn->query($q_exists);
            if($res_check->num_rows > 0){
                $error_message = "These dates are not available";
            }
            else{
                $q = "INSERT INTO bookings(check_in_date, check_out_date, date_created, user_id, room_id) ";
                $q .= " VALUES('" . $date_from . "', '" . $date_to . "', '" . date('Y-m-d H:i:s') . "', 1, " . intval($room_id) . ")";
                
                $res_b = $conn->query($q);
                if($res_b === false){
                    $error_message = "Could not book for those dates";
                }
                else{
                    $success_message = "You have successfully booked your room";
                }
            }
        }
    }
}

$q_room = "SELECT * FROM room LEFT JOIN room_type ON room_type.id=room.room_type WHERE room_id=".$room_id;
$res_r = $conn->query($q_room);
if($res_r->num_rows === 0){
    header('Location: ../page2/index.php');
}
$room = $res_r->fetch_object();

$q_user = "SELECT * FROM user WHERE user_id=1";
$res_u = $conn->query($q_user);
while($u = $res_u->fetch_object()){
    $users = $u->username;
}

$q_reviews = "SELECT * FROM reviews LEFT JOIN user ON reviews.user_id=user.user_id WHERE room_id=".$room_id;
$reviews = array();
$res_re = $conn->query($q_reviews);
$total_rating = 0;
$num_reviews = 0;
$avg = 0;
while($re = $res_re->fetch_object()){
    $total_rating += $re->rate;
    $num_reviews ++;
    $reviews[] = $re;
}
if($num_reviews > 0){
    $avg = $total_rating / $num_reviews;
}
$in_favs = false;
$q_fav = "SELECT * FROM favorites WHERE user_id=1 AND room_id= " . $room_id;
$res_fav = $conn->query($q_fav);
if($res_fav->num_rows > 0){
    $in_favs = true;
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
    <script src="../js/star-rating.js"></script>
    <link rel="stylesheet" href='../css/bootstrap-datepicker.css' />
    <script src="../js/bootstrap-datepicker.js"></script>
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
        <div class="ui-grid-solo ui-responsive">
            <div class="ui-block-a">
                <div class="ui-grid-b ui-responsive">
                    <div class="ui-block-a">
                        <div class="ui-bar ui-bar-a">
                            <?php echo $room->name . ', ' . $room->city . ', ' . $room->area; ?>
                        </div>
                    </div>
                    <div class="ui-block-b">
                        <div class="ui-bar ui-bar-a">
                            Reviews
                            <span class="fa fa-star <?php echo $avg >= 1 ? 'checked' : ''; ?>"></span>
                            <span class="fa fa-star <?php echo $avg >= 2 ? 'checked' : ''; ?>"></span>
                            <span class="fa fa-star <?php echo $avg >= 3 ? 'checked' : ''; ?>"></span>
                            <span class="fa fa-star <?php echo $avg >= 4 ? 'checked' : ''; ?>"></span>
                            <span class="fa fa-star <?php echo $avg >= 5 ? 'checked' : ''; ?>"></span>
                        </div>
                    </div>
                    <div class="ui-block-c">
                        <div class="ui-bar ui-bar-a">
                            Cost Per Night:
                            <?php echo $room->price; ?>&euro;
                        </div>
                    </div>

                </div>
                <div id='atf_container'>
                    <?php
                    if($in_favs){
                    ?>
                    <input style='background: #0f0!important; color: #fff;width: 100%;padding: 10px; ' type='button' value='Remove from Favorites' onclick='toggle_to_favorites(<?php echo $room_id ?>);'>
                    <?php
                    }else{
                    ?>
                    <input type="button" value="Add to Favorites" onclick='toggle_to_favorites(<?php echo $room_id; ?>);'>
                    <?php
                    }
                    ?>
                </div>
                <div class="hotel-img">
                    <img src="../rooms/<?php echo $room->photo; ?>" alt=hotel-image class="hotel-img">
                </div>

            </div>
            <div class="ui-grid-d ui-responsive">
                <div class="ui-block-a">
                    <div class="ui-bar ui-bar-a">
                        <i class="fas fa-male"></i><i class="fas fa-female"></i></i> Count of guests:
                        <?php echo $room->count_of_guests; ?>
                    </div>
                </div>
                <div class="ui-block-b">
                    <div class="ui-bar ui-bar-a">
                        <i class="fas fa-bed"></i> Room type:
                        <?php echo $room->room_type; ?>
                    </div>
                </div>
                <div class="ui-block-c">
                    <div class="ui-bar ui-bar-a">
                        <i class="fas fa-parking"></i> Parking:
                        <?php echo $room->parking ? 'Yes' : 'No'; ?>
                    </div>
                </div>
                <div class="ui-block-d">
                    <div class="ui-bar ui-bar-a">
                        <i class="fas fa-wifi"></i> Wifi:
                        <?php echo $room->wifi ? 'Yes' : 'No'; ?>
                    </div>
                </div>
                <div class="ui-block-e">
                    <div class="ui-bar ui-bar-a">
                        <i class="fas fa-dog"></i> Pet friendly:
                        <?php echo $room->pet_friendly ? 'Yes' : 'No'; ?>
                    </div>
                </div>
            </div>
            <hr>
            <div class="hotel-description">
                <h4>Hotel-Description</h4>
                <p>
                    <?php echo $room->long_description; ?>
                </p>
            </div>
            <form action="./index.php?room_id=<?php echo $room_id; ?>" method="post" data-ajax='false'>
                <?php
                if(isset($error_message) && $error_message){
                ?>
                <div class="alert alert-danger" ><?php echo $error_message; ?></div>
                <?php
                }
                ?>
                <?php
                if(isset($success_message) && $success_message){
                ?>
                <div class='alert alert-success'><?php echo $success_message; ?></div>
                <?php
                }
                ?>
                <input type="hidden" name="booking_r" value="bbb" />
                <div class="ui-grid-a ui-responsive">
                    <div class="ui-block-a">
                        <input placeholder="Arrive" required class="form-control datepicker" type="text" name="date_from" value="<?php echo @$_SESSION['date_from']; ?>" />

                    </div>
                    <div class="ui-block-b">
                        <input placeholder="Leave" required class="form-control datepicker" type="text" name="date_to" value="<?php echo @$_SESSION['date_to']; ?>"/>
                    </div>
                </div>
                <div class="book-now">
                    <input type="submit" data-inline="true" value="Book Now">
                </div>
            </form>

            <hr>
            <div class="map">
                <h2>Hotel Location</h2>
            </div>
            <div class="mapouter">
                <div class="gmap_canvas"><a href="https://www.pureblack.de"></a>
                    <iframe width="100%" height="300" frameborder="0" scrolling="no" marginheight="0" marginwidth="0"
                        src="https://maps.google.com/maps?q=<?php echo $room->lat_location; ?>,<?php echo $room->lng_location; ?>&hl=es;z=14&amp;output=embed">
                    </iframe>
                </div>
            </div>
            <form action="./index.php?room_id=<?php echo $room_id; ?>" method="post" data-ajax="false">
                <input type="hidden" name='submitting_review' value="aaa" />
                <section class='rating-widget'>
                    <!-- Rating Stars Box -->
                    <div class='rating-stars'>
                        <ul id='stars'>
                            <li class='star' title='Poor' data-value='1'>
                                <i class='fa fa-star fa-fw'></i>
                            </li>
                            <li class='star' title='Fair' data-value='2'>
                                <i class='fa fa-star fa-fw'></i>
                            </li>
                            <li class='star' title='Good' data-value='3'>
                                <i class='fa fa-star fa-fw'></i>
                            </li>
                            <li class='star' title='Excellent' data-value='4'>
                                <i class='fa fa-star fa-fw'></i>
                            </li>
                            <li class='star' title='WOW!!!' data-value='5'>
                                <i class='fa fa-star fa-fw'></i>
                            </li>
                        </ul>
                    </div>
                    <input type="hidden" name='star_rating' id='star_rating_input' value="0" />
                </section>
                <div>
                    <textarea placeholder="Add your Review Here !" name='rating_comment' class="comments"></textarea>
                </div>
                <div class="submit">
                    <input type="Submit" data-inline="true" value="Submit">
                </div>
            </form>
            <hr>
            <div class="reviews">
                <?php
                foreach($reviews as $r){
                ?>
                <p> <?php echo $r->username; ?></p>
                <span class="fa fa-star <?php echo $r->rate >= 1 ? 'checked' : ''; ?>"></span>
                <span class="fa fa-star <?php echo $r->rate >= 2 ? 'checked' : ''; ?>"></span>
                <span class="fa fa-star <?php echo $r->rate >= 3 ? 'checked' : ''; ?>"></span>
                <span class="fa fa-star <?php echo $r->rate >= 4 ? 'checked' : ''; ?>"></span>
                <span class="fa fa-star <?php echo $r->rate >= 5 ? 'checked' : ''; ?>"></span>
                <p> <?php echo nl2br($r->text); ?></p>
                <p style='color: #777;font-size: 0.8em;'><?php echo date('d-m-Y H:i:s', strtotime($r->date_created)) ?></p>
                <?php
                }
                ?>
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
    $(document).ready(function(){
        $('.datepicker').datepicker({format: 'dd-mm-yyyy'});
    });
    function toggle_to_favorites(room_id){
        $.ajax({
            method: 'post',
            url: './favs.php',
            data: {
                room_id: room_id
            },
            dataType: 'json',
            success: function(response){
                if(response.success){
                    $('#atf_container').html(response.message);
                    $('input[type=button]').button();
                }
                else{
                    alert(response.message);
                }
            },
            error: function(response){
                console.log(response);
            }
        })
    }
    </script>

</body>

</html>
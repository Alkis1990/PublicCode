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

$conn->query('SET NAMES utf8');

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


// echo "Connected successfully";
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

        <div class="ui-grid-solo ui-responsive">
            <form action="../page2/index.php" method='post' data-ajax='false'>
                <div class="ui-grid-a ui-responsive">
                    <div class="ui-block-a">
                        <select class="form-control" id="city" name="city">
                            <option value="" disabled selected>City</option>
                            <?php
                            foreach($cities as $c){
                                ?>
                            <option value="<?php echo $c; ?>">
                                <?php echo $c; ?>
                            </option>
                            <?php
                            }
                            ?>
                        </select>
                    </div>
                    <div class="ui-block-b">
                        <select class="form-control" id="roomType" name="type">
                            <option value="" disabled selected>Room Type</option>
                            <?php
                            foreach($types as $t){
                                ?>
                            <option value="<?php echo $t->id; ?>">
                                <?php echo $t->room_type; ?>
                            </option>
                            <?php
                            }
                            ?>
                        </select>
                    </div>
                </div>
                <div class="ui-grid-a ui-responsive">
                    <div class="ui-block-a">
                        <input placeholder="Arrive" required class="form-control datepicker" type="text" name="date_from" />

                    </div>
                    <div class="ui-block-b">
                        <input placeholder="Leave" required class="form-control datepicker" type="text" name="date_to" />
                    </div>
                </div>
                <div class="submit">
                    <input type="submit" value="Search">
                </div>

            </form>
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
    <script>
        $('.datepicker').datepicker({
            format: 'dd-mm-yyyy'
        });
    </script>
</body>

</html>
<?php
require_once $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/dbconnect.php';

?>
<?php


if(@$_SESSION['user_logged_in'] === 'yes'){
    header('Location: /Eudoxus/');
}
if(@$_POST['username']){
    $username = $conn->real_escape_string(@$_POST['username']);
    $password = $conn->real_escape_string(@$_POST['password']);
    $q = "SELECT * FROM users WHERE username='" . $username . "' AND password = MD5('" . $password ."')";
    
    $res = $conn->query($q);
    if($res->num_rows === 0){
        $error_message = "Wrong username or password";
    }
    else{
        $user = $res->fetch_assoc();
        unset($user['password']);
        $_SESSION['user'] = $user;
        $_SESSION['user_logged_in'] = true;
        header('Location: /Eudoxus/');
    }
}

include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/header.php';
?>
        <div id="LoginForm">
            <div class="container">
                <div class="login-form">
                    <div class="main-div">
                        <div class="panel">
                            <h2>Σύνδεση</h2>
                            <?php
                            if(isset($error_message)){
                                ?>
                                <div class="alert alert-danger">
                                    <?php
                                    echo $error_message;
                                    ?>
                                </div>
                                <?php
                            }
                            ?>
                        </div>
                        <form action="/Eudoxus/log_in/index.php" method="post">

                            <div class="form-group">


                                <input type="text" class="form-control" name="username" id="inputEmail" placeholder="Username">

                            </div>

                            <div class="form-group">

                                <input type="password" class="form-control" name="password" id="inputPassword" placeholder="Κωδικός Χρήστη">

                            </div>
                            <div class="forgot">
                                <a href="reset.html">Ξέχασα τον Κωδικό μου!</a>
                            </div>
                            <button type="submit" class="btn btn-primary">Login</button>

                        </form>
                    </div>
                </div>
            </div>
        </div>

<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/footer.php';
?>
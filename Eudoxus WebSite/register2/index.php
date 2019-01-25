<?php
require_once $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/dbconnect.php';
if(@$_SESSION['user_logged_in']){
    header('/Eudoxus/index.php');
}
if(!@$_POST['student_type']){
    header('Location: /Eudoxus/register1/index.php');
}
if(!@$_POST['university']){
    header('Location: /Eudoxus/register1/index.php');
}
if(@$_POST['username']){
    $username = $conn->real_escape_string(@$_POST['username']);
    $password = $conn->real_escape_string(@$_POST['password']);
    $am = $conn->real_escape_string(@$_POST['am']);
    $student_type = $_POST['student_type'];
    $university = $_POST['university'];
    $department = @$_POST['department'];
    $degree = $conn->real_escape_string(@$_POST['degree']);
    $name = $conn->real_escape_string(@$_POST['name']);
    $last_name = $conn->real_escape_string(@$_POST['last_name']);
    $email = $conn->real_escape_string(@$_POST['email']);
    $phone = $conn->real_escape_string(@$_POST['phone']);
    $q = "INSERT INTO users VALUES(null, '" . $username . "', MD5('" . $password . "'), '" . $email . "', '" . $last_name . "', '" . $name . "',".
        " '". $university . "', '" . $department . "', '" . md5(date('Y-m-d')) . "', '" . $phone . "', '" . 1 . "', 0, '" . $am . "', '" . $student_type . "')";
    $res = $conn->query($q);
    if($res){
        $newid = $conn->insert_id;
        $_SESSION['user_logged_in'] = true;
        $qu = "SELECT * FROM users WHERE userID=".$newid;
        $resu = $conn->query($qu);
        $user = $resu->fetch_assoc();
        unset($user['password']);
        $_SESSION['user'] = $user;
        header('Location: /Eudoxus/');
    }
    else{

        $error_message = $conn->error;
    }
}
$departments = array();

$q_d = "SELECT * FROM departments WHERE universityID=" . $_POST['university'];
$res_d = $conn->query($q_d);
$departments = array();
while($d = $res_d->fetch_object()){
    $departments[] = $d;
}

?>
<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/header.php';
?>


        <div class="signup-form">
            <form action="" method="post">
                <h2>Φορμα Εγγραφής</h2>
                <?php
                if(@$error_message){
                    ?>
                    <div class="alert alert-danger">
                    <?php
                    echo $error_message;
                    ?>
                    </div>
                    <?php
                }
                ?>
                <div class="form-group">
                    <div class="row">
                        <div class="col-md">
                            <input type="hidden" name="student_type" value="<?php echo $_POST['student_type']; ?>">
                            <input type="hidden" name="university" value="<?php echo $_POST['university']; ?>">
                            <div class="username"><input type="text" class="form-control" name="username" placeholder="Όνομα χρήστη"
                                    required="required"></div>
                            <input type="password" class=" form-control" name="password" placeholder="Κωδικός" required="required">
                            <input type="password" class="form-control" name="confirm_password" placeholder="Επιβεβαίωση Κωδικού"
                                required="required">
                            <input type="text" class="form-control" name="am" placeholder="Αριθμός Μητρώου" />
                            <select class="form-control" name="department" required>
                                <option value="" disabled selected>Επιλεξτέ Τμήμα</option>
                                <?php
                                foreach($departments as $d){
                                    ?>
                                    <option value="<?php echo $d->departmentID; ?>"><?php echo $d->department; ?></option>
                                    <?php
                                }                       
                                ?>
                            </select>
                            <?php
                            if(@$_POST['student_type'] === 'postgrad'){
                                ?>
                                <input type="text" name="degree" class="form-control" placeholder="Αντικείμενο Πτυχείου"/>
                                <?php
                            }
                            ?>
                        </div>
                        <div class="col-md">
                            <input type="text" class="form-control" name="name" placeholder="Όνομα" required="required">
                            <input type="text" class="form-control" name="last_name" placeholder="Επώνυμο" required="required">
                            <input type="email" class="form-control" name="email" placeholder="Email" required="required">
                            <input type="phone" class="form-control" name="phone" placeholder="Τήλεφωνο" required="required">

                        </div>
                    </div>
                    <div class="form-group">
                        <label class="checkbox-inline"><input type="checkbox" required="required"> I accept the <a href="#">Terms
                                of Use</a> &amp; <a href="#">Privacy Policy</a></label>
                    </div>
                    <div class="form-group parent-btn">
                        <div class="child-btn">
                        <button type="submit" class="btn btn-success btn-lg btn-block">Υποβολή</button>
                        </div>
                    </div>
            </form>
            <div class="text-center">Έχετε Ήδη δημιουργήσει λογαριασμό; κάντε είσοδο <a href="/Eudoxus/log_in/index.php">Εδώ</a></div>
        </div>
        </div>
<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/footer.php';
?>
<?php
require_once $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/dbconnect.php';
if(!$_SESSION['user_logged_in']){
    header('Location: /');
}
if(@$_POST['name']){
    $name = @$_POST['name'];
    $studentID = @$_POST['studentID'];
    $surname = @$_POST['surname'];
    $email = @$_POST['email'];
    $phone = @$_POST['phone'];
    $semester = @$_POST['semester'];
    $q = "UPDATE users SET name='" . $name . "', studentID='" . $studentID . "', surname='" . $surname . "', email='" . $email . "', phone='" . $phone . "', semester='" . $semester . "' WHERE userID=" . $_SESSION['user']['userID'];
    $res = $conn->query($q);
    if($res){
        $success_message = 'Οι αλλαγές σας αποθηκεύτηκαν επιτυχώς.';
        $quser = "SELECT * FROM users WHERE userID=".$_SESSION['user']['userID'];
        $resuser = $conn->query($quser);
        $user = $resuser->fetch_assoc();
        unset($user['password']);
        $_SESSION['user'] = $user;
    }
    else{
        $error_message = $conn->error;
    }
}
$qu = "SELECT * FROM universities WHERE universityID=".$_SESSION['user']['universityID'];
$qd = "SELECT * FROM departments WHERE departmentID=".$_SESSION['user']['departmentID'];
$resu = $conn->query($qu);
$resd = $conn->query($qd);
$university = $resu->fetch_object();
$department = $resd->fetch_object();
?>
<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/header.php';
?>

        <div class="container ">
            <div class="row">
                <div class="card col-md-12">
                    <div class="card-body">
                        <form method="post" action="">
                                <h1>Το Προφίλ μου</h1>
                                <?php
                                if(@$success_message){
                                ?>
                                <div class="alert alert-success">
                                <?php
                                echo $success_message;
                                ?>
                                </div>
                                <?php
                                }
                                ?>
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
                            <div class="row">
                                <div class="col-md-8">
                                    <div class="tab-content profile-tab" id="myTabContent">
                                        <div class="tab-pane fade show active" id="home" role="tabpanel" aria-labelledby="home-tab">
                                            <div class="row">
                                                <div class="col-md-4">
                                                    <label>Ίδρυμα</label>
                                                </div>
                                                <div class="col-md-8">
                                                    <p><?php echo $university->university; ?></p>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-md-4">
                                                    <label>Τμήμα</label>
                                                </div>
                                                <div class="col-md-8">
                                                    <p><?php echo $department->department; ?></p>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-md-4">
                                                    <label>Αριθμός μητρόου</label>
                                                </div>
                                                <div class="col-md-8">
                                                    <p><input type="form-control" name="studentID" value="<?php echo $_SESSION['user']['studentID']; ?>" required/></p>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-md-4">
                                                    <label>Όνομα</label>
                                                </div>
                                                <div class="col-md-8">
                                                    <p><input type="form-control" name="name" value="<?php echo $_SESSION['user']['name']; ?>" required/></p>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-md-4">
                                                    <label>Επώνυμο</label>
                                                </div>
                                                <div class="col-md-8">
                                                    <p><input type="form-control" name="surname" value="<?php echo $_SESSION['user']['surname']; ?>" required/></p>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-md-4">
                                                    <label>Email</label>
                                                </div>
                                                <div class="col-md-8">
                                                    <p><input type="form-control" name="email" value="<?php echo $_SESSION['user']['email']; ?>" required/></p>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-md-4">
                                                    <label>Τηλέφωνο</label>
                                                </div>
                                                <div class="col-md-8">
                                                    <p><input type="form-control" name="phone" value="<?php echo $_SESSION['user']['phone']; ?>" required/></p>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-md-4">
                                                    <label>Τρέχον Εξάμηνο</label>
                                                </div>
                                                <div class="col-md-8">
                                                    <p><input type="form-control" name="semester" value="<?php echo $_SESSION['user']['semester']; ?>" required/></p>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-md-4">
                                                    <label>Παραληφθέντα Συγγράμματα</label>
                                                </div>
                                                <div class="col-md-8">
                                                    <p><?php echo intval($_SESSION['user']['BooksTaken']) . ' από ' . $department->books; ?></p>
                                                </div>
                                            </div>
                                            
                                        </div>
                                        <div class="edit">
                                        <input type="submit" class="btn btn-warning btn-block" name="btnAddMore" value="Αποθήκευση" />
                                    </div>
                                        
                                    </div>
                                </div>
                            </div>
                        </form>
                    </div>
                </div>
            </div>
        </div>
        <?php
        include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/footer.php';
        ?>
<?php
require_once $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/dbconnect.php';
if(@$_SESSION['user_logged_in']){
    header('/index.php');
}
$q_u = "SELECT * FROM universities";
$res = $conn->query($q_u);
$universities = array();
while($u = $res->fetch_object()){
    $universities[] = $u;
}
?>
<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/header.php';


?>
<div class="signup-form col-8">
    <form action="/Eudoxus/register2/index.php" method="post">
        <h2>Εγγραφή νέου χρήστη</h2>
        <div class="form-group parent-kind">
            <select class="form-control" name="student_type">
                <option value="" disabled selected>Επιλεξτέ ομάδα</option>
                <option value="undergrad">Προπτυχιακός Φοιτητής</option>
                <option value="postgrad">Μεταπτυχιακός Φοιτητής</option>
            </select>
        </div>
        <div class="form-group parent-kind">
            <select class="form-control" name="university">
                <option value="" disabled selected>Επιλεξτέ Πανεπιστήμιο</option>
                <?php
                foreach($universities as $u){
                    ?>
                    <option value="<?php echo $u->universityID; ?>"><?php echo $u->university; ?></option>
                    <?php
                }                       
                ?>
            </select>
        </div>
        <div class="form-group parent-btn col-8">
            <div class="child-btn">
            <button type="submit" class="btn btn-success btn-lg btn-block">Σύνεχεια</button>
            </div>
        </div>
    </form>
</div>
<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/footer.php';
?>
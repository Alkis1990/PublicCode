<?php
require_once $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/dbconnect.php';
if(!@$_SESSION['user_logged_in']){
    header('/Eudoxus/index.php');
}
//var_dump($_POST);
$qu = "SELECT * FROM universities WHERE universityID=".$_SESSION['user']['universityID'];
$qd = "SELECT * FROM departments WHERE departmentID=".$_SESSION['user']['departmentID'];
$resu = $conn->query($qu);
$resd = $conn->query($qd);
$university = $resu->fetch_object();
$department = $resd->fetch_object();
$modules = array();
$qm = "SELECT * FROM modules WHERE departmentID=" . $department->departmentID;
$resm = $conn->query($qm);
$semesters = array();
while($m = $resm->fetch_object()){
    $m->books = array();
    
    
    $modules[$m->moduleID] = $m;
}
sort($semesters);
$qb = "SELECT books.bookID, books.title, books.moduleID, books.author, books.BookYear, books.Diathesima, books.EkdotikosOikos, books.Address FROM books LEFT JOIN modules ON books.moduleID=modules.moduleID WHERE departmentID=".$department->departmentID;
$resb = $conn->query($qb);
while($b = $resb->fetch_object()){
    $modules[$b->moduleID]->books[$b->bookID] = $b;
}
$selected_modules = array();
foreach($modules as $m){
    if(@$_POST['books'.$m->moduleID]){
        $m->selected_book = $_POST['books'.$m->moduleID];
        $selected_modules[] = $m;
        $semesters[$m->semester] = $m->semester;
    }
}
sort($semesters);
if(@$_POST['submitted']){
    $books = $_POST['books'];
    foreach($books as $b){
        $qib = "INSERT INTO bookselection VALUES (null, " . $_SESSION['user']['userID'] . ", " . $b . ")";
        $resb = $conn->query($qib);
    }
    $q1 = "SELECT COUNT(*) as books_count FROM bookselection WHERE userID=".$_SESSION['user']['userID'];
    $res1 = $conn->query($q1);
    $bbs = $res1->fetch_object();
    $q2 = "UPDATE users SET BooksTaken=".$bbs->books_count . " WHERE userID=" . $_SESSION['user']['userID'];
    $res2 = $conn->query($q2);
    $quser = "SELECT * FROM users WHERE userID=".$_SESSION['user']['userID'];
    $resuser = $conn->query($quser);
    $user = $resuser->fetch_assoc();
    unset($user['password']);
    $_SESSION['user'] = $user;
    if($resb){
        $success_message = "Η δήλωση συγγραμάτων ολοκληρώθηκε επιτυχώς";
    }
    else{
        $error_message = "Η δήλωση συγγραμάτων απέτυχε";
    }
}
?>
<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/header.php';
?>
<?php
if(@$success_message){
    ?>
    <div class="alert alert-success">
    <?php echo $success_message; ?>
    </div>
    <?php
}
else{
?>
<form class="container" action="" method="post">
<?php
if(@$error_message){
    ?>
    <div class="alert alert-danger">
    <?php
    $error_message;
    ?>
    </div>
    <?php
}
?>
    <input type="hidden" name="submitted" value="1" />
    <h1>Δήλωση Συγγραμάτων</h1>
    <div class="row">
    

        <div class="col-md-12">
        



            <!-- Tab links -->
            <div class="tab">
            <?php
            foreach($semesters as $s){
?>
            <button type="button" class="tablinks" onclick="eksamino(event, 'semester<?php echo $s; ?>')"><?php echo $s; ?>ο εξάμηνο</button>
<?php
            }
            ?>
                
            </div>

            <!-- Tab content -->


            <?php
            foreach($semesters as $s){
            ?>
            <div id="semester<?php echo $s; ?>" class="tabcontent">
                
                <?php
                foreach($selected_modules as $m){
                    if($m->semester === $s){
                        $book = $m->books[$m->selected_book];
                ?>
                <div class="row">
                   <div class="col-md-5">
                        <?php echo $m->title; ?>
                   </div>
                   <div class="col-md-7">
                        <h2><?php echo $book->title; ?></h2>
                        <p><?php echo $book->author . ' - ' . $book->BookYear; ?></p>
                        <p><?php echo $book->EkdotikosOikos . ' (' . $book->Address . ') -' . $book->Diathesima . ' διαθέσιμα'; ?></p>
                   </div>
                </div>
                <input type="hidden" name="books[]" value="<?php echo $book->bookID ?>" />
                <?php
                    }
                }
                ?>
            </div>
                <?php
            }
                ?>
            
            <input type= "submit" class="btn btn-primary" value="Ολοκλήρωση">
        </div>
        
    </div>
</form>
    <script>
        function eksamino(evt, cityName) {
            // Declare all variables
            var i, tabcontent, tablinks;

            // Get all elements with class="tabcontent" and hide them
            tabcontent = document.getElementsByClassName("tabcontent");
            for (i = 0; i < tabcontent.length; i++) {
                tabcontent[i].style.display = "none";
            }

            // Get all elements with class="tablinks" and remove the class "active"
            tablinks = document.getElementsByClassName("tablinks");
            for (i = 0; i < tablinks.length; i++) {
                tablinks[i].className = tablinks[i].className.replace(" active", "");
            }

            // Show the current tab, and add an "active" class to the button that opened the tab
            document.getElementById(cityName).style.display = "block";
            evt.currentTarget.className += " active";
        }
    </script>


<?php
}
require $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/footer.php';
?>
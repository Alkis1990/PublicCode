<?php
require_once $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/dbconnect.php';
if(!@$_SESSION['user_logged_in']){
    header('/Eudoxus/index.php');
}
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
    $semesters[$m->semester] = $m->semester;
    
    $modules[$m->moduleID] = $m;
}
sort($semesters);
$qb = "SELECT books.bookID, books.title, books.moduleID FROM books LEFT JOIN modules ON books.moduleID=modules.moduleID WHERE departmentID=".$department->departmentID;
$resb = $conn->query($qb);
while($b = $resb->fetch_object()){
    $modules[$b->moduleID]->books[] = $b;
}
?>
<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/header.php';
?>

<form action="/Eudoxus/dilosi2/index.php" method="post" class="container">
    <h1>Δήλωση Συγγραμάτων</h1>
    <div class="row">


        <div class="col-md-12">




            <!-- Tab links -->
            <div class="tab">
                <?php
            foreach($semesters as $s){
?>
                <button type="button" class="tablinks" onclick="eksamino(event, 'semester<?php echo $s; ?>')">
                    <?php echo $s; ?>ο εξάμηνο</button>
                <?php
            }
            ?>


            </div class="dilosi1_t">

            <!-- Tab content -->

            <?php
            foreach($semesters as $s){
            ?>
            <div id="semester<?php echo $s; ?>" class="tabcontent">

                <?php
                foreach($modules as $m){
                    if($m->semester === $s){
                ?>
                <div class="row">
                    <div class="col-md-5">
                        <?php echo $m->title; ?>
                    </div>
                    <div class="col-md-7">
                        <select name="books<?php echo $m->moduleID; ?>" class="form-control">
                            <option value="">Χωρίς Σύγγραμα</option>
                            <?php
                            foreach($m->books as $b){
                            ?>
                            <option value="<?php echo $b->bookID; ?>">
                                <?php echo $b->title; ?>
                            </option>
                            <?php
                            }
                            ?>
                        </select>
                    </div>
                </div>
                <?php
                    }
                }
                ?>
            </div>
            <?php
            }
                ?>

            <input type="submit" class="btn btn-primary" value="Συνέχεια">
        </div>
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
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/footer.php';
?>
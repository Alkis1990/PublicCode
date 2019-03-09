<?php
require_once $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/dbconnect.php';
$q1 = "SELECT DISTINCT(EkdotikosOikos) as publisher FROM books";
$q2 = "SELECT DISTINCT(BookYear) as year FROM books";
$q3 = "SELECT DISTINCT(author) as author FROM books";
$publishers = array();
$years = array();
$authors = array();
$res1 = $conn->query($q1);
while($p = $res1->fetch_object()){
    $publishers[] = $p->publisher;
}
$res2 = $conn->query($q2);
while($y = $res2->fetch_object()){
    $years[] = $y->year;
}
$res3 = $conn->query($q3);
while($a = $res3->fetch_object()){
    $authors[] = $a->author;
}
$books = array();
if(@$_POST['find-all']){
    $q = "SELECT * FROM books WHERE 1 ";
    if(@$_POST['search_publisher']){
        $q .= " AND EkdotikosOikos='" . $_POST['search_publisher'] . "' ";
    }
    if(@$_POST['search_year']){
        $q .= " AND BookYear='" . $_POST['search_year'] . "' ";
    }
    if(@$_POST['search_author']){
        $q .= " AND author='" . $_POST['search_author'] . "' ";
    }
    if(@$_POST['search_text']){
        $q .= " AND (title LIKE '%" . $_POST['search_text'] . "%' OR author LIKE '%" . $_POST['search_text'] . "%' OR EkdotikosOikos LIKE '%" . $_POST['search_text'] . "%') ";
    }
    $res = $conn->query($q);
    while($b = $res->fetch_object()){
        $books[] = $b;
    }
}
if(@$_POST['find-with-avail']){
    $q = "SELECT * FROM books WHERE Diathesima > 0 ";
    if(@$_POST['search_publisher']){
        $q .= " AND EkdotikosOikos='" . $_POST['search_publisher'] . "' ";
    }
    if(@$_POST['search_year']){
        $q .= " AND BookYear='" . $_POST['search_year'] . "' ";
    }
    if(@$_POST['search_author']){
        $q .= " AND author='" . $_POST['search_author'] . "' ";
    }
    if(@$_POST['search_text']){
        $q .= " AND (title LIKE '%" . $_POST['search_text'] . "%' OR author LIKE '%" . $_POST['search_text'] . "%' OR EkdotikosOikos LIKE '%" . $_POST['search_text'] . "%') ";
    }
    $res = $conn->query($q);
    while($b = $res->fetch_object()){
        $books[] = $b;
    }
}
?>
<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/header.php';
?>
<div class="container-fluid">
    <div class="headLine">
        <h1>Αναζήτηση Συγγραμμάτων</h1>
    </div>
    <div class="card" style="width: 100%;     margin-bottom: 20px;">
        <div class="card-body">
            <form action="" method="post">
                <div class="row">
                    <div class="col-md-2">
                        <h4>Εκδόσεις</h4>
                        <select class="form-control" name="search_publisher">
                            <option value="">Επιλέξτε Εκδόσεις</option>
                            <?php
                            foreach($publishers as $p){
                                ?>
                                <option value="<?php echo $p; ?>" <?php echo @$_POST['search_publisher'] === $p ? 'selected' : ''; ?> ><?php echo $p; ?></option>
                                <?php
                            }
                            ?>
                        </select>
                    </div>
                    <div class="col-md-2">
                        <h4>Χρονολογία</h4>
                        <select class="form-control" name="search_year">
                            <option value="">Επιλέξτε Χρονολογία</option>
                            <?php
                            foreach($years as $y){
                                ?>
                                <option value="<?php echo $y; ?>" <?php echo @$_POST['search_year'] === $y ? 'selected' : ''; ?>><?php echo $y; ?></option>
                                <?php
                            }
                            ?>
                        </select>
                    </div>
                    <div class="col-md-2">
                        <h4>Συγγραφέας</h4>
                        <select class="form-control" name="search_author">
                            <option value="">Επιλέξτε Συγγραφέα</option>
                            <?php
                            foreach($authors as $a){
                                ?>
                                <option value="<?php echo $a; ?>" <?php echo @$_POST['search_author'] === $a ? 'selected' : ''; ?>><?php echo $a; ?></option>
                                <?php
                            }
                            ?>
                        </select>
                    </div>
                    <div class="col-md-3">
                        <h4>Αναζήτηση</h4>
                        <input type="text" name="search_text" value="<?php echo @$_POST['search_text']; ?>" class="form-control" />
                    </div>
                    <div class="col-md-3">
                        <h4><br /></h4>
                        <input type="submit" name="find-all" value="Αναζήτηση" class="btn btn-primary"/>
                        <input type="submit" name="find-with-avail" value="Έχουν Διαθέσιμα" class="btn btn-primary"/>
                    </div>
                </div>
            </form>
            <div class="clearfix">
            </div>
            <table class="table table-primary table-responsive table-striped">
                <thead>
                    <tr>
                        <th>Τίτλος</th>
                        <th>Συγγραφέας</th>
                        <th>Εκδοτικός Οίκος</th>
                        <th>Έτος</th>
                        <th>Διαθέσιμα</th>
                    </tr>
                </thead>
                <tbody>
                <?php
            foreach($books as $b){
                ?>
                <tr>
                    <td><?php echo $b->title; ?></td>
                    <td><?php echo $b->author; ?></td>
                    <td><?php echo $b->EkdotikosOikos; ?></td>
                    <td><?php echo $b->BookYear; ?></td>
                    <td><?php echo $b->Diathesima; ?></td>
                </tr>
                <?php
            }
            ?>
                </tbody>
            </table>
            
        </div>
    </div>
    
</div>
<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/footer.php';
?>
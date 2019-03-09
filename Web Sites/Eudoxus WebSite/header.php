<html lang="en-US">

<head>
    <meta charset="UTF-8">
    <meta name="description" content=" EUDOXUS BOOKS.">
    <meta name="keywords" content="HTML5,form">
    <meta name="author" content="Alkis Kotsas">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="//maxcdn.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css" rel="stylesheet" id="bootstrap-css">
    <script src="//maxcdn.bootstrapcdn.com/bootstrap/4.1.1/js/bootstrap.min.js"></script>
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.5.0/css/all.css" integrity="sha384-B4dIYHKNBt8Bc12p+WXckhzcICo0wtJAoU8YZTY5qE0Id1GSseTk6S+L3BlXeVIU"
        crossorigin="anonymous">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO"
        crossorigin="anonymous" id="bootstrap-css">
    <script src="//cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy"
        crossorigin="anonymous"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
    <link rel="stylesheet" type="text/css" href="/Eudoxus/styles.css">
    <script src="/Eudoxus/header.js"></script>
    <script src="/Eudoxus/navbar.js"></script>
    <script src="/Eudoxus/jquery-3.3.1.min.js"></script>
    <title>Eudoxus</title>

</head>


   


    <body>
    <header>

        <div class="header" id="myHeader">
            <div class="elements">
                <span>
                    <a href="/Eudoxus/index.php" class="Logo"><img src="/Eudoxus/assets/eudoxus-logo-small.png" alt="logo" class="logo_img"></a>
                </span>
                <span class="english">
                    <a href="/Eudoxus/under_construction/index.php" class="Uktxt"><img src="/Eudoxus/assets/UK.jpg" alt="UK" class="uk"> English</a>

                </span>
            </div>
            <div class="sign_buttons">
                <?php
                if(!@$_SESSION['user_logged_in']){
                ?>
                <a href="/Eudoxus/register1/index.php"><button>Εγγραφή</button></a>
                <a href="/Eudoxus/log_in/index.php"><button>Είσοδος</button></a>
                <?php
                }
                else{
                    ?>
                    <a href="/Eudoxus/profile/index.php" class="btn btn-primary"><?php echo $_SESSION['user']['name'] . ' ' . $_SESSION['user']['surname']; ?></a>
                    <a href="/Eudoxus/logout.php" class="btn btn-danger">Logout</a>
                    <?php
                }
                ?>
            </div>
        </div>
    </header>


        <div class="navbar navbar-expand-md navbar-dark bg-dark mb-4" role="navigation">
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarCollapse"
                aria-controls="navbarCollapse" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarCollapse">
                <ul class="navbar-nav mr-auto">
                    <li class="nav-item active">
                        <a class="nav-link" href="/Eudoxus/index.php">Αρχική Σελίδα <span class="sr-only">(current)</span></a>
                    </li>
                    <li class="nav-item active">
                        <a class="nav-link" href="/Eudoxus/under_construction//index.php">Ανακοινώσεις <span class="sr-only">(current)</span></a>
                    </li>
                    <li class="nav-item dropdown active">
                        <a class="nav-link dropdown-toggle" id="dropdown1" data-toggle="dropdown" aria-haspopup="true"
                            aria-expanded="false">Φοιτητές</a>
                        <ul class="dropdown-menu" aria-labelledby="dropdown1">
                            <li class="dropdown-item"><a href="/Eudoxus/dilosi1/index.php">Δήλωση συγγραμμάτων</a></li>
                            <li class="dropdown-item"><a href="/Eudoxus/under_construction/index.php">Ανταλλαγή συγγραμμάτων</a></li>
                        </ul>
                    </li>
                    <li class="nav-item active">
                        <a class="nav-link" href="/Eudoxus/under_construction/index.php">Εκδότες <span class="sr-only">(current)</span></a>
                    </li>
                    <li class="nav-item active">
                        <a class="nav-link" href="/Eudoxus/under_construction/index.php">Γραματεία Τμημάτων <span class="sr-only">(current)</span></a>
                    </li>

                    <li class="nav-item dropdown active">
                        <a class="nav-link dropdown-toggle" id="dropdown1" data-toggle="dropdown" aria-haspopup="true"
                            aria-expanded="false">Συγγράμματα</a>
                        <ul class="dropdown-menu" aria-labelledby="dropdown1">
                            <li class="dropdown-item" ><a href="/Eudoxus/search/index.php">Βάση συγγραμμάτων</a></li>
                            <li class="dropdown-item" ><a href="/Eudoxus/under_construction/index.php">Επιλεγμένα Συγγράμματα</a></li>
                        </ul>
                    </li>
                    <li class="nav-item active">
                        <a class="nav-link" href="/Eudoxus/under_construction/index.php">Σημεία Διανομης<span class="sr-only">(current)</span></a>
                    </li>
                    <li class="nav-item active">
                        <a class="nav-link" href="/Eudoxus/under_construction/index.php">Βιβλιοθήκες<span class="sr-only">(current)</span></a>
                    </li>

                    <li class="nav-item dropdown active">
                        <a class="nav-link dropdown-toggle" id="dropdown1" data-toggle="dropdown" aria-haspopup="true"
                            aria-expanded="false">Βοήθεια</a>
                        <ul class="dropdown-menu" aria-labelledby="dropdown1">
                            <li class="dropdown-item"><a href="/Eudoxus/questions.php">Συχνές Ερωτήσεις</a></li>
                            <li class="dropdown-item"><a href="/Eudoxus/under_construction/index.php">Επικοινωνία</a></li>
                        </ul>
                    </li>


                </ul>
            </div>
        </div>
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

    <title>Euro-Tripper</title>



</head>

<body>
    <header data-position="fixed">
        <div class="logo"><img src="./assets/logo.png" alt=logo class="responsive"></div>
        <div class="profile">
            <i class="fas fa-user"></i>
            <a href=""><span>User</span></a>
        </div>
    </header>
    <main id="main">
        <div class="ui-grid-a ui-responsive">
            <div class="ui-block-a">
                <h2>Favorites</h2>
                <hr>
                <ol>
                    <li>Hotel Transilvania</li>
                    <li>Hotel 2</li>
                </ol>
                <h2>Reviews</h2>
                <hr>
                <ol>
                    <li>Hotel Transilvania</li>
                    <span class="fa fa-star checked"></span>
                    <span class="fa fa-star checked"></span>
                    <span class="fa fa-star checked"></span>
                    <span class="fa fa-star"></span>
                    <span class="fa fa-star"></span>
                    <li>Hotel 2</li>
                    <span class="fa fa-star checked"></span>
                    <span class="fa fa-star checked"></span>
                    <span class="fa fa-star checked"></span>
                    <span class="fa fa-star checked"></span>
                    <span class="fa fa-star checked"></span>

                </ol>
            </div>

            <div class="ui-block-b">
                <div class="panel panel-default">
                    <div class="panel-heading">
                        <h1>My Bookings</h1>
                        <hr>
                    </div>
                    <ul class="all-bookings">
                        <li class="hotel-details">
                            <div class="flex">
                                <div class="hotel-img">
                                    <img src="../rooms/room-2.jpg" alt=hotel-image class="hotel-img">
                                </div>
                                <div class="vertical-row"></div>
                                <div>
                                    <div class="hotel-name">
                                        <h3>Hotel transilvania</h3>
                                        <p>this is some info for the current hotel, and again and again and again and
                                            again
                                            and again and again and again and again and again and again and again and
                                            again
                                            and again and again </p>
                                    </div>
                                    <div class="hotel-place">
                                        <h5>Athens</h5>
                                        <h5>Patisia</h5>
                                    </div>
                                    <div class="room-view-button">
                                        <input type="button" data-inline="true" value="Room Overview">
                                    </div>
                                </div>
                            </div>
                            <div class="ui-grid-c" id="card-box">

                                <div class="ui-block-a" id="bl">total cost</div>
                                <div class="ui-block-b" id="bl">stay from</div>
                                <div class="ui-block-c" id="bl">leave on</div>
                                <div class="ui-block-d" id="bl">room type:Double</div>

                            </div>


                            <hr>
                        </li>
                        <ul>
                </div>
            </div>


    </main>

    <div data-role="footer" data-position="fixed">
        <div class="ui-grid-c" id="footer-box">

            <div class="ui-block-a" id="fl">

            </div>
            <div class="ui-block-b" id="fl">
                <p>Coded by Alkis kotsas </p>
            </div>
            <div class="ui-block-c" id="fl">
                &middot; &copy;Euro-Triper 2018
            </div>

            <div class="ui-block-d" id="fl">
                <a href="">About Us</a>
                <span>|</span>
                <a href="">Contact Us</a>
            </div>
        </div>
    </div>

    </div>


</body>

</html>
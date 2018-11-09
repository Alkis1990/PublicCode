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
    <header>
        <div class="logo"><img src="./assets/logo.png" alt=logo class="responsive"></div>
        <div class="profile">
            <i class="fas fa-user"></i>
            <a href=""><span>User</span></a>
        </div>
    </header>
    <main id="main">
        <div class="ui-grid-a ui-responsive">
            <div class="ui-block-a">
                <section>
                    <div>
                        <select class="guests" id="guests">
                            <option value="" disabled selected>guests</option>
                            <option value="one">one</option>
                            <option value="two">two</option>
                        </select>
                    </div>
                    <div>
                        <select class="roomtype" id="roomtype">
                            <option value="" disabled selected>roomtype</option>
                            <option value="single">single</option>
                            <option value="double">double</option>
                        </select>
                    </div>
                    <div>
                        <select class="city" id="city">
                            <option value="" disabled selected>City</option>
                            <option value="Athens">Athens</option>
                            <option value="London">London</option>
                        </select>
                        <div data-role="range">
                            <div data-role="main" class="ui-content">
                                <form method="post" action="/action_page_post.php">
                                    <div data-role="rangeslider">
                                        <label for="price-min">Price:</label>
                                        <input type="range" name="price-min" id="price-min" value="200" min="0" max="1000">
                                        <label for="price-max">Price:</label>
                                        <input type="range" name="price-max" id="price-max" value="800" min="0" max="1000">
                                    </div>
                                    <div class="datesin">
                                    <input placeholder="Arrive" class="form-control" type="text" onfocus="(this.type='date')"  id="Arrive" name="trip" value=""/> 
                                    </div>
                                    <div class="dateout">
                                    <input placeholder="Leave" class="form-control" type="text" onfocus="(this.type='date')"  id="Leave" name="trip" value=""/> 
                                    </div>
                                    <input type="submit" data-inline="true" value="search">
                                </form>
                            </div>
                        </div>
                    </div>
                </section>
            </div>

            <div class="ui-block-b">
                <div class="panel panel-default">
                    <div class="panel-heading">
                        <h1>Search Results</h1>
                        <hr>
                    </div>
                    <ul class="all-results">
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
                            <div class="ui-grid-b" id="card-box">

                                <div class="ui-block-a" id="bl">cost per night</div>
                                <div class="ui-block-b" id="bl">count of guests</div>
                                <div class="ui-block-c" id="bl">room type:Double</div>

                            </div>


                            <hr>
                        </li>
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

                                <div class="ui-block-a" id="bl">cost per night</div>
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
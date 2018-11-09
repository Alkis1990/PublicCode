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
        <div class="ui-grid-solo ui-responsive">
            <div class="ui-block-a">
                <div class="ui-grid-b ui-responsive">
                    <div class="ui-block-a">
                        <div class="ui-bar ui-bar-a">
                            Hotel transilvania,Athens,Patisia
                        </div>
                    </div>
                    <div class="ui-block-b">
                        <div class="ui-bar ui-bar-a">
                            Reviews
                            <span class="fa fa-star checked"></span>
                            <span class="fa fa-star checked"></span>
                            <span class="fa fa-star checked"></span>
                            <span class="fa fa-star"></span>
                            <span class="fa fa-star"></span>
                        </div>
                    </div>
                    <div class="ui-block-c">
                        <div class="ui-bar ui-bar-a">
                            Cost Per Night
                        </div>
                    </div>

                </div>

                <div class="hotel-img">
                    <img src="../rooms/room-2.jpg" alt=hotel-image class="hotel-img">
                </div>

            </div>
            <div class="ui-grid-d ui-responsive">
                <div class="ui-block-a">
                    <div class="ui-bar ui-bar-a">
                        count of guests
                    </div>
                </div>
                <div class="ui-block-b">
                    <div class="ui-bar ui-bar-a">
                        room type
                    </div>
                </div>
                <div class="ui-block-c">
                    <div class="ui-bar ui-bar-a">
                        parking
                    </div>
                </div>
                <div class="ui-block-d">
                    <div class="ui-bar ui-bar-a">
                        wifi
                    </div>
                </div>
                <div class="ui-block-e">
                    <div class="ui-bar ui-bar-a">
                        pet friendly
                    </div>
                </div>
            </div>
            <hr>
            <div class="hotel-description">
                <h4>Hotel-Description</h4>
                <p>this is some info for the current hotel, and again and again and again and
                    again
                    and again and again and again and again and again and again and again and
                    again
                    and again and again </p>
            </div>
            <div class="book-now">
                <input type="button" data-inline="true" value="Book Now">
            </div>

            <hr>
            <div class="map">
                <h2>Hotel Location</h2>
            </div>
            <div class="mapouter">
                <div class="gmap_canvas"><a href="https://www.pureblack.de"></a>
                    <iframe src="https://maps.google.com/maps?q=university%20of%20san%20francisco&t=k&z=13&ie=UTF8&iwloc=&output=embed"
                        id="gmap_canvas" frameborder="0" scrolling="no" marginheight="0" marginwidth="0"></iframe>
                </div>
            </div>
            <div class="review">
                <h4>Leave Review</h4>
                <span class="fa fa-star checked"></span>
                <span class="fa fa-star checked"></span>
                <span class="fa fa-star checked"></span>
                <span class="fa fa-star"></span>
                <span class="fa fa-star"></span>
            </div>
            <form action="/html/tags/html_form_tag_action.cfm" method="post">
                <div>
                    <textarea placeholder="Add your Review Here !" class="comments" >
                    </textarea>
                </div>
                </form>
                <div class="submit">
                    <input type="Submit" data-inline="true" value="Submit">
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




</body>

</html>
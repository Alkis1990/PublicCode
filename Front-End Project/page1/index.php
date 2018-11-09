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
        <div class="ui-grid-solo ui-responsive">
            <div class="ui-grid-a ui-responsive">
                <div class="ui-block-a">
                    <select class="form-control" id="city">
                        <option value="" disabled selected>City</option>
                        <option value="Athens">Athens</option>
                        <option value="London">London</option>
                    </select>
                </div>
                <div class="ui-block-b">
                    <select class="form-control" id="roomType">
                        <option value="" disabled selected>Room Type</option>
                        <option value="Single">Single</option>
                        <option value="Double">Double</option>
                    </select>
                </div>
            </div>
            <div class="ui-grid-a ui-responsive">
                <div class="ui-block-a">
                <input placeholder="Arrive" class="form-control" type="text" onfocus="(this.type='date')"  id="Arrive" name="trip" value=""/> 

                </div>
                <div class="ui-block-b">
                <input placeholder="Leave" class="form-control" type="text" onfocus="(this.type='date')"  id="Leave" name="trip" value=""/> 
                </div>
            </div>
            <div class="Search">
                <input type="button" data-inline="true" value="Search">
            </div>
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
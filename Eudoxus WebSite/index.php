<?php
require_once $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/dbconnect.php';
?>
<?php
require $_SERVER['DOCUMENT_ROOT']."/Eudoxus/header.php";
?>
        <div class="container-fuid">
           

                <div class="col alert alert-warning">
                    <div class="main_contentfluid text-center" style= "padding: 50px 10px">

                        <p>ο χρόνος που απομένει για να λήξουν οι δηλώσεις συγραμμάτων</p>
                        <p id="demo"></p>
                    </div>
                </div>

            </div>
        </div>

    

        <!-- Display the countdown timer in an element -->

        <script>
            // Set the date we're counting down to
            var countDownDate = new Date("Jan 30, 2019 15:37:25").getTime();

            // Update the count down every 1 second
            var x = setInterval(function () {

                // Get todays date and time
                var now = new Date().getTime();

                // Find the distance between now and the count down date
                var distance = countDownDate - now;

                // Time calculations for days, hours, minutes and seconds
                var days = Math.floor(distance / (1000 * 60 * 60 * 24));
                var hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
                var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
                var seconds = Math.floor((distance % (1000 * 60)) / 1000);

                // Display the result in the element with id="demo"
                document.getElementById("demo").innerHTML = days + " Ημέρες " + hours + " Ώρες " +
                    minutes + " λεπτά " + seconds + " Δευτερόλεπτα ";

                // If the count down is finished, write some text 
                if (distance < 0) {
                    clearInterval(x);
                    document.getElementById("demo").innerHTML = "EXPIRED";
                }
            }, 1000);
        </script>

        
<?php
include $_SERVER['DOCUMENT_ROOT'].'/Eudoxus/footer.php';
?>
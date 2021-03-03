<?php

$db_hostname = 'localhost';
$db_database = 'test';
$db_username = 'root';
$db_password = '';

$con = mysqli_connect($db_hostname, $db_username, $db_password, $db_database);

if (mysqli_connect_error()) {
    echo"failed to connect:" . mysqli_connect_error();
}
//make sure that is an input data
if (isset($_POST['degree']) && isset($_POST['other'])) {
    
    //reading the received data and store it in a variable 'input'
    $v1 = $_POST['degree'];
    $v2 = $_POST['other'];
   
    $query = "INSERT INTO ESP8266 (DEGREE,OTHER) VALUES ('+$v1+','+$v2+')";
    
    //store values in table and go back to index.html page
    mysqli_query($con, $query);
}

?>
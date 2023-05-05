<?php
$Temp = $_GET['temp'];                  //get the value of temp variable from the URL
$Humidity = $_GET['hum'];               //get the value of hum variable from the URL
$date = date('m/d/Y h:i:s a', time());  //current date time

//Embedd the temperature and humidity data along with date time in a string
$fileContent = "Temp is ".$Temp."°C and humidity is ".$Humidity." at ".$date."\n";

//Append the created string into a text file.
$status = file_put_contents('log.txt',$fileContent,FILE_APPEND);

//File writing status
if($status)
    echo "Data written successfully.";
else
    echo "Something went wrong!";
?>
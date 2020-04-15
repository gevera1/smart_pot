#!/usr/bin/php
<?php
   $dbhost = '35.182.25.38';
   $dbuser = 'pot';
   $dbpass = 'Pot123456';
    
   $conn = new mysqli($dbhost, $dbuser, $dbpass);
   
   if($conn->connect_error) {
      die('Could not connect: ' . $conn->connect_error);
   }
   
   echo "connected successfully!\n\n";
   
   mysqli_select_db($conn, 'smart_pot');

   $sql = "SELECT * FROM setting WHERE pid = '1'";
   
   $result = $conn->query($sql) or die($conn->error);
   
   if( $result->num_rows > 0 ) {
      	while($row = $result->fetch_assoc()) {
		$id = $row['pid'];
      		$water = $row['water_intense'];
            	$led = $row['light_intense'];
            	$w_freq = $row['water_freq'];
            	$l_freq = $row['light_freq'];
         }
   } else {
	echo "Table empty.\n";
   }
   $command = "./control " . $id . " " . $water . " " . $led . " " . $w_freq . " " . $l_freq;
   system($command);
   
   echo "Performed script successfully\n";
   
   $conn->close();
?>

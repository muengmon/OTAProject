<html>
<body>

<?php


// เพิ่ม     fw_ver   เอาไว้เช็ค firmware version_
$dbname = 'dht_chularat';
$dbuser = 'root';  
$dbpass = 'AdminP@ssw0rd1'; 
$dbhost = 'localhost'; 

$connect = @mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

if(!$connect){
	echo "Error: " . mysqli_connect_error();
	exit();
}

echo "Connection Success!<br><br>";

$ip = $_POST["ip"];
$temperature = $_POST["temperature"];
$humidity = $_POST["humidity"];
$name = $_POST["name"];
$mac_addr = $_POST["mac_addr"];
$fw_ver = $_POST["fw_ver"];
 
/*echo $ip;
echo $temperature;
echo $humidity;
echo $name;
echo $mac_addr;
echo $fw_ver;*/

$check = "SELECT  * FROM dht_device WHERE mac_device = '$mac_addr'";
$result1 = mysqli_query($connect, $check) or die(mysqli_error());
/*echo "<br>".$check;*/
$row_chack=mysqli_fetch_array($result1, MYSQLI_ASSOC);
$num_ck=mysqli_num_rows($result1);
$id_device = $row_chack['id_device'];
$temperature_high=$row_chack['setting_temperature_high'];
$humidity_high=$row_chack['setting_humidity_high'];
$temperature_low=$row_chack['setting_temperature_low'];
$humidity_low=$row_chack['setting_humidity_low'];
//echo "<br>id-->".$id_device."th-->".$temperature_high."hh-->".$humidity_high."tl-->".$temperature_low."hl-->".$humidity_low;
if($num_ck > 0)
{//อัพเดท
    $query = "UPDATE dht_device SET ip_device = '$ip' , temperature_device = '$temperature' , humidity_device = '$humidity' , name_device = '$name' ,fw_ver_device = '$fw_ver' WHERE mac_device = '$mac_addr' ";
	$result = mysqli_query($connect,$query);

	echo "update Success!<br>";
	if( $temperature > $temperature_high or $temperature < $temperature_low or $humidity < $humidity_low or $humidity > $humidity_high  )
	{ 	
		if( $temperature < $temperature_low ){ $alert_name ='Low Temperature';}
		if( $temperature > $temperature_high ){ $alert_name ='High Temperature';}
		if( $humidity < $humidity_low ){ $alert_name ='Low Humidity';}
		if( $humidity > $humidity_high ){ $alert_name ='High Humidity';}
		$query = "INSERT INTO dht_alert ( id_device , temperature_alert , humidity_alert , Text_alert ) VALUES ('$id_device','$temperature', '$humidity','$alert_name')";
		$result = mysqli_query($connect,$query);
	}
	
}
else 
{//เพิ่มข้อมูล
	$query = "INSERT INTO dht_device (ip_device,temperature_device, humidity_device,name_device,mac_device,fw_ver_device,setting_temperature_low,setting_temperature_high,setting_humidity_low,setting_humidity_high) VALUES ('$ip','$temperature', '$humidity', '$name','$mac_addr','$fw_ver','17','31','21','79')";
	$result = mysqli_query($connect,$query);
	echo "Insertion Success!<br>";
}
?>
</body>
</html>

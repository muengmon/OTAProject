

<?php


// เพิ่ม     fw_ver   เอาไว้เช็ค firmware version_
$dbname = 'dht_chularat';
$dbuser = 'root';  
$dbpass = 'AdminP@ssw0rd1'; 
$dbhost = 'localhost'; 

$mac_addr=$_GET["mac_addr"];
//echo $mac_addr;


$connect = @mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

if(!$connect){
	echo "Error: " . mysqli_connect_error();
	exit();
}
$readmac = "SELECT  * FROM dht_device WHERE mac_device = '$mac_addr'";

$result1 = mysqli_query($connect, $readmac) or die(mysqli_error());
/*echo "<br>".$check;*/
$row_chack=mysqli_fetch_array($result1, MYSQLI_ASSOC);
//echo $readmac;
//echo $row_chack['setting_temperature_high'];
$data22=array("mac_addr"=> $row_chack['mac_device'],"setting_temperature_low" =>$row_chack['setting_temperature_low'],"setting_temperature_high" =>$row_chack['setting_temperature_high'],"setting_humidity_low" =>$row_chack['setting_humidity_low'],"setting_humidity_high" =>$row_chack['setting_humidity_high']);

echo json_encode($data22);

?>

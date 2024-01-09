<?php
require 'includ/function/config.php';
$reqData=$_POST["reqData"];

    $sql = "SELECT * FROM dht_device WHERE id_device ='".$reqData."'";
    $result = $db->query($sql);
    $row = $result->fetch_assoc();
    echo json_encode($row); 

?>
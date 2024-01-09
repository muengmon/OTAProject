<!DOCTYPE html>
<html lang="en">
<?php require 'includ/function/config.php'; 
$sql_Count = "SELECT MAX(id_device)as countdata  FROM dht_device";
$result_Count = $db->query($sql_Count);
$row_Count = $result_Count->fetch_assoc();

$Count_data = $row_Count['countdata'];
?>
<head>
  <!-- Required meta tags -->
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <title>Temp CHG</title>
  <!-- base:css -->
  <link rel="stylesheet" href="includ/css/typicons.css">
  <link rel="stylesheet" href="includ/css/vendor.bundle.base.css">
  <!-- endinject -->
  <!-- plugin css for this page -->
  <!-- End plugin css for this page -->
  <!-- inject:css -->
  <link rel="stylesheet" href="includ/css/style.css">
  <!-- endinject -->
  <link rel="shortcut icon" href="img/favicon.png" />
  <link rel="stylesheet" href="includ/css/bootstrap.min.css">
  <script src="includ/js/jquery-3.1.1.min.js"></script>
  <script src="includ/js/jquery-3.1.1.min.js/popper.min.js"></script>
  <script src="includ/js/jquery-3.1.1.min.js/bootstrap.bundle.min.js"></script>
  <link href="includ/css/led-digital-7.css" rel="stylesheet">
  <link href="includ/css/styletext.css" rel="stylesheet">
  



</head>
<div class="container-scroller">
    <!-- partial:partials/navbar.php -->
    <?php require 'partials/navbar.php'; ?>
    <!-- partial:partials/partial.php -->
    <?php require 'partials/partial.php'; ?>
    <div class="container-fluid page-body-wrapper">        
      <!-- partial:partials/_settings-panel.html -->
      <?php //equire 'partials/settings-panel.php'; ?>
      <!-- Main -->
      <!-- partial:partials/_sidebar.html -->
      <?php require 'partials/sidebar.php'; ?>
      <!-- partial Content -->
      <?php require 'partials/content.php'; ?>
      <!-- content-wrapper ends -->
      <!-- partial:partials/_footer.html -->
      <?php require 'partials/footer.php'; ?> 
      <!-- main-panel ends -->
    </div>
    <!-- page-body-wrapper ends -->
</div>
  <!-- container-scroller -->


  <!-- base:js -->
  <script src="includ/js/vendor.bundle.base.js"></script>
  <!-- endinject -->
  <!-- Plugin js for this page-->
  <script src="includ/chart.js/Chart.min.js"></script>
  <!-- End plugin js for this page-->
  <!-- inject:js -->
  <script src="includ/js/off-canvas.js"></script>
  <script src="includ/js/hoverable-collapse.js"></script>
  <script src="includ/js/template.js"></script>
  <script src="includ/js/settings.js"></script>
  <script src="includ/js/todolist.js"></script>
  <!-- endinject -->
  <!-- Custom js for this page-->
  <script src="includ/js/dashboard.js"></script>
  <!-- End custom js for this page-->
  <script>
    let today = new Date().toISOString().slice(0, 10);
    document.getElementById("date").innerHTML = today;
  </script>
  <script type="text/javascript">
function refData (reqData) {
  for(let reqData=0;reqData<=<?=$Count_data;?>;reqData++){
		$.ajax({
			type: 'POST',
			url: 'getDataSource.php',
			data: { 'reqData': reqData},
			dataType: 'json',
			success: function (responseText) {
				var var_temperature = parseFloat(responseText.temperature_device).toFixed(2);
				var var_humidity = parseFloat(responseText.humidity_device).toFixed(2);
				var var_time = responseText.time_device;
				var var_name = responseText.name_device;
        var var_temperature_high = responseText.setting_temperature_high;
        var var_temperature_low = responseText.setting_temperature_low;
        var var_humidity_high = responseText.setting_humidity_high;
        var var_humidity_low = responseText.setting_humidity_low;


				if(var_temperature>var_temperature_high  ){ var ColorTemp="#ff0000"; }
				else if(var_temperature< var_temperature_low ){ var ColorTemp="#00ffff"; }
				else{var ColorTemp="#33ff00";}
				if(var_humidity> var_humidity_high ){ var ColorHum="#ff0000"; }
				else if(var_humidity< var_humidity_low ){ var ColorHum="#00ffff"; }
				else{var ColorHum="#33ff00";}
				
				$("#txt_temperature_"+reqData).css("color",ColorTemp);
				$("#txt_humidity_"+reqData).css("color",ColorHum);
				$("#txt_time_"+reqData).css("color",ColorHum);
				$("#txt_name_"+reqData).css("color","#000000");

				$("#txt_name_"+reqData).html("<p><font size='2'>"+ var_name +"</font></p>");
				$("#txt_temperature_"+reqData).html("<p class='a'>"+var_temperature+"<font size='6'>°C</font></p>");		
				$("#txt_humidity_"+reqData).html("<p class='a'>"+var_humidity+"<font size='6'>%</font></p>");
				$("#txt_time_"+reqData).html("<p class='c'>"+ convertToDateThai(new Date(var_time)) +" "+ new Date(var_time).toLocaleTimeString() +"</p>");
				
			},error: function(jqXHR, textStatus, errorThrown) {console.log(errorThrown + ': ' + textStatus);}
		});
	}
}
function convertToDateThai( date ) {
        var month_th = [
            "",
            "ม.ค.", 
            "ก.พ.", 
            "มี.ค.",
            "เม.ย.",
            "พ.ค.",
            "มิ.ย.",
            "ก.ค.",
            "ส.ค.",
            "ก.ย.",
            "ต.ค.",
            "พ.ย.",
            "ธ.ค."
        ];
        return result = date.getDate()+" "+month_th[( date.getMonth()+1 )]+" "+( date.getFullYear()+543 );
    }



setInterval(refData, 1000);
</script>
</body>

</html>


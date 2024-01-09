<!DOCTYPE html>
<html lang="en">
<?php require 'includ/function/config.php'; 
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
<?php
    $id_device = $_GET["id"];
    $sql_data_local = "SELECT * FROM dht_device WHERE id_device = '$id_device' ";
    $result_data_local = $db->query($sql_data_local);
    $row_data_local = $result_data_local->fetch_assoc();
    $Count_data_alond = $row_data_local['id_device'];
    $mac_device_logs = $row_data_local['mac_device'];
    //echo $mac_device_logs."----".$Count_data_alond;
    $perpage = 20;
    if (isset($_GET['page'])) 
    {
      $page = $_GET['page'];
      $pageo = $page - 1;
    } else {
      $page = 1;
      $pageo =$page;
    }
    $start = ($page - 1) * $perpage;
    $totaldata_query="SELECT * FROM dht_alert WHERE id_device = '$Count_data_alond'";
    $resultdata=mysqli_query($db,$totaldata_query)or die("Query failed");
    $total_data= mysqli_num_rows($resultdata);
    $total_page = ceil($total_data/$perpage);

    if ($page==$total_page) 
    {
      $pagen = $total_page;
    } else {
      $pagen = $page + 1;;
    }
   
    //echo $total_page;

    $sql_alert = "SELECT * FROM dht_alert WHERE id_device = '$Count_data_alond' ORDER BY time_alert DESC LIMIT $start,$perpage ";
    $result_alert = $db->query($sql_alert);        
    //echo $sql_alert;
    

      
?>
<body>
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
    <div class="main-panel" >
      <div class="col-xl grid-margin stretch-card flex-column">
        <div class="row" style="height:100%;">
        <!----------------------------------------->
        <div class="col-md-12">
              <div class="card">
                <div class="table-responsive pt-3">
                  <?
                    echo'<h3 class="mb-2 text-titlecase mb-4" style="text-align:center;">'.$row_data_local['name_device'].' V. '.$row_data_local['fw_ver_device'].'</h3>';
                  ?>
                  <table class="table table-striped project-orders-table">
                    <thead>
                      <tr> 
                        <th class="ml-5" style="text-align:center;">ลำดับ</th>
                        <th style="text-align:center;">Time</th>
                        <th style="text-align:center;">Temperature</th>
                        <th style="text-align:center;">Humidity</th>
                        <th style="text-align:center;">Alert</th>
                      </tr>
                    </thead>
                    <tbody>
                      <?php
                      if($total_page==0)
                      {
                        echo "<tr>";
                          echo "<td style='text-align:center;'>Nodata</td>";
                          echo "<td style='text-align:center;'>Nodata</td>";
                          echo "<td style='text-align:center;'>Nodata</td>";
                          echo "<td style='text-align:center;'>Nodata</td>";                          
                          echo "<td style='text-align:center;'>Nodata</td>";  
                          echo "</tr>"; 
                      }else
                      {
                        $j=$start;
                        while ($row_alert = $result_alert->fetch_array())
                        {  
                          $j++;
                          echo "<tr>";
                          echo "<td style='text-align:center;'>".$j."</td>";
                          echo "<td style='text-align:center;'>".$row_alert['time_alert']."</td>";
                          echo "<td style='text-align:center;'>".$row_alert['temperature_alert']."</td>";
                          echo "<td style='text-align:center;'>".$row_alert['humidity_alert']."</td>";
                          if($row_alert['Text_alert'] == "Low Temperature" OR $row_alert['Text_alert'] == "Low Humidity" )
                          {
                            echo "<td style='text-align:center;color:blue;'>".$row_alert['Text_alert']."</td>";
                          }
                          else if($row_alert['Text_alert'] == "High Temperature" OR $row_alert['Text_alert'] == "High Humidity" )
                          {
                            echo "<td style='text-align:center;color:red;'>".$row_alert['Text_alert']."</td>";
                          }
                          echo "</tr>"; 
                        }
                      }
                      ?>                                          
                    </tbody>
                  </table>
                  
                </div>
              </div>
                <!------------------------------------------------>
                <div style="text-align:center;">
                  <ul class="pagination justify-content-center">
                  <?php
                    if($total_data > 21)
                    {
                      echo "<li class='page-item'><a class='page-link' href='contentlogs.php?id=".$_GET["id"]."&page=1'>First</a></li>";
                      echo "<li class='page-item'><a class='page-link' href='contentlogs.php?id=".$_GET["id"]."&page=".$pageo."'>Previous</a></li>";
                    }
                            
                    if($page>=4)
                    {
                      echo"<li class='page-item'><a class='page-link'>...</a></li>";
                    }
                    for($i=$page-2;$i<=$page+2;$i++)
                    {
                      if($i > 0 and $i <= $total_page)
                      {
                        echo "<li class='page-item'><a class='page-link' href='contentlogs.php?id=".$_GET["id"]."&page=".$i."'>".$i."</a></li>";

                      }
                    }
                    if($total_page >= $page + 3)
                    {
                      echo"<li class='page-item'><a class='page-link'>...</a></li>";
                    }
                    if($total_page > $page  )
                    {
                      echo "<li class='page-item'><a class='page-link' href='contentlogs.php?id=".$_GET["id"]."&page=".$pagen."'>Next</a></li>";
                      echo "<li class='page-item'><a class='page-link' href='contentlogs.php?id=".$_GET["id"]."&page=".$total_page."'>Last</a></li>"; 
                    } 
                  ?>   
                           
                  </ul>
                </div>
                <p class="text-center">ช้อมูลทั้งหมด <?php echo $total_data;?> รายการ</p> 
                <p class="text-center">หน้าทั้งหมด <?php echo $total_page;?> หน้า</p> 
                <!------------------------------------------------>
            </div>
        <!------------------------------------------------>
        </div>
      </div>     
    <!-- content ends -->
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
</body>
</html>

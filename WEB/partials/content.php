<div class="main-panel">
  <div class="content-wrapper">
    <div class="row">
      <div class="col-xl-12 grid-margin stretch-card flex-column">
        <h5 class="mb-2 text-titlecase mb-4">Temperature And Humidity</h5>
        <div class="row">
                <?php
                    for($i=1;$i<=$Count_data;$i++){
                      $sql_row_chack="SELECT * FROM dht_device WHERE id_device = '$i'";
                      $result_row_chack=mysqli_query($db,$sql_row_chack)or die("Query failed");
                      $total_row_chack= mysqli_num_rows($result_row_chack); 
                      if($total_row_chack > 0 )
                      {
                        echo'<div class="col-md-2 grid-margin stretch-card">';
                        echo'<div class="card">';
                        echo'<div class="card-body d-flex flex-column justify-content-between">';
                        echo'<div  align = "center" id="txt_name_'.$i.'"><p><font size="2"></font></p></div>';
                        echo'<div class="FormDigital" id="txt_temperature_'.$i.'" align = "center" ><p class="b"></p>Not Connect</div>';
                        echo'<div class="FormDigital" id="txt_humidity_'.$i.'" align = "center"><p class="b"></p>ไม่สามารถติดต่อได้</div>';
                        echo'<div  id="txt_time_'.$i.'" align = "center"><p class="c"></p></div>';
                        echo'</div>';
                        echo'</div>';
                        echo'</div>';
                      }                
                    }
                ?>
        </div>
      </div>
    </div>
  </div>

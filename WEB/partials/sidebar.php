<nav class="sidebar sidebar-offcanvas" id="sidebar" >
        <ul class="nav">
          <li class="nav-item">
            <a class="nav-link" href="index.php">
              <i class="typcn typcn-device-desktop menu-icon"></i>
              <span class="menu-title">Dashboard</span>
              <!--<div class="badge badge-danger">new</div>-->
            </a>
          </li>
          <li class="nav-item">
      <a class="nav-link" data-toggle="collapse" href="#form-elements" aria-expanded="false" aria-controls="form-elements">
        <i class="typcn typcn-film menu-icon"></i>
        <span class="menu-title">Temp CHG Server</span>
        <i class="menu-arrow"></i>
      </a>
      <div class="collapse" id="form-elements">
        <ul class="nav flex-column sub-menu">
        <?php
            $sql_device = "select * from dht_device";
            $result_device = $db->query($sql_device);
            while ($row_device = $result_device->fetch_array())
            {  
              echo "<li class='nav-item'><a class='nav-link' href='contenttemp.php?id=".$row_device['id_device']."'>".$row_device['name_device']."</a></li>";
            }
        ?>   
        </ul>
      </div>
    </li>
    <li class="nav-item">
      <a class="nav-link" data-toggle="collapse" href="#Logs" aria-expanded="false" aria-controls="Logs">
        <i class="typcn typcn-document-text menu-icon"></i>
        <span class="menu-title">Logs CHG Server</span>
        <i class="menu-arrow"></i>
      </a>
      <div class="collapse" id="Logs">
        <ul class="nav flex-column sub-menu">
        <?php 
          $sql_device = "select * from dht_device";
          $result_device = $db->query($sql_device);
          while ($row_device = $result_device->fetch_array())
          { 
              echo "<li class='nav-item'><a class='nav-link' href='contentlogs.php?id=".$row_device['id_device']."'>".$row_device['name_device']."</a></li>";
          }
        ?> 
        </ul>
      </div>
    </li>
        </ul>
</nav>
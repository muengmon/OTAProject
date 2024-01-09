<nav class="navbar col-lg-12 col-12 p-0 fixed-top d-flex flex-row">
      <div class="navbar-brand-wrapper d-flex justify-content-center">
        <div class="navbar-brand-inner-wrapper d-flex justify-content-between align-items-center w-100">
          <a class="navbar-brand brand-logo" href="index.php"><img src="img/logo.png" alt="logo"/></a>
          <a class="navbar-brand brand-logo-mini" href="index.php"><img src="img/logo-mini.png" alt="logo"/></a>
          <button class="navbar-toggler navbar-toggler align-self-center" type="button" data-toggle="minimize">
            <span class="typcn typcn-th-menu"></span>
          </button>
        </div>
      </div>
      <div class="navbar-menu-wrapper d-flex align-items-center justify-content-end">
        <ul class="navbar-nav mr-lg-2">
          <li class="nav-item nav-profile dropdown">
            <span class="nav-profile-name">Chularat Hospital Temp Server</span>
          </li>
          <li class="nav-item nav-user-status dropdown">
              <p class="mb-0"><img src="img/favicon.png" alt="favicon"/></a></p>
          </li>
        </ul>
        <ul class="navbar-nav navbar-nav-right">
          <li class="nav-item nav-date dropdown">
            <a class="nav-link d-flex justify-content-center align-items-center" href="javascript:;">
              <i class="typcn typcn-calendar"></i>
              <h6 class="date mb-0">
                <?
                $date = date("d-m-Y");
                echo $date ;
               ?>
               </h6>
              
            </a>
          </li>
          <li class="nav-item dropdown">
            <a class="nav-link count-indicator dropdown-toggle d-flex justify-content-center align-items-center" id="messageDropdown" href="index.php">
              <i class="typcn typcn-cog-outline mx-0"></i>
              <!--<span class="count"></span>--->
            </a>
          </li>
        </ul>
        <button class="navbar-toggler navbar-toggler-right d-lg-none align-self-center" type="button" data-toggle="offcanvas">
          <span class="typcn typcn-th-menu"></span>
        </button>
      </div>
    </nav>
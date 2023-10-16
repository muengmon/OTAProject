void ShowDisplay (float av,float t,float h)
{    String ssidSHOW = WiFi.SSID();
    String IdNameSHOW = IdName;
     
  //===============================SSID==================================
  display.clearDisplay();
   display.setTextColor(WHITE);
   display.setCursor(0,0);
  // Display static text
  display.println("SSID: ");
  display.setCursor(30,0);
  // Display static text
  display.println(ssidSHOW);
  //===============================FirmwareVer==================================
  //display.clearDisplay();
   display.setTextColor(WHITE);
   display.setCursor(70,10);
  // Display static text
  display.println("v:= ");
  display.setCursor(95,10);
  // Display static text
  display.println(FirmwareVer);

  //=============================== name ==================================
   display.setTextColor(WHITE);
   display.setCursor(0,20);
  // Display static text
  display.println("name: ");
  display.setCursor(30,20);
  // Display static text
  display.println(IdNameSHOW);
     
     //A04
  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.println("A0 :");
  display.setCursor(30, 30);
  // Display static text
  display.println(av);

///temp
   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(0,40);
  // Display static text
  display.println("T :");
  display.setCursor(20,40);
  // Display static text
  display.println(t);

//humi
display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(70,40);
  // Display static text
  display.println("H :");
  display.setCursor(95,40);
  // Display static text
  display.println(h);

//temp+av

   display.setTextColor(WHITE);
   display.setCursor(0,50);
  // Display static text
  display.println("T + a0 :");
  display.setCursor(70,50);
  // Display static text
  display.println(t+av);
  display.display(); 
  delay(100);

/*mac

   display.setTextColor(WHITE);
   display.setCursor(0,60);
  // Display static text
  display.println("mac :");
  display.setCursor(30,60);
  // Display static text
  display.println(mac_address);
  display.display(); 
  delay(100);

  */
  // delay(10000);
 // display.clearDisplay();
  }

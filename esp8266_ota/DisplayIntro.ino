void DisplayIntro()
{
  String ssid = WiFi.SSID(); 
  String ip_Address = WiFi.localIP().toString();
  String maddress = WiFi.macAddress();
  
    display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("!! WiFi connected !!");
 display.setTextSize(1);
   
   //===============================SSID==================================
   display.setTextColor(WHITE);
   display.setCursor(0,20);
  // Display static text
  display.println("SSID : ");
  display.setCursor(30,20);
  // Display static text
  display.println(ssid);
  
  //===============================IP========================================
  
  display.setCursor(0, 40);
  display.println("IP  : ");
  display.setCursor(30,40);
  // Display static text
  display.println(ip_Address);
  display.display(); 

//===============================mac========================================

   display.setTextColor(WHITE);
   display.setCursor(0,50);
  // Display static text
  display.println("mac:");
  display.setCursor(20,50);
  // Display static text
  display.println(maddress);
  display.display(); 
  delay(100);


  
 delay(5000);
display.clearDisplay();

  }


void SHOWTEMP(float H,float T,float F,String FirmwareVer)
{
   display.clearDisplay();
   display.setTextColor(WHITE);
   display.setCursor(0,0);
  // Display static text
  display.println("Ver : ");
  display.setCursor(30,0);
  // Display static text
  display.println(FirmwareVer);


  
   //display.clearDisplay();
    display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(0,40);
  // Display static text
  display.println("T :");
  display.setCursor(20,40);
  // Display static text
  display.println(T);

//humi
display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(70,40);
  // Display static text
  display.println("H :");
  display.setCursor(95,40);
  // Display static text
  display.println(H);
 
 
 display.display();
  }
  
  

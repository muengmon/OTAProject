void WIFI_Reset (){
 if (digitalRead(SET_PIN) == LOW) 
    {digitalWrite(LED_BUILTIN, HIGH);
    
  Serial.println("wifi reset ?.waiting ...");
   display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(30, 0);
      // Display static text
      display.println("wifi reset ?.waiting ...");
      display.display(); 

  WiFiManager wm;
  unsigned long last1;
  SPIFFS.format();
  Serial.println(" reset succes ...");
  digitalWrite(LED_BUILTIN, LOW);
    display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 20);
      // Display static text
      display.println(" *-*reset succes*-*  ");
      display.display(); 
     
 
  wm.resetSettings();
   ESP.reset();
   delay(5000);
    }

  
  
}
  

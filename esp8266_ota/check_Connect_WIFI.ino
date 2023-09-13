  
  void check_Connect_WIFI()
  {
  // เช็คการเชื่อมต่อ WIFI ถ้าไม่มีการเชื่อมต่อให้ restart
unsigned long currentMillis = millis();
// if WiFi is down, try reconnecting
 while ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis_WIFI >=interval_WIFI)) {
     Serial.print(millis());
      Serial.println("Reconnecting to WiFi...");
  
       display.clearDisplay();
       display.setTextColor(WHITE);
       display.setTextSize(1);
       display.setCursor(0, 0);
       display.println("Reconnecting to WiFi...");
       display.display(); 
       
       pinMode(LED_BUILTIN, HIGH); //แสดงไฟ
 /*
      WiFi.disconnect();
      WiFi.reconnect();
   //ESP.restart();       // คำสั่งรีเซ็ต ESP*/

   
  previousMillis_WIFI = currentMillis;
}
       WiFi.setAutoReconnect(true);
       WiFi.persistent(true);
        pinMode(LED_BUILTIN, LOW); //แสดงไฟ

  
  }

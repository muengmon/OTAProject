  
  void check_Connect_WIFI()
  {

       
// if WiFi is down, try reconnecting


// WiFiClient client;
    //const int httpPort = 80;
    // เช็คการเชื่อมต่อ WIFI ถ้าไม่มีการเชื่อมต่อให้ restart
    if (WiFi.status() != WL_CONNECTED)  {
        Serial.println("WIFI  connection failed");
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500); 
        //แสดงในจอ  display
       
       display.clearDisplay();
       display.setTextColor(WHITE);
       display.setTextSize(1);
       display.setCursor(0, 0);
       display.println("WIFI connection failed");
       display.display();
        delay(2000);
    //WiFi.disconnect();
   // WiFi.reconnect();
    
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    }
























/*  
 *   
 *     // เช็คการเชื่อมต่อ WIFI ถ้าไม่มีการเชื่อมต่อให้ restart
        long previousMillis_WIFI = 0;
        long interval_WIFI = 30000;
        long currentMillis_WIFI = millis();
 *   
 *   // while ((WiFi.status() != WL_CONNECTED) && (currentMillis_WIFI - previousMillis_WIFI >=interval_WIFI)) {
  while (WiFi.status() != WL_CONNECTED ) {
     Serial.print(millis());
      Serial.println("Reconnecting to WiFi...");
  
       display.clearDisplay();
       display.setTextColor(WHITE);
       display.setTextSize(1);
       display.setCursor(0, 0);
       display.println("Reconnecting to WiFi...");
       display.display(); 
       
      pinMode(LED_BUILTIN, HIGH); //แสดงไฟ
 // previousMillis_WIFI = currentMillis_WIFI;
   // WiFi.disconnect();
    //WiFi.reconnect();
    ESP.restart();       // คำสั่งรีเซ็ต ESP
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
 
  previousMillis_WIFI = currentMillis_WIFI;
}
    WiFi.setAutoReconnect(true);
     WiFi.persistent(true);
       pinMode(LED_BUILTIN, LOW); //แสดงไฟ
     //delay (5000);
  */
  }



 void DHT21_(String FirmwareVer){
  

 float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
    float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

 SHOWTEMP(h,t,f,FirmwareVer);
  
  //----------------------ส่งค่าไปในฐานข้อมูล SQL -----------------------------------
// กำหนดเวลาในการส่งข้อมูลSQL
    now = millis();
   if (now - lastMeasure > TimesendData)
  {
    lastMeasure=millis();
    SendToSqlServer(h,t,f);
    digitalWrite(LED1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200); 
  }

}

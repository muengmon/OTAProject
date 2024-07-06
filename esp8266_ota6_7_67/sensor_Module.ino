void sensor_Module ()
{

  String ssidSHOW = WiFi.SSID();
  String IdNameSHOW = IdName;
  // val = analogRead(A0);// อ่านค่า Analog ขาA0 เก็บไว้ในตัวแปร Val
  // val = map(val, 0, 1023, -100 , 100 ); // แปลงค่า ระหว่าง 0-1023 เป็น 0-180
  float av = val * 0.1; //ค่าที่จะเอาไปใช้
  String IdName_ = IdName;
  String ip_ = WiFi.localIP().toString();
  ///-----------------Read DHT22----------------------------------------------------
  /*  float h = dht.readHumidity();
    float t = dht.readTemperature();

    float f = dht.readTemperature(true);


    delay(1000);*/
  display.clearDisplay();

  float humidity = dht.readHumidity();
  float temperatureDHT22 = dht.readTemperature();
  if (!isnan(humidity) && !isnan(temperatureDHT22))
  {
    temp = temperatureDHT22;
    humi = humidity;
    //temp
     display.clearDisplay();
       //===============================SSID==================================
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("SSID: ");
  display.setCursor(30, 0);
  // Display static text
  display.println(ssidSHOW);
   //===============================FirmwareVer==================================
  //display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(75, 8);
  // Display static text
  display.println("v:= ");
  display.setCursor(100, 8);
  // Display static text
  display.println(FirmwareVer);

  //=============================== name ==================================
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  // Display static text
  display.println("name: ");
  display.setCursor(30, 20);
  // Display static text
  display.println(IdNameSHOW);
  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 40);
    display.println("tempDHT22 :");
    display.setCursor(70, 40);
    display.print(temperatureDHT22);
    display.println("  C");

    //humi
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 50);
    display.println("humidity :");
    display.setCursor(70, 50);
    display.print(humidity);
    display.println(" %");
  }
  else {
    // Read DS18B20 sensor data
    ds18b20.requestTemperatures();
    float temperatureDS18B20 = ds18b20.getTempCByIndex(0);

    if (temperatureDS18B20 != DEVICE_DISCONNECTED_C && temperatureDS18B20 != 85.0)
    {
      temp = temperatureDS18B20;
       display.clearDisplay();
             //===============================SSID==================================
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("SSID: ");
  display.setCursor(30, 0);
  // Display static text
  display.println(ssidSHOW);
   //===============================FirmwareVer==================================
  //display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(75, 8);
  // Display static text
  display.println("v:= ");
  display.setCursor(100, 8);
  // Display static text
  display.println(FirmwareVer);

  //=============================== name ==================================
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  // Display static text
  display.println("name: ");
  display.setCursor(30, 20);
  // Display static text
  display.println(IdNameSHOW);
  
       display.setTextSize(1);
       display.setTextColor(WHITE);
      display.setCursor(0, 40);
      display.print("DS18B20Temp:");
      display.setCursor(80, 40);
      display.print(temperatureDS18B20);
      display.println(" C");
    }  else {
      // Display error message on OLED if no sensor detected
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Error: No sensor");
      display.setCursor(0, 20);
      display.println("detected or could");
      display.setCursor(0, 40);
      display.println("not read data");
    }
  }
  display.display();
  delay(2000); // รอ 2 วินาที
  // ===============กำหนดเวลาในการส่งข้อมูลSQL======================================================

  now = millis();
  if (now - lastMeasure > TimesendData)
  {
   
    lastMeasure = now;
  
    sendtoSQLServer(ip_, temp, humi, IdName_);
   
    // กำหนดเวลาในการส่งข้อมูลLine
    now1 = millis();
    if (now1 - lastMeasure1 > atoi(TIMEalert) * 60000)
    {
      lastMeasure1 = now1;
      sendlineNotify(temp, humi, IdName_);
      Serial.print("TimeLine_");
      Serial.println(atoi(TIMEalert));

      Serial.print("now1");
      Serial.println(now1);
    }
  }
}

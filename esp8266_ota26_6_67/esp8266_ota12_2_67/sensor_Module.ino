void sensor_Module ()
{
  val = analogRead(A0);// อ่านค่า Analog ขาA0 เก็บไว้ในตัวแปร Val
  val = map(val, 0, 1023, -100 , 100 ); // แปลงค่า ระหว่าง 0-1023 เป็น 0-180
  float av = val * 0.1; //ค่าที่จะเอาไปใช้
  String IdName_ = IdName;
  String ip_ = WiFi.localIP().toString();
  ///-----------------Read DHT22----------------------------------------------------
 /* float h = dht.readHumidity();
  float t = dht.readTemperature();

  float f = dht.readTemperature(true);
*/
   float h = 5;
  float t = 20;

  float f = 45;
  delay(1000);

  ShowDisplay (av, t, h); //แสดงจอ 0.96"

  // ===============กำหนดเวลาในการส่งข้อมูลSQL======================================================

  now = millis();
  if (now - lastMeasure > TimesendData)
  {



    temp = t + av;
    humi = h;
    ip_1 = ip_;

    if (isnan(temp) || isnan(humi))
    {
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println("!!!!!Failed to read DHT22!!!!!");
      display.display();
      ///////

      Serial.println("Failed to read DHT22");
      delay(1000);
      Serial.println("restart");
      delay(1000);
      digitalWrite(pinOutput, LOW);
      delay(1000);
      ESP.restart();       // คำสั่งรีเซ็ต ESP
    }
    else
    {
      Serial.print("Humidity: ");
      Serial.print(humi);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.println(" ℃");
      Serial.print("NAME : ");
      Serial.println(IdName_);
    }
    lastMeasure = now;
    sendtoSQLServer(ip_, temp, humi, IdName_);
    digitalWrite(LED_BUILTIN, HIGH);


    delay(500);
  }
  digitalWrite(LED_BUILTIN, LOW);
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

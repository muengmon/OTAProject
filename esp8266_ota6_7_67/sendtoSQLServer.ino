void sendtoSQLServer(String ip_, float temperature, float humidity, String IdName_)
{

  const char* serverName = "http://aofdiy.thddns.net:9094/WEB/post-connect-data.php";
  String apiKeyValue = "tPmAT5Ab3j7F9";
  //WiFiClient client;
 //-------------------------------------------MQTT-------------------------------------------------------------------------------------------------
 //String storedSSID;
//String storedPASS;
  
  String storedSSID = WiFi.SSID();
  String storedPASS = WiFi.psk();

  // ข้อมูลเซิร์ฟเวอร์ MQTT
const char* mqttServer = "aofdiy.thddns.net";
const int mqttPort = 9091;
const char* mqttUser = "aof"; // ถ้ามี
const char* mqttPassword = "aof172531"; // ถ้ามี
String mqttTopic = "home/arduino/sensor/" + IdName_;
WiFiClient Client;
PubSubClient mqttClient(Client);

 mqttClient.setServer(mqttServer, mqttPort);
//--------------------------------------------------------------------------------------------------------------------------------------------------------
  
   String mac_addr =  WiFi.macAddress();

  // Create an HTTPClient instance
  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  if (!(client, serverName))
  {
     LINE.setToken(line_token);
    LINE.notifySticker(2, 34); // เป็นคำสั่งใช้ ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
    LINE.notify("ระบบแจ้งอุณหภูมิ  " + String(IdName) + "  ไม่สามารถเชื่อมฐานข้อมูลได้ T-T!");
    Serial.println("ไม่สามารถเชื่อมต่อ ฐานข้อมูล");
    //แสดงในจอ  display
    delay(2000);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("connection failed");
    //   ESP.restart();       // คำสั่งรีเซ็ต ESP
  }

  // Prepare your HTTP POST request data
  String httpRequestData = "api_key=" + apiKeyValue
                           + "&ip=" + ip_
                           + "&temperature=" + temperature
                           + "&humidity=" + humidity
                           + "&name=" +IdName_
                           + "&mac_addr=" + mac_addr
                           + "&fw_ver=" + FirmwareVer;

  Serial.print("httpRequestData: ");
  Serial.println(httpRequestData);

  // Send HTTP POST request
  int httpResponseCode = http.POST(httpRequestData);

  // Debug output
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println("Response payload: " + payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println("Error message: " + http.errorToString(httpResponseCode));
  }

  // Free resources
  http.end();
   digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
   // Send an HTTP POST request every 30 seconds
    delay(3000);


  if (!mqttClient.connected()) {
     while (!mqttClient.connected()) {
    Serial.print("กำลังเชื่อมต่อกับเซิร์ฟเวอร์ MQTT...");
    if (mqttClient.connect("ESP8266Client", mqttUser, mqttPassword)) {
      Serial.println("เชื่อมต่อสำเร็จ");
    } else {
      Serial.print("การเชื่อมต่อล้มเหลว, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" ลองใหม่ใน 5 วินาที");
      delay(5000);
    }

  }
  }

  // สร้าง payload เป็น JSON หรือ plain text
  String payload = "{\"temperature\":" + String(temperature) + ", \"humidity\":" + String(humidity) + "}";

  // ส่งข้อมูลไปยัง MQTT broker
  mqttClient.publish(mqttTopic.c_str(), payload.c_str());
  mqttClient.loop();
  Serial.println("ข้อมูล "+payload+"  ส่ง MQTT แล้ว");
   // รอ 5 วินาทีก่อนส่งข้อมูลอีกครั้ง
   //  delay(5000);
  
unsigned long timeout = millis();
while (client.available() == 0) {
  if (millis() - timeout > 1000) {
   
    Serial.println(">>> หมดเวลาเชื่อมต่อ ฐานข้อมูล !");
    client.stop();
    return;
  }
}

// Read all the lines of the reply from server and print them to Serial
/*while (client.available()) {
  String line = client.readStringUntil('\r');
  Serial.print(line);
}*/
Serial.println();
Serial.println("closing connection");

}

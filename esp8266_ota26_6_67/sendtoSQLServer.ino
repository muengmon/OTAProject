void sendtoSQLServer(String ip_, float temperature, float humidity, String IdName_)
{
  const char* serverName = "http://aofdiy.thddns.net:9094/WEB/post-connect-data.php";
  String apiKeyValue = "tPmAT5Ab3j7F9";
  WiFiClient client;

  // Create an HTTPClient instance
  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  if (!(client, serverName))
  {
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

// Send an HTTP POST request every 30 seconds
delay(3000);

unsigned long timeout = millis();
while (client.available() == 0) {
  if (millis() - timeout > 1000) {
    LINE.setToken(line_token);
    LINE.notifySticker(2, 34); // เป็นคำสั่งใช้ ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
    LINE.notify("ระบบแจ้งอุณหภูมิ  " + String(IdName) + "  ไม่สามารถเชื่อมฐานข้อมูลได้ T-T!");
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

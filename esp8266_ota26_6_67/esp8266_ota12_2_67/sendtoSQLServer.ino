void sendtoSQLServer(String ip_, float temperature, float humidity, String IdName_)
{
  const char* host = "aofdiy.thddns.net";
  WiFiClient client;
  const int httpPort = 9094;
  // เช็คการเชื่อมต่อ ฐานข้อมูล
  if (!client.connect(host, httpPort)) {
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


  // This will send the request to the server
  String url = "/WEB/connect.php?";
 // url += "ip=192.168.137.37&temperature=24.50&humidity=31.50&name=AOF,D.I.Y!&mac_addr=A4:CF:12:FD:A4:7F&fw_ver=0.16";
   url +=  ("&ip=") + ip_ +
               ("&temperature=") + temperature +
               ("&humidity=") + humidity +
               ("&name=") + IdName_ +
               ("&mac_addr=") + mac_addr +
               ("&fw_ver=") + FirmwareVer;
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
             "Host: " + String(host) + "\r\n" +
             "Connection: close\r\n\r\n");

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
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");

}

void sendtoSQLServer(String ip_,float temperature,float humidity,String IdName_)
{

 String mac_addr =  WiFi.macAddress();
 WiFiClient client;
   const char* host = "tempchg.synology.me";
    const int httpPort = 80;
   // เช็คการเชื่อมต่อ ฐานข้อมูล 
    if (!client.connect(host, httpPort)) {
        Serial.println("ไม่สามารถเชื่อมต่อ ฐานข้อมูล");
        
        //แสดงในจอ  display
      //  delay(1000);
       display.clearDisplay();
       display.setTextColor(WHITE);
       display.setTextSize(1);
       display.setCursor(0, 0);
       display.println("DB connection failed");
       display.display();
      // ESP.restart();       // คำสั่งรีเซ็ต ESP
      delay(2000);
    }


   // เชื่อมต่อกับ server https  ไม่สามารถใช้ http ได้ 
   else if(client.connect(host, httpPort))
   {
 client.print(String("GET https://tempchg.synology.me/connect1.php?") + 
                          ("&ip=") + ip_ +
                          ("&temperature=") + temperature +
                          ("&humidity=") + humidity +
                          ("&name=") + IdName_ +
                          ("&mac_addr=") + mac_addr +
                          ("&fw_ver=") + FirmwareVer +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 3000) {
                LINE.setToken(line_token);
                LINE.notifySticker(2,34); // เป็นคำสั่งใช้ ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
                LINE.notify("ระบบแจ้งอุณหภูมิ  "+String(IdName)+"  ไม่สามารถเชื่อมฐานข้อมูลได้ T-T!");
                Serial.println(">>> หมดเวลาเชื่อมต่อ ฐานข้อมูล !");
            client.stop();
            return;
        }
    }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line); 
    }
    Serial.println();
       display.clearDisplay();
       display.setTextSize(1);
       display.setTextColor(WHITE);
       display.setCursor(0, 0);
        // Display static text
       display.println("closing connection");
       display.setTextSize(1);
       display.display();
       Serial.println("closing connection");
    delay(2000);
     
  } 

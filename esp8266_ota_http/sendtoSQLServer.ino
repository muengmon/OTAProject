void sendtoSQLServer(String ip_,float temperature,float humidity,String IdName_,String mac_addr)
{
    WiFiClient client;
    HTTPClient http;
  
    const char* serverName = "http://ch3itroom.fortiddns.com:8081/connect.php";
                              

   String apiKeyValue = "tPmAT5Ab3j7F9";


   // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

   // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

   String httpRequestData = "api_key=" + apiKeyValue + "&ip=" + ip_
                          + "&temperature=" + temperature + "&humidity=" + humidity
                          + "&name=" + IdName_ + "&mac_addr=" + mac_addr + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

// Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
  // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
  //  http.addHeader("Content-Type", "application/json");
   // int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
 // }
 // else {
  //  Serial.println("WiFi Disconnected");
 // }
  //Send an HTTP POST request every 30 seconds
  //delay(30000);  
//}
/*
    const int httpPort = 80;
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


   // เชื่อมต่อกับ server https  ไม่สามารถใช้ http ได้ 
 client.print(String("GET https://tempchg.synology.me/connect.php?") + 
                          ("&ip=") + ip_ +
                          ("&temperature=") + temperature +
                          ("&humidity=") + humidity +
                          ("&name=") + IdName_ +
                          ("&mac_addr=") + mac_addr +
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

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line); 
    }
    Serial.println();
    Serial.println("closing connection");
    
     */
  } 

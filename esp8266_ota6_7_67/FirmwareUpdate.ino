//String URL_fw_Version = "http://192.168.77.31/WEB/FW/bin_version.txt";
String URL_fw_Version = "http://aofdiy.thddns.net:9094/WEB//FW/bin_version.txt";

String URL_fw_Bin = "http://aofdiy.thddns.net:9094/WEB/FW/fw.bin";
const char* hostFW = "aofdiy.thddns.net";
const int httpsPortFW = 9094;
WiFiClient client;
/*//float FirmwareVer = 1.0; // กำหนดเวอร์ชั่นเฟิร์มแวร์ปัจจุบัน

  unsigned long previousMillis_2 = 0;
  unsigned long previousMillis_3 = 0;
  const long interval = 60000;
  const long mini_interval = 5000;
*/

void setClock() {
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
}


void FirmwareUpdate() {
  HTTPClient http;
  http.begin(client, URL_fw_Version);
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("payload = " + payload);
      Serial.println("FirmwareVer = " + String(FirmwareVer));
      float payloadfloat = payload.toFloat();
      if (payloadfloat == FirmwareVer) {
        Serial.println("Device already on latest firmware version");
      } else {
        Serial.println("ตรวจพบ FW เวอร์ชั่นใหม่ ");
        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        // Display static text
        display.println("detect FW Vertion.. ");
        // display.setCursor(30, 0);
        // Display static text
        //display.println(ssidSHOW);
        display.display();
        delay(5000);
        
        // t_httpUpdate_return ret = ESPhttpUpdate.update(URL_fw_Bin.c_str());
        //  t_httpUpdate_return ret = ESPhttpUpdate.update(hostFW, httpsPortFW, URL_fw_Bin.c_str());
        t_httpUpdate_return ret = ESPhttpUpdate.update(client, URL_fw_Bin);
        switch (ret) {
          case HTTP_UPDATE_FAILED:
            Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            break;
          case HTTP_UPDATE_NO_UPDATES:
            Serial.println("HTTP_UPDATE_NO_UPDATES");
            break;
          case HTTP_UPDATE_OK:
            Serial.println("HTTP_UPDATE_OK");
            break;
        }
      }
    }
  } else {
    Serial.printf("GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void repeatedCall() {
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis_3) >= interval) {
    previousMillis_3 = currentMillis;
    setClock();
    FirmwareUpdate();
  }

  if ((currentMillis - previousMillis_2) >= mini_interval) {
    static int idle_counter = 0;
    previousMillis_2 = currentMillis;
    Serial.print("Active fw version: ");
    Serial.println(FirmwareVer);
    Serial.print("Idle Loop.... ");
    Serial.println(idle_counter++);
    if (idle_counter % 2 == 0)
     // digitalWrite(LED_BUILTIN, HIGH);
    //else
     // digitalWrite(LED_BUILTIN, LOW);
    if (WiFi.status() != WL_CONNECTED)
      check_Connect_WIFI();
  }
}

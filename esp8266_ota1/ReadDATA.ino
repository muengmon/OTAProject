void ReadDATA ()
{
  String mac_addr =  WiFi.macAddress();
  String payload;
  WiFiClient client;

  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, "http://tempchg.synology.me/readDATA.php?mac_addr=" + mac_addr)) { // HTTP


    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        payload = http.getString();
        //   Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect");
  }

  // DynamicJsonDocument doc(1024);
  // deserializeJson(doc, payload);
  DynamicJsonBuffer jb;
  JsonObject& json = jb.parseObject(payload);
  if (json.success()) {
    // json.printTo(Serial);

    String mac_addr = json["mac_addr"];
    String templow = json["setting_temperature_low"];
    String temphigh = json["setting_temperature_high"];
    Serial.println("mac_addr" + mac_addr);
    Serial.println("setting_temperature_low" + templow);
    Serial.println("setting_temperature_high" + temphigh);

    TempLow  = templow;
    TempHigh = temphigh;
    delay(1000);
  }


  //delay(10000);

}

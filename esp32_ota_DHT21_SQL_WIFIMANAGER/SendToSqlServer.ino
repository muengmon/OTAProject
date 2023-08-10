void SendToSqlServer(float h,float t,float f,String Mac_Addr)
{
  
   HTTPClient http;
    http.begin(HOST_NAME + PATH_NAME + ("?temperature=") + t+
                                       ("&humidity=") + h+ 
                                       ("&Mac_Addr=") + Mac_Addr 
    
    
    ); //HTTP
    int httpCode = http.GET();
        Serial.print(F("Humidity: "));
        Serial.print(h);
        Serial.print(F("%  Temperature: "));
        Serial.print(t);
        Serial.print(F(" C "));
        Serial.print(F("Mac_Addr: "));
        Serial.print(Mac_Addr);

 /* http.begin(HOST_NAME + PATH_NAME +   ("&ip=") + "1.1.1.1" +
                          ("&temperature=") + t +
                          ("&humidity=") + h +
                          ("&name=") + "22" +
                          ("&mac_addr=") + "70-B5-E8-66-C1-66");*/

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
     
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

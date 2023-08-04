void tick(){
  digitalWrite(LED,!digitalRead(LED));
}

void configModeCallback(WiFiManager *myWiFiManager){
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
  ticker.attach(0.2, tick);
}



void setupWIFI() {
 
 pinMode(LED,OUTPUT);
 
  ticker.attach(1,tick);
  
  WiFiManager wm;
  wm.setAPCallback(configModeCallback);
    if( !wm.autoConnect("Temperature CHG") ){
    Serial.println("failed to connect and hit timeout");
    ESP.restart();
    delay(1000);   
  }
  
  ticker.detach();
  digitalWrite(LED, LOW);
  
  delay(100);
  Serial.println("");
  Serial.println("connected...already..WiFi :)");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
}

void Reset_begin() {
 bool ReadSwitch = digitalRead(RESET_PIN);
  if(ReadSwitch == pressed)
  {
   // Serial.println("Pressed Switch.");
   // delay(500);

    Serial.println("Wifi Reset? Pls. waiting 30S..");
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    // Display static text
    display.println("Wifi Reset? Pls. waiting 30S.. ");
    display.setCursor(30, 0);
    display.display();
    // Display static text
    delay(15000);

    Serial.println("WiFi Reset Settings....OK!.");
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.println("Connect FIWI config.. ");
    display.setCursor(30, 20);
    display.println("Temperature CHG.. ");
    display.display();
    delay(15000);
    // คำสั่ง รีเซตค่า
    WiFiManager wm;
    wm.resetSettings();
    ESP.eraseConfig();
    SPIFFS.format();
    delay(3000);
    ESP.restart();
    // delay(3000);

    Serial.println(" reset succes ...");
  }
}

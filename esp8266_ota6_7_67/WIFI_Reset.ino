void Wifi_Reset_begin() {
 
 currentState = digitalRead(RESET_PIN);
  Serial.print("Current state: ");
  Serial.println(currentState); // Add this line to print the current state for debugging

  if (lastState == HIGH && currentState == LOW) {
    Serial.println("Wifi Reset? Pls. waiting 30S..");
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Wifi Reset? Pls. waiting 30S.. ");
    display.display();
    delay(15000);

    Serial.println("WiFi Reset Settings....OK!.");
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Connect WiFi config.. ");
    display.setCursor(0, 20);
    display.println("Temperature CHG.. ");
    display.display();
    delay(15000);

    // Reset WiFi settings
    WiFiManager wm;
    wm.resetSettings();
    ESP.eraseConfig();
    SPIFFS.format();
    delay(3000);
    ESP.restart();

    Serial.println("reset success ...");
  } else if (lastState == LOW && currentState == HIGH) {
    Serial.println("The button is released");
  }

  // save the last state
  lastState = currentState;

}

void Wifi_Reset_begin(){
  currentState = digitalRead(RESET_PIN);
  
 if (lastState == HIGH && currentState == LOW){
    Serial.println("Wifi Reset? Pls. waiting 3S..");
    display.clearDisplay();
   display.setTextColor(WHITE);
   display.setCursor(0,0);
  // Display static text
   display.println("Wifi Reset? Pls. waiting 3S.. ");
   display.setCursor(30,0);
    display.display();
  // Display static text
    delay(3000);

      Serial.println("WiFi Reset Settings....OK!.");
       display.clearDisplay();
        display.setTextColor(WHITE);
        display.setCursor(0,0);
  // Display static text
        display.println("Connect FIWI to config.. ");
        display.setCursor(30,0);
         display.println("Temperature CHG.. ");
        display.display();
      WiFiManager wm;
      wm.resetSettings(); 
      ESP.restart();  
      delay(3000);
     

        
      
 }
  else if (lastState == LOW && currentState == HIGH){
 Serial.println("The button is released");
}
  // save the the last state
  lastState = currentState;
  
}

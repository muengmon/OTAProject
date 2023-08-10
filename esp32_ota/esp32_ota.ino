#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>

#include "cert.h"
const char * ssid = "boysniper_2.4";
const char * password = "m4a1sniperf1r2";
int  LED1 = 2;
String FirmwareVer = {
  "0.1"
};


void connect_wifi();
void firmwareUpdate();
int FirmwareVersionCheck();

unsigned long previousMillis = 0; // will store last time LED was updated
unsigned long previousMillis_2 = 0;
const long interval = 60000;
const long mini_interval = 1000;
struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button_boot = {
  0,
  0,
  false
};



void IRAM_ATTR isr() {
  button_boot.numberKeyPresses += 1;
  button_boot.pressed = true;
}

void setup() {
  //-----------------------------------------------------------------OTA---------------------------------------------------------------------
  
  pinMode(button_boot.PIN, INPUT);
  attachInterrupt(button_boot.PIN, isr, RISING);
  Serial.begin(115200);
  Serial.print("Active firmware version:");
  Serial.println(FirmwareVer);
  pinMode(LED1, OUTPUT);
  connect_wifi();
 //------------------------------------------------------------------------------------------------------------------------------------------
  
}
void loop() {

  //-----------------------------------------------------------------OTA---------------------------------------------------------------------
  if (button_boot.pressed) { //to connect wifi via Android esp touch app 
    Serial.println("Firmware update Starting..");
    firmwareUpdate();
    button_boot.pressed = false;
  }
  repeatedCall();
  digitalWrite(LED1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
  delay(200); 
   //-----------------------------------------------------------------CODE---------------------------------------------------------------------            
  // ใส่ code ตรงนี้

  
}

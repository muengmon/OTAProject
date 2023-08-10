#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>

String mac_addr;

//--------------------------wifi manager-----------------------------------------------------------------
#include <WiFiManager.h>
#include <Ticker.h>
Ticker ticker;
#define LED  2


//-----------------------------wifi reset -------------------------------------------------------------
#define RESET_PIN 5  // GIOP5 pin connected to button

// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;

//--------------------------OTA--------------------------------------------------------------------------
#include "cert.h"

int  LED1 = 2;
String FirmwareVer = {
  "1.0"
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

//--------------------------------------DHT21 -------------------------------------------------
#include "DHT.h"
#define DHTTYPE DHT21   // DHT 22  (AM2302), AM2321
#define DHTPin 4
DHT dht(DHTPin, DHTTYPE);


//--------------------------------connect SQL -------------------------------------------------
const char* host = "tempchg.synology.me";
String HOST_NAME = "https://tempchg.synology.me"; // change to your PC's IP address
String PATH_NAME   = "/insert_temp.php";
//String queryString = "?temperature=30.5";
//----------เวลาในการส่งข้อมูล SQL -------------
int TimesendData = 60000;
long now = millis();
long lastMeasure = 0;
//*   -------------------------------------------DISPLAY จอ OLED -----------------------------------------------

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,OLED_RESET);
void setupOLED (){
  // Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }//delay(2000);
  display.clearDisplay();
  }
//---------------------------------------------------------------------------------------------

void setup() {
Serial.begin(115200);
//--------------------------RESET WIFI -------------------------------------------------------
 pinMode(RESET_PIN, INPUT_PULLUP);
 //-----------------------------------------------------------------WIFI manager--------------

setupWIFI();
setupOLED (); 
  //-----------------------------------------------------------------OTA-----------------------
  
  pinMode(button_boot.PIN, INPUT);
  attachInterrupt(button_boot.PIN, isr, RISING);
  
  Serial.print("Active firmware version:");
  Serial.println(FirmwareVer);
  pinMode(LED1, OUTPUT);
  connect_wifi();
 //----------------------------------------------------------DHT21----------------------------
  dht.begin();

  //============================================WIFI_Manager==================================
//IntroDisplay();
testdrawline();      // Draw many lines

  testdrawrect();      // Draw rectangles (outlines)

  testfillrect();      // Draw rectangles (filled)

  testdrawcircle();    // Draw circles (outlines)

  testfillcircle();    // Draw circles (filled)

  testdrawroundrect(); // Draw rounded rectangles (outlines)

  testfillroundrect(); // Draw rounded rectangles (filled)

  testdrawtriangle();  // Draw triangles (outlines)

  testfilltriangle();  // Draw triangles (filled)

 // testdrawchar();      // Draw characters of the default font
}
void loop() {
     mac_addr = WiFi.macAddress();
     Wifi_Reset_begin();    
  //-----------------------------------------------------------------OTA----------------------
  if (button_boot.pressed) { //to connect wifi via Android esp touch app 
    Serial.println("Firmware update Starting..");
    display.clearDisplay();
   display.setTextColor(WHITE);
   display.setCursor(0,0);
  // Display static text
  display.println("Firmware update Starting.. ");
  display.display();

    firmwareUpdate();
    button_boot.pressed = false;
  }
  repeatedCall();
                        // wait for a second
  digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
  delay(200); 
   //-----------------------------------------------------------------CODE----------------------        
  // ใส่ code ตรงนี้

//--------------อ่านค่า DHT21 --------->> ส่งค่าไป SQL----------------------------------------------
 DHT21_(FirmwareVer,mac_addr,WiFi.SSID());
 
       //--------------------------------------------DISPLAY---------------------------
  
 //
 
 
}

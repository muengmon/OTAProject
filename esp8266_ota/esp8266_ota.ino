#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <time.h>
#include <TridentTD_LineNotify.h>
//----------------------------------DHT -------------------------------------------------------------------------------------------------------------------
#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPin D6
#define pinOutput D5    //ขาไฟเลี้ยง +  dht22

DHT dht(DHTPin, DHTTYPE);
float temp;
float humi;

#define pininput D1
     //ขา เอาไว้รีเซตค่า

//----------------------------------WIFI MANAGER -------------------------------------------------------------------------------------------------------------------
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>




//potentiometer  ตัวปรับค่า
int val; 

//---------------------------------- -------------------------------------------------------------------------------------------------------------------


#include <WiFiClientSecure.h>
#include <CertStoreBearSSL.h>
BearSSL::CertStore certStore;
#include "cert.h"

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-FirmwareVer-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
float FirmwareVer= 0.39;



String ip_1;
String mac_addr;

 long previousMillis = 0;        // will store last time LED was updated
 
// constants won't change:
const long interval = 60000; 

char line_token[50] = "2iMePvASf74v40NHARmYBLTrVSKBBAa4azOjWsWIYAz";
char IdName[50] = "  name ";
char TEMPalert[5] = "00";
char TIMEalert[5] = "00";


bool shouldSaveConfig = false;
int buttonState;




//----------เวลาในการส่งข้อมูล SQL -------------
int TimesendData = 60000;
long now = millis();
long lastMeasure = 0;
//
long now1 = millis();
long lastMeasure1 = 0;






// =====================================================display SSD1306 ================================================================================
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//========================================================================================================================================================
//-----------------------------wifi reset --//ขา เอาไว้รีเซตค่า--------------------------------------------------------
#define RESET_PIN D7  // GIOP7 pin connected to button

// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;


//void connect_wifi();
    unsigned long previousMillis_2 = 0;
    unsigned long previousMillis_3 = 0;        // will store last time LED was updated
    const long interval_3 = 60000;
    const long mini_interval = 1000;

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

  
void setup()
{
  Serial.begin(115200);
   dht.begin();
   
  Serial.println("");
  Serial.println("Start");
  //WiFi.mode(WIFI_STA);
  //connect_wifi();  
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pininput, INPUT_PULLUP); 
  pinMode(RESET_PIN, INPUT_PULLUP);
  pinMode(pinOutput, OUTPUT);
  digitalWrite(pinOutput, HIGH);




//------------------------------------------DisplayWellcome-------------------------------------------------------------------------------------------
//display
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
   delay(2000);
 //------------------------------------------DisplayWellcome-------------------------------------------------------------------------------------------
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30, 0);
  // Display static text
  display.println("Please connect ");
  display.setCursor(0, 20);
  display.println(" SSID =  Temperature Alert");
  display.setCursor(0, 40);
  display.println("Password = password");
  display.setCursor(30, 50);
  display.println("AOF,D.I.Y!");
  display.display(); 


//======================================================================================================================================================
  WIFI_Manager();
  DisplayIntro();
  
  
  Serial.println();
  Serial.print("local ip : ");
  Serial.println(WiFi.localIP());
  Serial.print("Line Token : ");
  Serial.println(line_token);


//============================================แจ้งเตือนใน LINE เปิดเครื่อง==========================================================================================================================================================================
    LINE.setToken(line_token);
   //  LINE.notifySticker(2,34); // เป็นคำสั่งใช้ ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
     LINE.notify("สวัสดีครับระบบแจ้งอุณหภูมิ  "+String(IdName)+"  v : "+FirmwareVer+"  พร้อมแจ้งเตือนแล้วครับ ^-^!");
    

//setClock();
  
}

void loop()
{
  repeatedCall();
  Wifi_Reset_begin();
  FirmwareUpdate();
  sensor_Module ();
  check_Connect_WIFI();
}

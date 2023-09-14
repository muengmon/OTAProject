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
#define SET_PIN D7      //ขา เอาไว้รีเซตค่า

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

//----------------------------------------------------------------------------------------------------------------------------------------------------
float FirmwareVer= 0.2;



String ip_1;
String mac_addr;

 long previousMillis = 0;        // will store last time LED was updated
 
// constants won't change:
const long interval = 60000; 

char line_token[50] = "Input Line notify Token";
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


 //------------เช็ค wifi---------------------------------------------------------------------------
       //  WiFiClient client;    //
       // const int httpPort = 80;

     unsigned long previousMillis_WIFI = 0;
     unsigned long interval_WIFI = 30000;
    //---------------------------------------------------------------------------------------------------

void setClock() {
   // Set time via NTP, as required for x.509 validation
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }

}

  



  

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
  pinMode(SET_PIN, INPUT_PULLUP);
  pinMode(pinOutput, OUTPUT);
  digitalWrite(pinOutput, HIGH);



//============================================แจ้งเตือนใน LINE เปิดเครื่อง==========================================================================================================================================================================
    LINE.setToken(line_token);
   //  LINE.notifySticker(2,34); // เป็นคำสั่งใช้ ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
     LINE.notify("สวัสดีครับระบบแจ้งอุณหภูมิ  "+String(IdName)+"  พร้อมแจ้งเตือนแล้วครับ ^-^!");
    


  

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
 

 

    WIFI_Reset ();
 
 // delay(2000);
//============================================WIFI_Manager=================================================================================================================================================================================
 WIFI_Manager();
//===================================================================================================================================================================================================================================
DisplayIntro();
  Serial.println();
  Serial.print("local ip : ");
  Serial.println(WiFi.localIP());
  Serial.print("Line Token : ");
  Serial.println(line_token);


setClock();
  
}

void loop()
{
  
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500); 
 
 
 check_Connect_WIFI();  //เช็คการเชื่อมต่อ WIFI 
  
  val = analogRead(A0);// อ่านค่า Analog ขาA0 เก็บไว้ในตัวแปร Val
  val = map(val, 0, 1023, -100 , 100 ); // แปลงค่า ระหว่าง 0-1023 เป็น 0-180
  float av = val*0.1; //ค่าที่จะเอาไปใช้
  
   
   
   String IdName_ = IdName;
  Serial.print(".");

///-----------------Read DHT22----------------------------------------------------
       float h = dht.readHumidity();
       float t = dht.readTemperature();
     
       float f = dht.readTemperature(true);
       delay(2000);
  ///====================  แสดงค่าออกจอ  ====================================================

        ShowDisplay (av,t,h,WiFi.SSID(),IdName);

         // กำหนดเวลาในการส่งข้อมูลSQL
    now = millis();
   if (now - lastMeasure > TimesendData)
  {
     
       String ip_ = WiFi.localIP().toString();
        mac_addr = WiFi.macAddress();
   
        temp =t+av;
        humi=h;
        ip_1=ip_;
    
       if(isnan(temp) || isnan(humi))
       {
         display.clearDisplay();
         display.setTextColor(WHITE);
         display.setTextSize(1);
         display.setCursor(0, 0);
         display.println("!!!!!Failed to read DHT22!!!!!");
         display.display(); 
         ///////
 
         Serial.println("Failed to read DHT22");
         delay(1000);
         Serial.println("restart");
         delay(1000);
         digitalWrite(pinOutput, LOW);
         delay(1000);
          ESP.restart();       // คำสั่งรีเซ็ต ESP
       }
      else
      {
         Serial.print("Humidity: ");
         Serial.print(humi);
         Serial.print(" %\t");
         Serial.print("Temperature: ");
         Serial.print(temp);
         Serial.println(" ℃");
         Serial.print("NAME : ");
         Serial.print(IdName_);
        }
    lastMeasure = now;
    sendtoSQLServer(ip_,temp,humi,IdName_,mac_addr);
    //  sendlineNotify(temperature,humidity,count);

        delay(100);   
  }

  // กำหนดเวลาในการส่งข้อมูลLine
      now1 = millis();
    if (now1 - lastMeasure1 > atoi(TIMEalert)*60000)
  {
    lastMeasure1 = now1;
    sendlineNotify(temp,humi,IdName_);
   Serial.print("TimeLine_");
   Serial.println(atoi(TIMEalert));

   Serial.print("now1");
   Serial.println(now1);
  }
   FirmwareUpdate();
  // repeatedCall(); 
}
/*
void connect_wifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("O");
  }                                   
  Serial.println("Connected to WiFi");
}*/

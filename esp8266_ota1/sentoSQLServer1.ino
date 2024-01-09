void sendtoSQLServer1(String ips, float temperature, float humidity, String IdNames)
{
    HTTPClient http;
    WiFiClient client;
    String mac_addr =  WiFi.macAddress();
    int    HTTP_PORT   = 80;
    String HTTP_METHOD = "GET"; // or "POST"
    char   HOST_NAME[] = "tempchg.synology.me"; // hostname of web server:
    String PATH_NAME   = "/connect1.php";
   // String queryString = String("?ip=") + String(ips) + String("&temperature=") + String(temperature)+ String("&humidity=") + String(humidity)+ String("&name=") + String(IdNames)+ String("&mac_addr=")+ String(mac_addr)+ String("&fw_ver=")+ String(FirmwareVer);
    
     String queryString = "?ip=192.168.137.37&temperature=24.50&humidity=31.50&name=  AOF,D.I.Y! &mac_addr=A4:CF:12:FD:A4:7F&fw_ver=0.16";
   
    if(client.connect(HOST_NAME, HTTP_PORT)) {
      Serial.println("Connected to server");
       // send HTTP request header
    client.println("POST " + PATH_NAME +" HTTP/1.1\r\n" +
                 "Host: " + PATH_NAME + "\r\n" +
                 "Connection: close\r\n\r\n");
    
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    
    client.println(); // end HTTP header
    client.println(queryString);
    delay(500);
    } else {
      Serial.println("connection failed");
    }
   
    
    Serial.print("HOST_NAME: ");
    Serial.println(HOST_NAME);
    Serial.print("PATH_NAME: ");
    Serial.println(PATH_NAME);
    Serial.print("WEB : ");
    Serial.println(HOST_NAME + PATH_NAME);
    }

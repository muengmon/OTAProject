// Root certificate for howsmyssl.com
const char IRG_Root_X1 [] PROGMEM = R"CERT(
-----BEGIN CERTIFICATE-----
MIIDmzCCAoOgAwIBAgIUVq0DUfH2Ms9rO5ipHODcaiv7akIwDQYJKoZIhvcNAQEL
BQAwXTELMAkGA1UEBhMCQVUxEzARBgNVBAgMClNvbWUtU3RhdGUxITAfBgNVBAoM
GEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDEWMBQGA1UEAwwNMTkyLjE2OC4xLjE2
NjAeFw0yNDAxMDYwODQ0MzhaFw0yNTAxMDUwODQ0MzhaMF0xCzAJBgNVBAYTAkFV
MRMwEQYDVQQIDApTb21lLVN0YXRlMSEwHwYDVQQKDBhJbnRlcm5ldCBXaWRnaXRz
IFB0eSBMdGQxFjAUBgNVBAMMDTE5Mi4xNjguMS4xNjYwggEiMA0GCSqGSIb3DQEB
AQUAA4IBDwAwggEKAoIBAQCOk/95YJXnVg3gloZKNrd3t+soIBGf3KIyLvGeWHlK
2Dfah9C99pla19v7A2T7sJ6NhAlNaVFJ+Ly+gDFPSCV8K0yQBY0oCYeWGs0RKTrX
GC1oRCnk+fL0mHgx+4T1K5Y9KhRgWi4lPYtUnPDk1odkvWiUBU2YeDE1Cltxe7jc
0JmZXBqRKl8Njq1gAGQGWPl7NxcTYfebE8jFnlXP86D8pf2bup+08ukQDOJSZN0S
MJUHsV9EHmifzc3LeoaXnFqNk1ZaKhYvQTxaNBYp4oxcG7ZuKe9JG9/kU77VgL/R
R5ubRvAVBmD+bF0KYUhKDy5MFFIhImYJXefCdQpp9XdrAgMBAAGjUzBRMB0GA1Ud
DgQWBBTnfRSF1JNYsxjGa/p3VeQPeZ0ZdjAfBgNVHSMEGDAWgBTnfRSF1JNYsxjG
a/p3VeQPeZ0ZdjAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQBI
KYgHuG6Q+1v7Cp0NjiCKacUPEwL3H2sUzbKx7/yXi56awTuFrJGEb3viFwSaCPcF
yrTNYuQ2DstjJXNgnPvaCf+1NIX6hBQKqSSHV1vNUqlkm84hYOGgKFsZhrvZrn8z
hr4b7+Li9Dt+5CphG+YaEeAwONm8TXv8xPViUN6PcJo7jza+LkMVMgio+MfpWc/S
ANgNmHbhEnx9bzSUe2cTpecjXNdgVI+uj2b/vIhhXhLf+pMl3szIURFdLHDbAXef
N/agPmiYEPNnw/zUjTGMLlJZCB400A/DGeXNB20f/SeVML5F6MHM6FlutJClE70s
ppVnPD/MdlizZFSQxS1u
-----END CERTIFICATE-----
)CERT";
void sendtoSQLServer(String ip_, float temperature, float humidity, String IdName_)
{
  


  X509List cert(IRG_Root_X1);
  WiFiClientSecure client;
  client.setTrustAnchors(&cert);
  HTTPClient https;
  const char* host = "https://aofdiy.thddns.net:9090";
  const int httpPort = 9090;
  // เช็คการเชื่อมต่อ ฐานข้อมูล
  if (!https.begin(client,host)) {
    Serial.println("ไม่สามารถเชื่อมต่อ ฐานข้อมูล");

    //แสดงในจอ  display
    delay(500);

  }


  // เชื่อมต่อกับ server https  ไม่สามารถใช้ http ได้
 // else if (client.connect(host, httpPort))
   else
  {
     client.print(String("GET https://aofdiy.thddns.net:9090/WEB/connect.php?&ip=192.168.137.37&temperature=24.50&humidity=31.50&name=  AOF,D.I.Y! &mac_addr=A4:CF:12:FD:A4:7F&fw_ver=0.16")+
                             
  /*  client.print(String("GET") +
                 ("/WEB/connect.php?ip=") + ip_ +
                 ("&temperature=") + temperature +
                 ("&humidity=") + humidity +
                 ("&name=") + IdName_ +
                 ("&mac_addr=") + mac_addr +
                 ("&fw_ver=") + FirmwareVer +*/
                 " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 3000) {

        Serial.println(">>> หมดเวลาเชื่อมต่อ ฐานข้อมูล !");
        client.stop();
        return;
      }
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();

  Serial.println("closing connection");
  delay(500);

}

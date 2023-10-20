void sendlineNotify(float temperature, float humidity, String IdName_)
{

  if (temperature > TempHigh.toInt()) {     //หากอุณหภูมิสูง จะแจ้งเตือนไปยังไลน์
    LINE.setToken(line_token);
    LINE.notifySticker(2,19); // เป็นคำสั่งใช้ ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
    LINE.notify( String(IdName_) + "  อุณหภูมิสูง = " + String(temperature) + " ℃  "   "  ความชื้น = " + String(humidity) + " %");
    delay(1000);
  }
  if (temperature < TempLow.toInt()) {     //หากอุณหภูมิต่ำ จะแจ้งเตือนไปยังไลน์
    LINE.setToken(line_token);
    LINE.notifySticker(2,29); // เป็นคำสั่งใช้ ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
    LINE.notify( String(IdName_) + "  อุณหภูมิต่ำ = " + String(temperature) + " ℃  "   "  ความชื้น = " + String(humidity) + " %");
    delay(1000);
  }

}

void MSGLCD_print(long MESSAGE, uint8_t index, uint8_t typeflag)
{
  Serial.print("In print function: ");
  Serial.println(MESSAGE);
  lcd.setCursor(12, 1);
  if (typeflag == 0)
    lcd.print(Menus[index]);
  if (typeflag == 1)
    lcd.print("Err");
  lcd.setCursor(0, 2);
  //customClear(0,2,19,2);
  String MSG;

  if (MESSAGE < 1000)
  {
    customClear(11, 2, 3, 2); //clear incase prev message was 1000+ (leaving pixles not refreshed)
  }
  if (MESSAGE < 100 && MESSAGE > 9)
  {
    MSG = "0";
    MSG += MESSAGE;
  }

  else if (MESSAGE < 10)
  {
    MSG = "00";
    MSG += MESSAGE;
  }
  else
    MSG += MESSAGE;
  customPrint(MSG, 0, 1); //update this with the custom print function so that its large font

}

void STRINGMSGLCD_print(unsigned char MESSAGE[8], uint8_t index)
{
  if (Menus_unsel[index] == "NULL1")
  {
    lcd.setCursor(0, 0);
    MSGUPDATE |= 0b00000001; //set first flag to true
  }
  if (Menus_unsel[index] == "NULL2")
  {
    lcd.setCursor(8, 0);
    MSGUPDATE |= 0b00000010;
  }
  if (Menus_unsel[index] == "NULL3")
  {
    lcd.setCursor(0, 1);
    MSGUPDATE |= 0b00000100;
  }
  if (Menus_unsel[index] == "NULL4")
  {
    lcd.setCursor(8, 1);
    MSGUPDATE |= 0b00001000;
  }

  CHAR_print(MESSAGE, 8);
}
void pagerefresh()
{
  if (pagelock == 0)
  {
    customClear(0, 0, 20, 4); //clears section of area displaying title and value
    //lcd.setCursor(0, 0);
    //lcd.print("CAN Message!");
    pagelock = 1;
  }
  //if ( (millis() - lcd_timeout > LCDTimeouttime) && MSGUPDATE != 0x0F)
  //{
  //  MSGUPDATE = 0x00; //reset to ensure VCU messges displayed correctly after timeout
  //  customClear(0, 0, 20, 4);
  //}
}

#define boottime 500 //set to 0 for debugging

void customPrint(int lrgnumber, uint8_t hor, uint8_t ver)  //print integer using the large font
{
  customPrint(String(lrgnumber), hor, ver);  //convert int to string and send to main overload fucntion
}


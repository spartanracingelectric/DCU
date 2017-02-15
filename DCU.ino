/* how to add messages to display:
    Update MSGIDS array with the IDs of messages of interest
    Update the Menus array with the IDs of messages of interest (in same order as MSGIDS
    Update the translator function such that it takes in the message and returns the human readable value
    If the message is a priority message (i.e. not driver selectable, then add to the Menus_unsel
    and MSIDs_unsel list instead.

*/

#include <avr/wdt.h> //watch-dog timer


#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <mcp_can.h>
#include <SPI.h>

#include <LED.h>
#define buzzpin 9
//LED buzzer(buzzpin, 1);          //LED library for buzzer timing etc..
LED buzzer;
uint8_t buzzerlock = 0;
unsigned int frequency;           //for globaly storing frequency value sent via CAN


//-----LCD Configurations
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
#define lcdrefreshrate 500        //refresh rate of the LCD
long unsigned lcd_refresh = 0;    //anti fast refresh timer

#define LCDTimeouttime 5000
long unsigned lcd_timeout;
uint8_t MSGUPDATE = 0; //used as a flag to indicate when all 4 messages have been populated on LCD

//CAN BUS configurations
#define CANINT 2
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
MCP_CAN CAN0(10);                 // Set CS to pin 10

//---------------------------Configuriations

//Driver Selectable Options
long unsigned int MSGIDS[] =  {
  0x0A7,  //Pack Voltage  --- 0
  0x0A6,  //Bus Current   --- 1
  0x0A5,  //Car Speed, based on RPM     --- 2
  0x629,  //State of Charge-- 3
  //0x516,//Speed         --- 4
  0x0A9,  //LV Level      --- 5
  //0x0C0   //Torque Setting--- 6
  //0xXXX,//Error         --- 7
}; //store message IDs here

String Menus[] = {  //titles that map out to the IDs in the IDS array
  "Volt",               //  --- 0
  "Amps",               //  --- 1
  "MPH",                //  --- 2
  "SOC",                //  --- 3
  //"MPH",              //  --- 4
  "LV V",           //  --- 5
  //"Torque Setting",     //  --- 6
  //"Err-",             //  --- 7
  //"BMS Error",        //  --- 8
  //"Rinehart Error",   //  --- 9
  //"VCU Error",        //  --- 10
  //"Buzzer"              //  --- 11
};

//Non-Driver Selectable Options
long unsigned int MSGIDS_unsel[] =  {
  //0x622,//BMS error     --- 1
  //0x0AB,//Rinehart error--- 2
  0x511,  //VCU Error 1   --- 3
  0x512,  //VCU Error 2   --- 4
  0x513,  //VCU Error 3   --- 5
  0x514,  //VCU Error 4   --- 6
  0x510   //Buzzer ctrl   --- 7
}; //store message IDs here

String Menus_unsel[] = {  //titles that map out to the IDs in the IDS array
  //"BMS Error",        //  --- 1
  //"Rinehart Error",   //  --- 2
  "NULL1",               //  --- 3  NULLx identifies the location on screen to print the message in
  "NULL2",               //  --- 4
  "NULL3",               //  --- 5
  "NULL4",               //  --- 6
  "Buzzer"              //  --- 7
};
const uint8_t MSGNBR = sizeof(MSGIDS) / 4; //total number of messages in the switch case
const uint8_t MSGNBR_unsel = sizeof(MSGIDS_unsel) / 4;

uint8_t dataflag = 0; //set to 1 by CAN ISR when data on bus, set to 0 once aquired.
long HMSG; //used to store the human redable data.
unsigned char *unsel_HMSG; //used to store raw char data
//encoder
uint8_t select = 0;

void setup()
{

  pinMode(buzzpin, OUTPUT);
  delay(1000);
  lcdbootup();
  encoder_setup();                //config interrupt for button etc..
  CAN_setup();                    //config interrupt for CAN etc...
  Serial.begin(115200);
  Serial.println("SRE-2 CAN Bus initialized");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("   GO SPARTAN");
  lcd.setCursor(0,1);
  lcd.print("RACING ELECTRIC!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting 4 Message...");
  delay(1000);
  wdt_enable(WDTO_2S); //Other options are: _15MS _30MS -60MS _120MS _250MS _500MS _1S _2S _4S _8S
  //dont set the WDT time too low...run risk of bricking the arduino
}

void loop()
{
  wdt_reset();
  statemachine();
  pagerefresh();
  buzzerUpdate(frequency);
}


uint8_t state = 1;
void statemachine()
{
  switch (state)
  {
    case 1:
      //Serial.println("In Case 1");
      if (digitalRead(CANINT) == 0) //CAN message available (triggered by ISR)
      {
        can_isr();
      }

      if (dataflag == 1)
      {
        state = 2;  //go to state 2
        dataflag = 0; //reset data available flag
      }
      break;

    case 2: //check if message is needed (independant of button position)
      //Serial.println("In Case 2");
      state = 1;  //default state is to check for more data if ID not of interest
      if (filter(rxId) == 1) //if data of interest & Driver selectable, go to state 3
      {
        state = 3;
      }
      if (filter_unsel(rxId) == 1) //if data in buffer of high priority (i.e. an error or buzzer)
      {
        state = 6;
      }
      break;

    case 3:

      state = 4;
      break;

    case 4: //Check if data matches the data selected w/ button
      //Serial.println("In Case 4");
      state = 1;  //if no match return to wait for new message
      if (MSGIDS[select] == rxId && millis() - lcd_refresh > lcdrefreshrate)
      {
        lcd_refresh = millis();
        state = 6;
      }
      break;

    case 5: //concatenate multiple messges onto screen (if more than 1 word long)
      Serial.println("In Case 5");
      state = 5; //stay on state 5 until message aquired
      if (digitalRead(CANINT) == 0) //CAN message available (triggered by ISR)
      {
        can_isr();
      }

      if (dataflag == 1)
      {
        dataflag = 0; //reset dataflag
        if(filter_unsel(rxId) == 1) 
        {
        state = 6;  ////VCU Message Available, go to state 6
        }
      }
      if (millis() - lcd_timeout > 500) //if stuck in state 5 (due to unfinished VCU message)
      {
        Serial.println("Clearaed - state 5");
        customClear(0, 0, 20, 4);
        MSGUPDATE == 0x00; //reset to ensure VCU messges displayed correctly after timeout
        state = 1;
      }
      break;

    case 6: //turn to human readable
      Serial.println("In Case 6");
      state = 7;
      if (filter_unsel(rxId) == 0)
      {
        HMSG = translator(rxBuf, rxId);
        Serial.print("HMSG: ");
        Serial.println(HMSG);
      }
      if (filter_unsel(rxId) == 1)
      {
        unsel_HMSG = unsel_translator(rxBuf, rxId);
        if (*unsel_HMSG == 0) //if nothing returned, then go back to state 1 (stuff was done in unsel_translator)
        {
          state = 1;
        }
      }
      break;

    case 7: //print on LCD
      Serial.println("In Case 7");
      lcd_timeout = millis();
      if (filter_unsel(rxId) == 0)
      {
        MSGLCD_print(HMSG, select, filter_unsel(rxId)); //send messege to print and the type of message
      }
      if (filter_unsel(rxId) == 1) //If message from the priority list
      {
        STRINGMSGLCD_print(unsel_HMSG, ADRS_2_index(rxId));
      }
      state = 1;
      if (MSGUPDATE != 0x0F && filter_unsel(rxId) == 1) //if VCU messege not yet interily displayed AND CURRENT message is priority
      {
        state = 5; //go to state 5 to wait for remainder of VCU message
      }
      if (MSGUPDATE == 0x0F) //entire VCU message displayed
      {
        state = 8;
        MSGUPDATE = 0x00;
      }
      break;

    case 8: //timeout state to display the alert for 10 seconds
      //Serial.println("In Case 8");
      state = 8;
      if (millis() - lcd_timeout > LCDTimeouttime) //loop to state 8 until timeout
      {
        Serial.println("Clearaed - state 8");
        customClear(0, 0, 20, 4);
        MSGUPDATE == 0x00; //reset to ensure VCU messges displayed correctly after timeout
        state = 1;
      }

      //clear the SPI buffer to prevent false displaying of info
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      break;
  }
}

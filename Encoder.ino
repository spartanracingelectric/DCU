//All sensor | buttons | switches functions are in this file

// encoder pins
#define PIN_ENC0   3 //int1

uint8_t ENC0prevstate= 1;
uint8_t pagelock = 0;  //used for updating screen upon pressing of button

void enc_isr()
{
  if(ENC0prevstate == 1 && digitalRead(PIN_ENC0) == 0)
  {
    select++;
    pagelock = 0;
  }
  ENC0prevstate = 0;
  if(ENC0prevstate == 0 && digitalRead(PIN_ENC0) == 1)
  ENC0prevstate = 1;
  
  if(select > MSGNBR - 1)
  {
    select = 0;
  }
}

void encoder_setup()
{
  pinMode(PIN_ENC0, INPUT);
  digitalWrite(PIN_ENC0, HIGH); //enable pullup
  attachInterrupt(digitalPinToInterrupt(PIN_ENC0), enc_isr,  CHANGE);
}

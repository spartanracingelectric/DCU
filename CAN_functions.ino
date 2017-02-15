void CAN_setup()
{
  CAN0.begin(CAN_500KBPS, MCP_8MHz);                       // init can bus : baudrate = 500k 
  pinMode(CANINT, INPUT);                            // Setting pin 2 for /INT input
  //attachInterrupt(digitalPinToInterrupt(CANINT), can_isr,  FALLING);
}

void can_isr()
{
  CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
  rxId = CAN0.getCanId();                    // Get message ID
  dataflag = 1;                              // Data available flag
  RAWSerial_print(rxId, rxBuf, len);
}

void RAWSerial_print(long unsigned int ID, unsigned char MSG[8], unsigned char LENGTH)
{
  Serial.print("ID: ");
  Serial.print(ID, HEX);

  Serial.print("  Data: ");
  for (int i = 0; i < LENGTH; i++)             // Print each byte of the data
  {
    if (MSG[i] < 0x10)                    // If data byte is less than 0x10, add a leading zero
    {
      Serial.print("0");
    }
    Serial.print(MSG[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void RAWLCD_print(long unsigned int ID, unsigned char MSG[8], unsigned char LENGTH)
{
  lcd.setCursor(3, 1);
  lcd.print(ID, HEX);
  
  for (int i = 0; i < LENGTH; i++)             // Print each byte of the data
  {
    lcd.setCursor(5 + i * 2, 2);
    lcd.print(MSG[i], HEX);
  }
}

void CHAR_print(unsigned char MSG[8], unsigned char LENGTH)
{
  for (int i = 0; i < LENGTH; i++)
  {
    lcd.write(MSG[i]);
  }
}

//Driver Selectable Filter
uint8_t filter(long unsigned int ID) //checks if ID is in master list
{
  for(uint8_t n = 0; n <= MSGNBR - 1; n++)
  {
    if(ID == MSGIDS[n])
    return 1; //ID present in master list
  }
  return 0; //ID not of interest
}

//Non-Driver Selectable Filter
uint8_t filter_unsel(long unsigned int ID) //checks if ID is of interest
{
  for(uint8_t n = 0; n <= MSGNBR_unsel - 1; n++)
  {
    if(ID == MSGIDS_unsel[n])
    {
        return 1; //ID present in master list
    }
  }
  return 0; //ID not of interest
}

//CAN address to Array conversion
uint8_t ADRS_2_index(long unsigned int ID) //checks if ID is of interest
{
  for(uint8_t n = 0; n <= MSGNBR_unsel - 1; n++)
  {
    if(ID == MSGIDS_unsel[n])
    {
        return n; //ID present in master list
    }
  }
}
long translator(unsigned char MSG[8], long unsigned int ID) //convert data to human readable
{
  switch(ID)
  {
    //-------LITTLE ENDIAN-------------
    //1 char = 1 byte = 8 bits
    //0x00 = 0b_ _ _ _ _ _ _ _ _
    //     MSB 7 6 5 4 3 2 1 0 LSB
    //SHIFT           168 0 
    case(0x0A6): //Motor Controller Current(s)
      return ((MSG[7]<<8) + (MSG[6]<<0));
    break;

    case(0x0A7): //Motor Controller Voltage(s)
      return abs(((MSG[1]<<8) + (MSG[0]<<0))/10.0);
    break;

    case(0x0A9): //12V Battery Voltage
      return abs( (MSG[7]<<8) + (MSG[6]) )/10;
    break;

    case(0x0A5):  //Motor Speed  0.0169 RPM = 1 MPH
      return abs( ((MSG[3]<<8) + (MSG[2]<<0)) )/(10.0*0.0169);
    break;

    case(0x0C0):
      return MSG[0];
    break;
    
    case(0x510):  //Buzzer Control
      frequency = ((MSG[1]<<8) + (MSG[0]<<0));
      buzzer_ctrl( ((MSG[6]<<16) + (MSG[5]<<8) + (MSG[4]<<0)) , (MSG[3]<<8) + (MSG[2]<<0) , MSG[7] );
      return 0;
    break;

    case(0x629):  //SOC - Little Endian thanks to Rusty The Man
      return ( MSG[6]*100.0/0xFF );
    break;

    case(0x516): //Speed
      return MSG[0];
    break;
    //------BIG ENDIAN--------------------

    case(0x626): //SOC INFO

    break;

    case(0x622): //BMS error

    break;

    case(0x0AB):  //Rinehart error

    break;

    case(0x511):  //VCU error
      //return MSG;
    break;
  }
  
}

unsigned char *unsel_translator(unsigned char MSG[8], long unsigned int ID) //convert data to human readable
{
  switch(ID)
  {
    //-------LITTLE ENDIAN-------------
    //1 char = 1 byte = 8 bits
    //0x00 = 0b_ _ _ _ _ _ _ _ _
    //     MSB 7 6 5 4 3 2 1 0 LSB
    //SHIFT           168 0 
    case(0x510):  //Buzzer Control
      frequency = ((MSG[1]<<8) + (MSG[0]<<0));
      buzzer_ctrl( ((MSG[6]<<16) + (MSG[5]<<8) + (MSG[4]<<0)) , (MSG[3]<<8) + (MSG[2]<<0) , MSG[7] );
      MSG[0] = 0;
      return MSG;
    break;
    //------BIG ENDIAN--------------------
    case(0x622): //BMS error

    break;

    case(0x0AB):  //Rinehart error

    break;

    case(0x511):  //VCU error
      return MSG;
    break;
    
    case(0x512):
      return MSG;
    break;

    case(0x513):
      return MSG;
    break;

    case(0x514):
      return MSG;
    break;
  }
}

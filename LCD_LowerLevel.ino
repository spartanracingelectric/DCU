//All the basic LCD functions that need not be looked at consistently go here
//Just to make things cleaner in the main LCD file

//The stuff that is in here is large font printing primitives and large font printing functions

byte LT[8] =
{
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte UB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte RT[8] =
{
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte LL[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111
};
byte LB[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte LR[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100
};
byte UMB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte LMB[8] =
{
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};


void lcdbootup()
{
  //initiallize the 20x4 LCD
  lcd.begin(16, 4);
  //Setup Menus for the workout machine
  lcd.backlight();
  //initialize the custom characters
  lcd.createChar(8, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, UMB);
  lcd.createChar(7, LMB);

  lcd.setCursor(0,0);
  lcd.print("BOOTUP");
}

void customdot(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(254);
  lcd.write(254);
  lcd.write(254);
  lcd.setCursor(hor, ver + 1);
  lcd.write(254);
  lcd.write(4);
  lcd.write(254);
}
void custom0(uint8_t hor, uint8_t ver)
{ // uses segments to build the number 0
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
}

void custom1(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(1);
  lcd.write(2);
  lcd.write(254);
  lcd.setCursor(hor, ver + 1);
  lcd.write(254);
  lcd.write(255);
  lcd.write(254);
}

void custom2(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(7);
}

void custom3(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void custom4(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(3);
  lcd.write(4);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(255);
}

void custom5(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(hor, ver + 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void custom6(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(hor, ver + 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void custom7(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(1);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(254);
  lcd.write(8);
  lcd.write(254);
}

void custom8(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void custom9(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(254);
  lcd.write(254);
  lcd.write(255);
}

void customA(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(255);
}

void customB(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(6);
  lcd.write(5);
  lcd.setCursor(hor, 1);
  lcd.write(255);
  lcd.write(7);
  lcd.write(2);
}

void customC(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(1);
  lcd.write(1);
  lcd.setCursor(hor, ver + 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(4);
}

void customD(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
  lcd.write(4);
  lcd.write(5);
}

void customE(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
  lcd.write(7);
  lcd.write(7);
}

void customF(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
}

void customG(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(1);
  lcd.write(1);
  lcd.setCursor(hor, ver + 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(2);
}

void customH(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(4);
  lcd.write(255);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(255);
}

void customI(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(1);
  lcd.write(255);
  lcd.write(1);
  lcd.setCursor(hor, ver + 1);
  lcd.write(4);
  lcd.write(255);
  lcd.write(4);
}

void customJ(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor + 2, ver);
  lcd.write(255);
  lcd.setCursor(hor, ver + 1);
  lcd.write(4);
  lcd.write(4);
  lcd.write(5);
}

void customK(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(4);
  lcd.write(5);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(2);
}

void customL(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
  lcd.write(4);
  lcd.write(4);
}

void customM(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(3);
  lcd.write(5);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(254);
  lcd.write(255);
}

void customN(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(2);
  lcd.write(254);
  lcd.write(255);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(3);
  lcd.write(5);
}

void customP(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
}

void customQ(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(255);
  lcd.write(4);
}

void customR(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(2);
}

void customS(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(8);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(hor, ver + 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void customT(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(1);
  lcd.write(255);
  lcd.write(1);
  lcd.setCursor(hor, ver + 1);
  lcd.write(254);
  lcd.write(255);
}

void customU(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(254);
  lcd.write(255);
  lcd.setCursor(hor, ver + 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
}

void customV(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(3);
  lcd.write(254);
  lcd.write(254);
  lcd.write(5);
  lcd.setCursor(hor + 1, ver + 1);
  lcd.write(2);
  lcd.write(8);
}

void customW(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.write(254);
  lcd.write(254);
  lcd.write(255);
  lcd.setCursor(hor, ver + 1);
  lcd.write(3);
  lcd.write(8);
  lcd.write(2);
  lcd.write(5);
}

void customX(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
  lcd.setCursor(hor, ver + 1);
  lcd.write(8);
  lcd.write(254);
  lcd.write(2);
}

void customY(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
  lcd.setCursor(hor + 1, ver + 1);
  lcd.write(255);
}

void customZ(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(1);
  lcd.write(6);
  lcd.write(5);
  lcd.setCursor(hor, ver + 1);
  lcd.write(8);
  lcd.write(7);
  lcd.write(4);
}

void customqm(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(1);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(hor, ver + 1);
  lcd.write(254);
  lcd.write(7);
}

void customsm(uint8_t hor, uint8_t ver)
{
  lcd.setCursor(hor, ver);
  lcd.write(255);
  lcd.setCursor(hor, ver + 1);
  lcd.write(7);
}

void customClear(uint8_t hor, uint8_t ver, uint8_t lengthx, uint8_t lengthy)  //clears a bunch of cells specified by input parameters
{
  for (uint8_t n = hor; n <= lengthx + hor; n++)
  {
    for (uint8_t m = ver; m <= lengthy + ver; m++)
    {
      lcd.setCursor(n, m);
      lcd.write(254); //clear the segment on the screen
    }
  }
}

void customPrint(String myStr, uint8_t hor, uint8_t ver)  //print strings using the large font
{
  ver--;      //offset adjustment so that 0,0 is first "block" on LCD
  
  for (int n = 0; n < myStr.length(); n++)
  {
    switch (myStr[n])
    {
      case 46:  //.
        hor--;  //decrement by 1 since dot needs not have that much space
        customdot(hor + n * 4, ver);
        hor--;  //decrement by 1 since dot needs not have that much space
        break;
      case 48:  //0
        custom0(hor + n * 4, ver);
        break;
      case 49:  //1
        custom1(hor + n * 4, ver);
        //hor--;  //decrement by 1 since 1 needs not use the last collum
        break;
      case 50:  //2
        custom2(hor + n * 4, ver);
        break;
      case 51:  //3
        custom3(hor + n * 4, ver);
        break;
      case 52:  //4
        custom4(hor + n * 4, ver);
        break;
      case 53:  //5
        custom5(hor + n * 4, ver);
        break;
      case 54:  //6
        custom6(hor + n * 4, ver);
        break;
      case 55:  //7
        custom7(hor + n * 4, ver);
        break;
      case 56:  //8
        custom8(hor + n * 4, ver);
        break;
      case 57:  //9
        custom9(hor + n * 4, ver);
        break;
      case 65:  //A
        customA(hor + n * 4, ver);
        break;
      case 66:  //B
        customB(hor + n * 4, ver);
        break;
      case 67:  //C
        customC(hor + n * 4, ver);
        break;
      case 68:  //D
        customD(hor + n * 4, ver);
        break;
      case 69:  //E
        customE(hor + n * 4, ver);
        break;
      case 70:  //F
        customF(hor + n * 4, ver);
        break;
      case 71:  //G
        customG(hor + n * 4, ver);
        break;
      case 72:  //H
        customH(hor + n * 4, ver);
        break;
      case 73:  //I
        customI(hor + n * 4, ver);
        break;
      case 74:  //J
        customJ(hor + n * 4, ver);
        break;
      case 75:  //K
        customK(hor + n * 4, ver);
        break;
      case 76:  //L
        customL(hor + n * 4, ver);
        break;
      case 77:  //M
        customM(hor + n * 4, ver);
        hor++;  //increment by 1 collum since M takes 4 rows not just 3
        break;
      case 78:  //N
        customN(hor + n * 4, ver);
        break;
      case 79:  //O
        custom0(hor + n * 4, ver);
        break;
      case 80:  //P
        customP(hor + n * 4, ver);
        break;
      case 81:  //Q
        customQ(hor + n * 4, ver);
        break;
      case 82:  //R
        customR(hor + n * 4, ver);
        break;
      case 83:  //S
        customS(hor + n * 4, ver);
        break;
      case 84:  //T
        customT(hor + n * 4, ver);
        break;
      case 85:  //U
        customU(hor + n * 4, ver);
        break;
      case 86:  //V
        customV(hor + n * 4, ver);
        break;
      case 87:  //W
        customW(hor + n * 4, ver);
        hor++;  //increment by 1 row since w takes 4 rows not just 3
        break;
      case 88:  //X
        customX(hor + n * 4, ver);
        break;
      case 89:  //Y
        customY(hor + n * 4, ver);
        break;
      case 90:  //Z
        customZ(hor + n * 4, ver);
        break;
    }
  }
}

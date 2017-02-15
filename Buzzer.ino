void buzzerUpdate(unsigned int freq)
{
  buzzer.update();
  if (buzzer.state() == 1 && buzzerlock == 0)
    {
      tone(buzzpin, freq);
      buzzerlock = 1;
    }
  if (buzzer.state() == 0 && buzzerlock == 1)
  {
    noTone(buzzpin);
    buzzerlock = 0;
  }
}

void buzzer_ctrl(unsigned int period, unsigned int duty, uint8_t brst)
{
  if (duty == 0)
  {
    buzzer.off();
  }
  else
  {
    if (brst == 0) // if not off AND infinite on
    {
      buzzer.on(period, duty/65535.0); //normalize it to a scale of 0 to 1.0
     }
    if (brst != 0)
    {
      buzzer.burst(period, duty/65535.0, brst);
    }
  }
}


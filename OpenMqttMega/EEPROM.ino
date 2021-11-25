#ifdef EPROM
void refreshStates()
{
  if (millis() - previousMillisEEPROM >= 60000)
  {
    previousMillisEEPROM = millis();
    for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
      EEPROM.update(i + OutputStatesStartingAdressEEPROM, OUTPUTSTATES[i]);
      EEPROM.update(i + PwmOutputValuePwmEEPROM, PWMOUTPUTVALUE[i]);
    }
    for (int i = 0; i < INPUTSINSYSTEM; i++) {
      EEPROM.update(i + InputValueLastStartingAdressEEPROM, INPUTVALUELAST[i]);
      EEPROM.update(i + InputStatesStartingAdressEEPROM, INPUTSTATES[i]);
      EEPROM.update(i + InputSwitchStatesStartingAdressEEPROM, INPUTSWITCHSTATES[i]);
      EEPROM.update(i + InputSwitchValueLastStartingAdressEEPROM, INPUTSWITCHVALUELAST[i]);
      EEPROM.update(i + InputStatesLastStartingAdressEEPROM, INPUTSTATESLAST[i]);
    }
#ifdef HVAC
    for (int i = 0; i < HVACS; i++) {
      EEPROM.update(i + HvacModeEEPROM, HvacMode[i]);
      EEPROM.update(i + HvacHvacTempEEPROM, HvacTemp[i]);
    }
#endif

#ifdef POWERMETER
    for (int i = 0; i < POWERMETERS; i++) EEPROMWritelong(PowerDataEEPROM + i, PowerState[i]);
#endif

#ifdef MQTTSERIALDISABLECOMMAND
    EEPROM.update(MQTTSERIALDISABLESTAEEEPROM, MQTTSERIALDISABLESTATE);
#endif
  }
}

void getStates()
{
  for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
    OUTPUTSTATES[i] = EEPROM.read(i + OutputStatesStartingAdressEEPROM);
    PWMOUTPUTVALUE[i] = EEPROM.read(i + PwmOutputValuePwmEEPROM);
  }
  for (int i = 0; i < INPUTSINSYSTEM; i++) {
    INPUTVALUELAST[i]       = EEPROM.read(i + InputValueLastStartingAdressEEPROM);
    INPUTSTATES[i]          = EEPROM.read(i + InputStatesStartingAdressEEPROM);
    INPUTSWITCHSTATES[i]    = EEPROM.read(i + InputSwitchStatesStartingAdressEEPROM);
    INPUTSWITCHVALUELAST[i] = EEPROM.read(i + InputSwitchValueLastStartingAdressEEPROM);
    INPUTSTATESLAST[i]      = EEPROM.read(i + InputStatesLastStartingAdressEEPROM);
  }
#ifdef HVAC
  for (int i = 0; i < HVACS; i++) {
    HvacMode[i] = EEPROM.read(i + HvacModeEEPROM);
    HvacTemp[i] = EEPROM.read(i + HvacHvacTempEEPROM);
  }
#endif

#ifdef POWERMETER
  for (int i = 0; i < POWERMETERS; i++)PowerState[i] = EEPROMReadlong(PowerDataEEPROM + i);
#endif

#ifdef MQTTSERIALDISABLECOMMAND
  MQTTSERIALDISABLESTATE = EEPROM.read(MQTTSERIALDISABLESTAEEEPROM);
#endif
}

void clearEEPROM() {
  for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
    EEPROM.update(i + OutputStatesStartingAdressEEPROM, 0);
    delay(10);
    EEPROM.update(i + PwmOutputValuePwmEEPROM, 0);
    delay(10);
  }
  for (int i = 0; i < INPUTSINSYSTEM; i++) {
    EEPROM.update(i + InputValueLastStartingAdressEEPROM, 0);
    delay(10);
    EEPROM.update(i + InputStatesStartingAdressEEPROM, 0);
    delay(10);
    EEPROM.update(i + InputSwitchStatesStartingAdressEEPROM, 0);
    delay(10);
    EEPROM.update(i + InputSwitchValueLastStartingAdressEEPROM, 0);
    delay(10);
    EEPROM.update(i + InputStatesLastStartingAdressEEPROM, 0);
    delay(10);
  }
#ifdef HVAC
  for (int i = 0; i < HVACS; i++) {
    EEPROM.update(i + HvacModeEEPROM, 0);
    delay(10);
    EEPROM.update(i + HvacHvacTempEEPROM, 0);
    delay(10);
  }
#endif

#ifdef POWERMETER
  for (int i = 0; i < POWERMETERS; i++) {
    EEPROMWritelong(PowerDataEEPROM + i, 0);
    delay(10);
  }
#endif
}

unsigned long EEPROMReadlong(long address) {
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  if (one >= 255 && two >= 255 && three >= 255 && four >= 255) {
    EEPROM.write(address, 0);
    EEPROM.write(address + 1, 0);
    EEPROM.write(address + 2, 0);
    EEPROM.write(address + 3, 0);
  }
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void EEPROMWritelong(int address, unsigned long value) {
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);

  EEPROM.update(address, four);
  EEPROM.update(address + 1, three);
  EEPROM.update(address + 2, two);
  EEPROM.update(address + 3, one);
}
#endif

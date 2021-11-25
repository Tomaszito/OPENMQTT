#ifdef ESP32_SERIAL_COMMUNICATION
void ESP32Setup() {
  Serial2.begin(115200);
}


void ESP32Loop() {
  while (Serial2.available() > 0 && Serial2RequestArriwed == false)  {
    Serial2Buffer[count] = Serial2.read();
    Serial2.flush();
    if (Serial2Buffer[count] == '\n' || count >= 50) break;
    count++;
  }
  //***********************************************************************************************************************************************************************************************************/
  //***********************************************************************************************************************************************************************************************************/
  //************************************************This is the communication between server and ESP32 ******serial *******************************************************************************************/
  //***********************************************************************************************************************************************************************************************************/
  //***********************************************************************************************************************************************************************************************************/
  //**************************************************EEPROM clearing if this is ansvered********************************************************************************************************************/
  if (StrContains(Serial2Buffer, "EPC!")) {
    Serial2.println(F("2EEPROM cleared!!"));//Mesage to lcd screen colum 2
    Serial2.println(F("delay:600"));        //Message to delay this message 600 milisec on screen
    clearEEPROM();                         //This script will clear server eeprom
  }
  //***************************************************Sending the MQTT ON/OFF informations************************************************************************************************************************/
  else if (StrContains(Serial2Buffer, "MQTT?")) {
    if (MQTTDISABLESTATE == 1) Serial.println(F("MQTT-ON"));
    else  Serial.println(F("MQTT-OFF"));
  }
  //***************************************************Sending the output informations***********************************************************************************************************************/
  else if (StrContains(SerialBuffer, "SO?")) {
    for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(OUTPUTSTATECOMMANDSIMPLE[i])));
      Serial.print(Buffer);
      Serial.println(OUTPUTSTATES[i]);
    }
  }
  else if (StrContains(SerialBuffer, "SP?")) {
    for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(OUTPUTPWMSTATECOMMANDSIMPLE[i])));
      Serial.print(Buffer);
      if (OutputType == true)Serial.println(PWMOUTPUTVALUE[i]);
      else Serial.println("0");
    }
  }
  //***************************************************Sending the Input informations************************************************************************************************************************/
  else if (StrContains(SerialBuffer, "SI?")) {
    for (int i = 0; i < INPUTSINSYSTEM; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(INPUTSTATECOMMANDSIMPLE[i])));
      Serial.print(Buffer);
      if (InputAsSwitch[i] == true)Serial.println(INPUTSWITCHSTATES[i]);
      else Serial.println(INPUTVALUE[i]);
    }
  }
  //***************************************************Sending the HVAC Mode informations************************************************************************************************************************/
  else if (StrContains(SerialBuffer, "HM?")) {
    for (int i = 0; i < HVACS; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(HVACMODECOMMANDSIMPLE[i])));
      Serial.print(Buffer);
      Serial.println(HvacMode[i]);
    }
  }
  //***************************************************Sending the HVAC Temperature informations************************************************************************************************************************/
  else if (StrContains(SerialBuffer, "HT?")) {
    for (int i = 0; i < HVACS; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(HVACTEMPCOMMANDSIMPLE[i])));
      Serial.print(Buffer);
      Serial.println(HvacTemp[i]);
    }
  }
  //***************************************************Sending the Temperature informations***********************************************************************************************************************/
  else if (StrContains(SerialBuffer, "ST?")) {
    for (int i = 0; i < usedTEMPMETERS; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(TEMPCOMMANDSIMPLE[i])));
      Serial.print(Buffer);
      Serial.println(tempState[i]);
    }
  }
  //***************************************************Sending the Humitity informations***********************************************************************************************************************/
  else if (StrContains(SerialBuffer, "SH?")) {
    for (int i = 0; i < usedTEMPMETERS; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(HUMIDITYCOMMANDSIMPLE[i])));
      Serial.print(Buffer);
      Serial.println(hudimitystate[i]);
    }
  }
  //***************************************************Recieving the output informations***********************************************************************************************************************/
  else if (StrContains(SerialBuffer, "SO")) {
    for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(OUTPUTSTATECOMMANDSIMPLE[i])));
      OUTPUTSTATES[i] = GetData(SerialBuffer, Buffer, OUTPUTSTATES[i]);
    }
  }
  else if (StrContains(SerialBuffer, "SP")) {
    for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(OUTPUTPWMSTATECOMMANDSIMPLE[i])));
      PWMOUTPUTVALUE[i] = GetData(SerialBuffer, Buffer, PWMOUTPUTVALUE[i]);
    }
  }
  //***************************************************Reading the HVAC Mode informations************************************************************************************************************************/
  else if (StrContains(SerialBuffer, "HM")) {
    for (int i = 0; i < HVACS; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(HVACMODECOMMANDSIMPLE[i])));
      HvacMode[i] = GetData(SerialBuffer, Buffer, HvacMode[i]);
    }
  }
  //***************************************************Reading the HVAC Temperature informations************************************************************************************************************************/
  else if (StrContains(SerialBuffer, "HT")) {
    for (int i = 0; i < HVACS; i++) {
      strcpy_P(Buffer, (char *)pgm_read_word(&(HVACTEMPCOMMANDSIMPLE[i])));
      HvacTemp[i] = GetData(SerialBuffer, Buffer, HvacTemp[i]);
    }
  }
  //***************************************************Reading the MQTT ON/OFF informations************************************************************************************************************************/
  else if (StrContains(SerialBuffer, "MQTTON")) MQTTSERIALDISABLESTATE = 1;
  else if (StrContains(SerialBuffer, "MQTTOFF")) MQTTSERIALDISABLESTATE = 0;
  for (int i = 0; i <= count; i++)SerialBuffer[i] = 32;
  SerialRequestArriwed = false;
  count = 0;
}









}




#endif

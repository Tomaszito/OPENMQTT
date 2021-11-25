#ifdef CAN
void CANinitalization()
{
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS);
  mcp2515.setNormalMode();
}

void CANroutine() {
  //********************************************************CAN messages recive and write to the buffer*********************************************************/
  int RawData = 0;
  int DigitalTemperature = 0;
  unsigned long currentmilliscan = millis();
  char writeOut[8];
  CanTimeOut = currentmilliscan;//Here i reset the timeout variables
  while (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)//Here we recieving data continously until our buffer fully fills up or we run out of time that was 300milisec
  {
    currentmilliscan = millis();//Actual time for the time out segment
    for (int i = 0; i < MessageLenght; i++) recivedRawData[RawData][i] = canMsg.data[i];
    RawData++;
    if (currentmilliscan - CanTimeOut <= 200) {
      DataArriwed = true;
      break;
    }
    else if (RawData >= CanDataBuffer) {
      DataArriwed = true;
      break;
    }
#ifdef CANDEBUG
    for (int a = 0; a < RawData; a++)
    {
      for (int i = 0; i < 8; i++) {
        writeOut[i] = recivedRawData[a][i];
        Serial.print(writeOut[i]);
      }
      Serial.println();
    }
#endif

  }
  //***************************************************Here we process raw data and write in to the variables***************************************************/
  if (DataArriwed == true) {
    for (int i = 0; i < RawData; i++) {
      for (int a = 0; a < MessageLenght; a++)CanData[a] = recivedRawData[a][i];
      ////////////////////////////////////////////////////////////////Expansion modules data//////////////////////////////////////////////////////////////////////
      if (StrContains(CanData, "E")) {
        if (CanOutputChanged == false) {
          if (StrContains(CanData, (char*)CanOutPrefix)) {
            for (int i = 0; i < CanOutputs; i++) {
              strcpy_P(recived, (char *)pgm_read_word(&(CanOutCommand[i])));
              CanStatesOut[i] = GetData(CanData, recived, CanStatesOut[i]);
            }
            continue;
          }
        }
        if (CanInputChanged == false) {
          if (StrContains(CanData, (char*)CanInPrefix)) {
            for (int i = 0; i < CanInputs; i++) {
              strcpy_P(recived, (char *)pgm_read_word(&(CanInCommand[i])));
              CanStatesIn[i] = GetData(CanData, recived, CanStatesIn[i]);
            }
            continue;
          }
        }
        if (CanHvacChanged == false) {
          if (StrContains(CanData, (char*)CanHvacPrefix)) {
            for (int i = 0; i < CanHvacs; i++) {
              strcpy_P(recived, (char *)pgm_read_word(&(CanHvacTemp[i])));
              CanHvacTempState[i] = GetData(CanData, recived, CanHvacTempState[i]);
            }
            for (int i = 0; i < CanHvacs; i++) {
              strcpy_P(recived, (char *)pgm_read_word(&(CanHvacMode[i])));
              CanHvacModeState[i] = GetData(CanData, recived, CanHvacModeState[i]);
            }
          }
          continue;
        }
        if (StrContains(CanData, (char*)CanTempPrefix)) {
          for (int i = 0; i < CanTempSensors; i++) {
            strcpy_P(recived, (char *)pgm_read_word(&(CanCommandTemp[i])));
            CanStatesTemp[i] = GetData(CanData, recived, CanStatesTemp[i]);
          }
          continue;
        }
        if (StrContains(CanData, (char*)CanHumidityPrefix)) {
          for (int i = 0; i < CanHumiditySensors; i++) {
            strcpy_P(recived, (char *)pgm_read_word(&(CanCommandHumidity[i])));
            CanStatesHumidity[i] = GetData(CanData, recived, CanStatesHumidity[i]);
          }
          continue;
        }
      }
      ////////////////////////////////////////////////////////////////Server (Main control unit) Shared Can Data//////////////////////////////////////////////////////////////////////
      else if (StrContains(CanData, "S"))//Server (Main control unit) dedicated data will start will S so if the data dont start with s i dont need to run the following code in that case i can save cpu time
      {
        if (StrContains(CanData, "SO?")) {
          ServerOutputChanged = true;//Server information requested for the expander or display, SO? = ServerOutput? and we will send it
          continue;
        }
        if (StrContains(CanData, "SI?")) {
          ServerInputChanged = true; //Server information requested for the expander or display -||-
          continue;
        }
        if (StrContains(CanData, "SHV?")) {
          ServerHvacChanged = true;  //Server information requested for the expander or display -||-
          continue;
        }
        if (StrContains(CanData, "ST?")) {
          ServerTemperatureAsked = true;  //Server information requested for the expander or display -||-
          continue;
        }
        if (StrContains(CanData, "SH?")) {
          ServerHumidityAsked = true;  //Server information requested for the expander or display -||-
          continue;
        }
        if (StrContains(CanData, "SO")) //Server (Main control unit) Output state change the code supports even the switch bonded outputs and also will change the button state
        {
          for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
            strcpy_P(recived, (char *)pgm_read_word(&(CanServerOut[i])));
            OUTPUTSTATES[i] = GetData(CanData, recived, OUTPUTSTATES[i]);
            if (AtachSwitch[i] == true)INPUTSTATES[OutSwitch[i]] = GetData(CanData, recived, INPUTSTATES[OutSwitch[i]]); // This is needed because if you chose dedicated switch to your output you need to bond input states to your Output states!!!!
          }
          continue;
        }
        if (StrContains(CanData, "SI")) // Server (Main control unit) Input Switch state change this is the intput switch that is mostly used on logic purposes
        {
          for (int i = 0; i < INPUTSINSYSTEM; i++) {
            strcpy_P(recived, (char *)pgm_read_word(&(CanServerIn[i])));
            INPUTSWITCHSTATES[i] = GetData(CanData, recived, INPUTSWITCHSTATES[i]);
          }
          continue;
        }
        if (StrContains(CanData, "SHT")) // Server (Main control unit) HVAC temperature
        {
          for (int i = 0; i < HVACS; i++) {
            strcpy_P(recived, (char *)pgm_read_word(&(CanServerHvacTemp[i])));
            HvacTemp[i] = GetData(CanData, recived, HvacTemp[i]);
          }
          continue;
        }
        if (StrContains(CanData, "SHM")) // Server (Main control unit) HVAC mode
        {
          for (int i = 0; i < HVACS; i++) {
            strcpy_P(recived, (char *)pgm_read_word(&(CanServerHvacMode[i])));
            HvacMode[i] = GetData(CanData, recived, HvacMode[i]);
          }
          continue;
        }
      }
    }
    RawData = 0;
    for (int a = 0; a < CanDataBuffer; a++) for (int i = 0; i < MessageLenght; i++) recivedRawData[i][a] = 0;//Clearing the data storage waiable
    DataArriwed = false;
  }
  //*****************************************Checking Requests if request arriwed data will be sended***************************************/
  if (CanOutputChanged == true)DataAsked = true;
  else if (CanInputChanged == true)DataAsked = true;
  else if (CanHvacChanged == true)DataAsked = true;
  else if (ServerOutputChanged == true)DataAsked = true;
  else if (ServerInputChanged == true)DataAsked = true;
  else if (ServerHvacChanged == true)DataAsked = true;
  else if (ServerTemperatureAsked == true)DataAsked = true;
  else if (ServerHumidityAsked == true)DataAsked = true;
  //***************************************************CAN message send from the integers***************************************************/
  if (currentmilliscan - SendDataMillis >= 500 && DataAsked == true) {
    BeQuietSended = 0;
    SendDataMillis = currentmilliscan;
    ////////////////////////////////////////////////////////////////////////Sending  Data To Expander/s To Stop Talking And Start Only Listening///////////////////////////////////////////////////////////////////
    while (BeQuietSended < 10) {
      SendString("SHUTUP", 0, 8);
      BeQuietSended++;
      if (BeQuietSended >= 10)break;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////Sending Data/////////////////////////////////////////////////////////////////////////////////////////////////
    while (BeQuietSended >= 10) { //After every body stops sending data we send our data
      ////////////////////////////////////////////////////////////////////////////////////////Sending Output Expander Data////////////////////////////////////////////////////////////////////////////////////////
      if (CanOutputChanged == true) {
        for (int i = 0; i < CanOutputs; i++) {
          strcpy_P(recived, (char *)pgm_read_word(&(CanOutCommand[i])));
          SendDatas(recived, CanStatesOut[i], 0, 8);
        }
        CanOutputChanged = false;
      }
      ////////////////////////////////////////////////////////////////////////////////////////Sending Input Expander Data////////////////////////////////////////////////////////////////////////////////////////
      if (CanInputChanged == true) {
        for (int i = 0; i < CanInputs; i++) {
          strcpy_P(recived, (char *)pgm_read_word(&(CanInCommand[i])));
          SendDatas(recived, CanStatesIn[i], 0, 8);
        }
        CanInputChanged = false;
      }
      ////////////////////////////////////////////////////////////////////////////////////////Sending Hvac Expander Data////////////////////////////////////////////////////////////////////////////////////////
      if (CanHvacChanged == true) {
        for (int i = 0; i < CanHvacs; i++) {
          strcpy_P(recived, (char *)pgm_read_word(&(CanHvacTemp[i])));
          SendDatas(recived, CanHvacTempState[i], 0, 8);
          strcpy_P(recived, (char *)pgm_read_word(&(CanHvacMode[i])));
          SendDatas(recived, CanHvacModeState[i], 0, 8);
        }
        CanHvacChanged = false;
      }
      //**************************************************************************************Server Data Sending**********************************************************************************************/
      ////////////////////////////////////////////////////////////////////////////////////////Sending Output Server Data////////////////////////////////////////////////////////////////////////////////////////
      if (ServerOutputChanged == true) {
        for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
          strcpy_P(recived, (char *)pgm_read_word(&(CanServerOut[i])));
          SendDatas(recived, OUTPUTSTATES[i], 0, 8);
        }
        ServerOutputChanged = false;
      }
      ////////////////////////////////////////////////////////////////////////////////////////Sending Input Server Data////////////////////////////////////////////////////////////////////////////////////////
      if (ServerInputChanged == true) {
        for (int i = 0; i < INPUTSINSYSTEM; i++) {
          strcpy_P(recived, (char *)pgm_read_word(&(CanServerIn[i])));
          SendDatas(recived, INPUTSWITCHSTATES[i], 0, 8);
        }
        ServerInputChanged = false;
      }
      ////////////////////////////////////////////////////////////////////////////////////////Sending Hvac Server Data////////////////////////////////////////////////////////////////////////////////////////
      if (ServerHvacChanged == true) {
        for (int i = 0; i < HVACS; i++) {
          strcpy_P(recived, (char *)pgm_read_word(&(CanServerHvacTemp[i])));
          SendDatas(recived, HvacTemp[i], 0, 8);
          strcpy_P(recived, (char *)pgm_read_word(&(CanServerHvacMode[i])));
          SendDatas(recived, HvacMode[i], 0, 8);
        }
        ServerHvacChanged = false;
      }
      ////////////////////////////////////////////////////////////////////////////////////////Sending Server Temp Sensor Data////////////////////////////////////////////////////////////////////////////////////////
      if (ServerTemperatureAsked == true) {
        for (int i = 0; i < usedTEMPMETERS; i++) {
          strcpy_P(recived, (char *)pgm_read_word(&(CanServerTemperature[i])));
          DigitalTemperature = int(tempState[i]);
          SendDatas(recived, DigitalTemperature, 0, 8);
        }
        ServerTemperatureAsked = false;
      }
      ////////////////////////////////////////////////////////////////////////////////////////Sending Server Humidity Sensor Data////////////////////////////////////////////////////////////////////////////////////////
      if (ServerHumidityAsked == true) {
        for (int i = 0; i < usedTEMPMETERS; i++) {
          strcpy_P(recived, (char *)pgm_read_word(&(CanServerHumidity[i])));
          SendDatas(recived, hudimitystate[i], 0, 8);
        }
        ServerHumidityAsked = false;
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      DataAsked = false;
      break;
    }
  }
}
void SendString(char* str, int id, int dlc)
{
  int strlenght = 0;
  strlenght = strlen(str);                                    //Checking how many caracters int this string
  if (strlenght > 8)strlenght = 8;                            //Dont allowing longer string (max 8 character) only the first 8 character sended
  canMsg.can_id  = id;                                        //Choosing id
  canMsg.can_dlc = dlc;                                       //Choosing dlc
  for (int i = 0; i < strlenght; i++)canMsg.data[i] = str[i]; //Writeing the string characters characters to the variable
  for (int i = strlenght; i < 8; i++)canMsg.data[i] = 32;     //Fill the remaning space with space
  delay(5);                                                   //Delay 5 sec betveen each data send to allow devices to recive
  mcp2515.sendMessage(&canMsg);                               //Sending the message
}
void SendDatas(char* prefix, int value, int id, int dlc) {
  int strlenght;
  int numlen;
  char numbers[3];
  if (value > 999)value = 999; //Converting larger numbers than 999
  strlenght = strlen(prefix);//Checking how many caracters the prefix have
  canMsg.can_id  = id;//Choosing id
  canMsg.can_dlc = dlc;//Choosing dlc
  for (int i = 0; i < strlenght; i++)canMsg.data[i] = prefix[i]; //Writeing the prefix characters to the wariable
  itoa(value, numbers, 3); //Convert int to char to prepare data to send as a char
  numlen = strlen(numbers);  //Checking the char how many character it has
  for (int i = strlenght; i < (numlen + strlenght); i++)canMsg.data[i] = numbers[i];//Write the nmbers after the prefix in char
  for (int i = (numlen + strlenght); i < 8; i++)canMsg.data[i] = 32;//Fill the remaning space with space
  delay(5);
  mcp2515.sendMessage(&canMsg);
}
#endif

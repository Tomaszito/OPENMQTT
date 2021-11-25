
void MQTTinitalization() {
  Ethernet.init(W5500SS);
  Ethernet.begin(mac, ip);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef MQTTDISABLESWITCH && MQTTSERIALDISABLECOMMAND
  pinMode(MQTTDISABLESWITCH, INPUT);
  if (digitalRead(MQTTDISABLESWITCH) == 0 || MQTTSERIALDISABLESTATE == 0) {
    MQTTOFF = true;
    MQTTOFFONSTART = true;
    MQTTOFFSERIAL = true;
    MQTTOFFSERIALSTART = true;
  }
  else {
    client.begin(mqttServer, net);
    client.onMessage(messageReceived);
    connect();
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif defined(MQTTSERIALDISABLECOMMAND)
  if (MQTTSERIALDISABLESTATE == 0) {
    MQTTOFFSERIAL = true;
    MQTTOFFSERIALSTART = true;
  }
  else {
    client.begin(mqttServer, net);
    client.onMessage(messageReceived);
    connect();
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif defined(MQTTDISABLESWITCH)
  pinMode(MQTTDISABLESWITCH, INPUT);
  if (digitalRead(MQTTDISABLESWITCH) == 0) {
    MQTTOFF = true;
    MQTTOFFONSTART = true;
  }
  else {
    client.begin(mqttServer, net);
    client.onMessage(messageReceived);
    connect();
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
#else
  client.begin(mqttServer, net);
  client.onMessage(messageReceived);
  connect();
#endif
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void MQTTroutine() {
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef MQTTDISABLESWITCH && MQTTSERIALDISABLECOMMAND
  if (digitalRead(MQTTDISABLESWITCH) == 0) MQTTOFF = true;
  else {
    if (MQTTOFFONSTART == true || MQTTOFFSERIALSTART == true) {
      client.begin(mqttServer, net);
      client.onMessage(messageReceived);
      connect();
      MQTTOFFONSTART = false;
      MQTTOFFSERIALSTART = false;
    }
    MQTTOFF = false;
  }
  if (MQTTOFF == false && MQTTOFFSERIAL == false) {
    if (millis() - lastMillis > 20000)
    {
      lastMillis = millis();
      MqttConnectionTimeOut = false;
      ConnectionErrors = 0;
    }
    if (MqttConnectionTimeOut == false) {
      client.loop();
      if (millis() - sendmillis > 200) {
        sendmillis = millis();
        if (!client.connected())connect();
        sendMessage();
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif defined(MQTTSERIALDISABLECOMMAND)
  if (MQTTOFFSERIAL == true) MQTTOFF = true;
  else {
    if (MQTTOFFONSTART == true) {
      client.begin(mqttServer, net);
      client.onMessage(messageReceived);
      connect();
      MQTTOFFSERIALSTART = false;
    }
    MQTTOFF = false;
    MQTTOFFSERIAL = false;
  }
  if (MQTTOFF == false) {
    if (millis() - lastMillis > 20000)
    {
      lastMillis = millis();
      MqttConnectionTimeOut = false;
      ConnectionErrors = 0;
    }
    if (MqttConnectionTimeOut == false) {
      client.loop();
      if (millis() - sendmillis > 200) {
        sendmillis = millis();
        if (!client.connected())connect();
        sendMessage();
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif defined(MQTTDISABLESWITCH)
  if (digitalRead(MQTTDISABLESWITCH) == 0) MQTTOFF = true;
  else {
    if (MQTTOFFONSTART == true) {
      client.begin(mqttServer, net);
      client.onMessage(messageReceived);
      connect();
      MQTTOFFONSTART = false;
    }
    MQTTOFF = false;
  }
  if (MQTTOFF == false) {
    if (millis() - lastMillis > 20000)
    {
      lastMillis = millis();
      MqttConnectionTimeOut = false;
      ConnectionErrors = 0;
    }
    if (MqttConnectionTimeOut == false) {
      client.loop();
      if (millis() - sendmillis > 200) {
        sendmillis = millis();
        if (!client.connected())connect();
        sendMessage();
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
#else
  if (millis() - lastMillis > 20000)
  {
    lastMillis = millis();
    MqttConnectionTimeOut = false;
    ConnectionErrors = 0;
  }
  if (MqttConnectionTimeOut == false) {
    client.loop();
    if (millis() - sendmillis > 200) {
      sendmillis = millis();
      if (!client.connected())connect();
      sendMessage();
    }
  }
#endif
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void connect() {
#ifdef MQTTDEBUG
  Serial.print("connecting...");
#endif
  while (!client.connect(deviceName, mqttUsername, mqttPassword)) {
#ifdef MQTTDEBUG
    Serial.print(".");
#endif
    ConnectionErrors++;
    if (ConnectionErrors > 5)
    {
      MqttConnectionTimeOut = true;
#ifdef MQTTDEBUG
      Serial.println("");
#endif
      break;
    }
  }
  for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(subsrcibeOut[i])));
    client.subscribe(String(buffer));
    strcpy_P(buffer, (char *)pgm_read_word(&(subsrcibeOut[i])));
    client.subscribe(String(buffer) + String("/brightness"));
  }
  for (int i = 0; i < INPUTSINSYSTEM; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(subsrcibeIn[i])));
    client.subscribe(String(buffer));
  }
#ifdef HVAC
  for (int i = 0; i < HVACS; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicHvacTemp[i])));
    client.subscribe(String(buffer));
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicHvacMode[i])));
    client.subscribe(String(buffer));
  }
#endif
#ifdef CAN
  for (int i = 0; i < CanOutputs; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicCanOut[i])));
    client.subscribe(String(buffer));
  }
  for (int i = 0; i < CanInputs; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicCanIn[i])));
    client.subscribe(String(buffer));
  }
  for (int i = 0; i < CanHvacs; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicCanHvacTemp[i])));
    client.subscribe(String(buffer));
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicCanHvacMode[i])));
    client.subscribe(String(buffer));
  }
#endif
}

void messageReceived(String &topic, String &payload) {
  int payloadValue;
  char topicChar[30];
  topic.toCharArray(topicChar, 30);
  payloadValue = payload.toInt();
#ifdef MQTTDEBUG
  Serial.println("incoming: " + topic + " - " + payload);
#endif
  for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(subsrcibeOut[i])));
    if (topic == String(buffer) && OutAsTermostate[i] == false) {
      OUTPUTSTATES[i] = payloadValue;
      if (AtachSwitch[i] == true)INPUTSTATES[OutSwitch[i] - 1] = OUTPUTSTATES[i];
#ifdef CAN
      ServerOutputChanged = true;//Sending the changed outputs to can devices
#endif
    }
    if (OutputType[i] == true) if (topic == (String(buffer) + String("/brightness"))) PWMOUTPUTVALUE[i] = payloadValue;
  }

  for (int i = 0; i < INPUTSINSYSTEM; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(subsrcibeIn[i])));
    if (topic == String(buffer)) {
      if ( AtachSwitch[i] == false && InputAsSwitch[i] == true)INPUTSWITCHSTATES[i] = payloadValue;
#ifdef CAN
      ServerInputChanged = true;
#endif
    }
  }

#ifdef HVAC
  for (int i = 0; i < HVACS; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicHvacTemp[i])));
    if (topic == String(buffer)) {
      HvacTemp[i] = payloadValue;
#ifdef CAN
      ServerHvacChanged = true;
#endif
    }
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicHvacMode[i])));
    if (topic == String(buffer)) {
      if (payload == "heat")HvacMode[i] = 1;
      else if (payload == "off")HvacMode[i] = 0;
#ifdef CAN
      ServerHvacChanged = true;
#endif
    }
  }
#endif

#ifdef CAN
  for (int i = 0; i < CanOutputs; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicCanOut[i])));
    if (topic == String(buffer)) {
      CanStatesOut[i] = payloadValue;
      CanOutputChanged = true;
    }
  }
  for (int i = 0; i < CanInputs; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicCanIn[i])));
    if (topic == String(buffer)) {
      CanStatesIn[i] = payloadValue;
      CanInputChanged = true;
    }
  }
  for (int i = 0; i < CanHvacs; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicCanHvacTemp[i])));
    if (topic == String(buffer))
    {
      CanHvacTempState[i] = payloadValue;
      CanHvacChanged = true;
    }
    strcpy_P(buffer, (char *)pgm_read_word(&(SubTopicCanHvacMode[i])));
    if (topic == String(buffer)) {
      if (payload == "heat")CanHvacModeState[i] = 1;
      else if (payload == "off")CanHvacModeState[i] = 0;
      CanHvacChanged = true;
    }
  }
#endif
}
//*********************************************************************************Send Message*******************************************************************************/
void sendMessage()
{
  for (int i = 0; i < OUTPUTSINSYSTEM; i++) {
    if (OutAsTermostate[i] == false) {
      strcpy_P(buffer, (char *)pgm_read_word(&(publisOut[i])));
      client.publish(String(buffer), String(OUTPUTSTATES[i]));
      if (OutputType[i] == true) client.publish((String(buffer) + String("/brightness")), /*"{ \"dimmer\": \"" +*/ String(PWMOUTPUTVALUE[i])/* + "\"}"*/) ;
    }
  }
  for (int i = 0; i < INPUTSINSYSTEM ; i++) {
    if (InputAsSwitch[i] == true) {
      if (InputType[i] == true) {
        strcpy_P(buffer, (char *)pgm_read_word(&(publisIn[i])));
        client.publish(String(buffer), String(analogRead(INPUTS[i])));//This gives back a raw analog data in 10bit (0-1023) with 5V reference
      }

      else {
        strcpy_P(buffer, (char *)pgm_read_word(&(publisIn[i])));
        client.publish(String(buffer), String(INPUTSWITCHSTATES[i])); //This will gives back the input state that has been setted up you can modify this states on switch and push buttan also thanks to the input integration function that reverses the input eve on switch...
      }
    }
  }

#ifdef TEMPSENSOR
  for (int i = 0; i < usedTEMPMETERS; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(PubTopicTemp[i])));
    strcpy_P(buffer1, (char *)pgm_read_word(&(TempSensorName[i])));
    strcpy_P(buffer2, (char *)pgm_read_word(&(TempSensorId[i])));
    client.publish(String(buffer), "{ \"name\": \"" + String(buffer1) + "\" ,\"id\": \" " + String(buffer2) + " \" ,\"temperature\":\" " + String(tempState[i], 2) + "\" ,\"humidity\": \" " + String(hudimitystate[i]) + "\"}");
  }
#endif

#ifdef HVAC
  for (int i = 0; i < HVACS; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(PubTopicHvacTemp[i])));
    client.publish(String(buffer), String(HvacTemp[i]));
    strcpy_P(buffer, (char *)pgm_read_word(&(PubTopicHvacMode[i])));
    if (HvacMode[i] == 1) client.publish(String(buffer), String("heat"));
    else if (HvacMode[i] == 0) client.publish(String(buffer), String("off"));
  }
#endif

#ifdef POWERMETER
  for (int i = 0; i < POWERMETERS; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(PubTopicPowerMeter[i])));
    strcpy_P(buffer1, (char *)pgm_read_word(&(PowerMeterName[i])));
    strcpy_P(buffer2, (char *)pgm_read_word(&(PowerMeterId[i])));
    strcpy_P(buffer3, (char *)pgm_read_word(&(PowerMeterUnitOfMesurement[i])));
    client.publish(String(buffer), "{ \"name\": \"" + String(buffer1) + "\" ,\"id\": \"" + String(buffer2) + "\" ,\"energy\":\"" + String(PowerState[i]) + "\" ,\"unit_of_measurement\": \"" + String(buffer3) + "\"}");
  }
#endif

#ifdef CAN
  for (int i = 0; i < CanOutputs; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(PubTopicCanOut[i])));
    client.publish(String(buffer), String(CanStatesOut[i]));
  }
  for (int i = 0; i < CanInputs; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(PubTopicCanIn[i])));
    client.publish(String(buffer), String(CanStatesIn[i]));
  }
#endif
#ifdef CANTEMPSENSOR
  for (int i = 0; i < CanTempSensors; i++) {
    strcpy_P(buffer, (char *)pgm_read_word(&(PubTopicCanTemp[i])));
    strcpy_P(buffer1, (char *)pgm_read_word(&(CanTempSensorName[i])));
    strcpy_P(buffer2, (char *)pgm_read_word(&(CanTempSensorId[i])));
    client.publish(String(buffer),  "{ \"name\": " + String(buffer1) + " ,\"id\": " + String(buffer2) + " ,\"temperature\": " + String(CanStatesTemp[i]) + " ,\"humidity\": " + String(CanStatesHumidity[i]) + "}");
  }
#endif
#ifdef CANHVAC

#endif
}

char StrContains(char *str, char *sfind)
{
  int found = 0;
  int index = 0;
  int len = 0;

  len = strlen(str);

  if (strlen(sfind) > len) {
    return 0;
  }
  while (index < len)
  {
    if (str[index] == sfind[found])
    {
      found++;
      if (strlen(sfind) == found)
      {
        return 1;
      }
    }
    else
    {
      found = 0;
    }
    index++;
  }
  return 0;
}

int GetData(char* str, char* sfind, int lastState)
{
  int match = 0;
  int index = 0;
  int lenght = 0;
  int number[3] = {0, 0, 0};
  int numbers = 0;
  int value = 0;

  lenght = strlen(str);

  if (strlen(sfind) > lenght) return lastState;//If the input string is smaller t

  while (index < lenght)
  { if (str[index] == sfind[match])
    {
      match++;
      if (strlen(sfind) == match)
      {
        number[0] = str[index + 1] - 48;
        number[1] = str[index + 2] - 48;
        number[2] = str[index + 3] - 48;
        if (number[0] > 9 || number[0] < 0) number[0] = 0;
        else numbers++;
        if (number[1] > 9 || number[1] < 0) number[1] = 0;
        else numbers++;
        if (number[2] > 9 || number[2] < 0) number[2] = 0;
        else numbers++;
        if (numbers <= 1)
        {
          value = str[index + 1] - 48;
          if (value > 9 || value < 0) return lastState;
          else return value;
        }
        if (numbers == 2)
        {
          number[1] = str[index + 1] - 48;
          number[0] = str[index + 2] - 48;
          value = (number[1] * 10) + number[0];
          if (value > 99 || value < 0) return lastState;
          else return value;
        }
        if (numbers >= 3) {
          number[2] = str[index + 1] - 48;
          number[1] = str[index + 2] - 48;
          number[0] = str[index + 3] - 48;
          value = number[2] * 100 + number[1] * 10 + number[0];
          if (value > 999 || value < 0) return lastState;
          else return value;
        }
      }
    }
    else match = 0;
    index++;
  }
  return lastState;
}

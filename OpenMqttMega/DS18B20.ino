#ifdef DS18B20
void Ds18b20setResolution() {
  sensors.begin();
  sensors.setResolution(TEMPMETER1, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER2, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER3, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER4, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER5, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER6, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER7, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER8, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER9, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER10, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER11, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER12, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER13, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER14, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER15, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER16, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER17, TEMPERATURE_PRECISION);
  sensors.setResolution(TEMPMETER18, TEMPERATURE_PRECISION);
}

void getDs18b20data() {
  sensors.requestTemperatures();
  if (TempSensorType[0] == true)tempState[0] = sensors.getTempC(TEMPMETER1);
  if (TempSensorType[1] == true)tempState[1] = sensors.getTempC(TEMPMETER2);
  if (TempSensorType[2] == true)tempState[2] = sensors.getTempC(TEMPMETER3);
  if (TempSensorType[3] == true)tempState[3] = sensors.getTempC(TEMPMETER4);
  if (TempSensorType[4] == true)tempState[4] = sensors.getTempC(TEMPMETER5);
  if (TempSensorType[5] == true)tempState[5] = sensors.getTempC(TEMPMETER6);
  if (TempSensorType[6] == true)tempState[6] = sensors.getTempC(TEMPMETER7);
  if (TempSensorType[7] == true)tempState[7] = sensors.getTempC(TEMPMETER8);
  if (TempSensorType[8] == true)tempState[8] = sensors.getTempC(TEMPMETER9);
  if (TempSensorType[9] == true)tempState[9] = sensors.getTempC(TEMPMETER10);
  if (TempSensorType[10] == true)tempState[10] = sensors.getTempC(TEMPMETER11);
  if (TempSensorType[11] == true)tempState[11] = sensors.getTempC(TEMPMETER12);
  if (TempSensorType[12] == true)tempState[12] = sensors.getTempC(TEMPMETER13);
  if (TempSensorType[13] == true)tempState[13] = sensors.getTempC(TEMPMETER14);
  if (TempSensorType[14] == true)tempState[14] = sensors.getTempC(TEMPMETER15);
  if (TempSensorType[15] == true)tempState[15] = sensors.getTempC(TEMPMETER16);
  if (TempSensorType[16] == true)tempState[16] = sensors.getTempC(TEMPMETER17);
  if (TempSensorType[17] == true)tempState[17] = sensors.getTempC(TEMPMETER18); 
}
#endif

#ifdef LM35
void LM35Loop() {
  int temp_adc_val;
  float temp_val;
  for (int i = 0; i < usedTEMPMETERS; i++) {
    if (TempSensorType[i] == false) {
      if (LM35TempSensor[i] == true) {
        temp_val = 0;
        temp_adc_val = analogRead(TempSensorPin[i]);
        temp_val = ((float)temp_adc_val * 4.88);
        temp_val = ((float)temp_val / 10);
        tempState[i] = temp_val;
      }
    }
  }
}
void LM35Setup() {
  for (int i = 0; i < usedTEMPMETERS; i++)if (LM35TempSensor[i] == true)pinMode(TempSensorPin[i], INPUT);
}
#endif

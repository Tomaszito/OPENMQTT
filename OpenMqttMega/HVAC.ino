#ifdef HVAC
void HVACLoop()
{
  int ActivateBoiler = 0;
  if (millis() - ElapsedTime > HeatTimeOut) {
    ElapsedTime = millis();
    for (int i = 0; i < HVACS; i++) {
      for (int i = 0; i < usedHEATERS; i++)
      {
        if (HvacMode[i] == 1)
        {
          if (tempState[HvacTempsensor[i]] <= (HvacTemp[i] - Heatofset)) {
            OUTPUTSTATES[HvacOutput[i]] = 1;
            ActivateBoiler++;
          }
          else if (tempState[HvacTempsensor[i]] >= (HvacTemp[i] + Heatofset))OUTPUTSTATES[HvacOutput[i]] = 0;
          if (ActivateBoiler >= 1) {
            OUTPUTSTATES[DigitalTermostateAndPumpOutput] = 1;
            BoilerAndHeatPumpState = 1;
          }
          else {
            OUTPUTSTATES[DigitalTermostateAndPumpOutput] = 0;
            BoilerAndHeatPumpState = 0;
          }
        }
      }
    }
  }
}
#endif

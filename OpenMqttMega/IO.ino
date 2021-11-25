void setIo() {
  //************************************************* SET INPUTS **************************************************************/
  for (int i = 0; i < INPUTSINSYSTEM; i++)if (INPUTS[i] < LASTIO)pinMode(INPUTS[i], INPUT);
  //************************************************* SET OUTPUTS *************************************************************/
  for (int i = 0; i < OUTPUTSINSYSTEM; i++)if (OUTPUTS[i] < LASTIO)pinMode(OUTPUTS[i], OUTPUT);
}
void refreshIo() {
  //*************************************************** FOR LOOP **************************************************************/
  for (int i = 0; i < INPUTSINSYSTEM; i++) {
    //************************************************** READ INPUTS **********************************************************/
    if (InputType[i] == true && INPUTS[i] < LASTIO) INPUTVALUE[i] = analogRead(INPUTS[i]);
    else if (INPUTS[i] < LASTIO) INPUTVALUE[i] = digitalRead(INPUTS[i]);
    //******************************** PUSH BUTTON AND NORMAL SWITCH CONTROL LOGIC*********************************************/
    if (millis() - DEBOUNCE >= BUTTONDEBOUNCE)
    {
      DEBOUNCE = millis();
      //************************************************* OUTPUT SWITCH LOGIC *************************************************/
      for (int i = 0; i < INPUTSINSYSTEM; i++)
      {
        if (AtachSwitch[i] == true) {
          if (INPUTVALUE[i] != INPUTVALUELAST[i] && SwitchType[i] == true)
          {
            if (OUTPUTSTATES[i] == 1)OUTPUTSTATES[i] = 0;
            else OUTPUTSTATES[i] = 1;
            INPUTVALUELAST[i] = INPUTVALUE[i];
          }
          else if (INPUTVALUE[i] == 1 && State[i] == 0 && SwitchType[i] == false)
          {
            if (OUTPUTSTATES[i] == 1)OUTPUTSTATES[i] = 0;
            else OUTPUTSTATES[i] = 1;
            State[i] = 1;
          }
          else if (INPUTVALUE[i] == 0 && State[i] == 1)State[i] = 0;
        }
        //************************************************* INPUT SWITCH LOGIC *************************************************/
        if (INPUTVALUE[i] != INPUTSWITCHVALUELAST[i] && InputSwitchType[i] == true)
        {
          if (INPUTSWITCHSTATES[i] == 1)INPUTSWITCHSTATES[i] = 0;
          else INPUTSWITCHSTATES[i] = 1;
          INPUTSWITCHVALUELAST[i] = INPUTVALUE[i];
        }
        else if (INPUTVALUE[i] == 1 && StateSwitch[i] == 0 && InputSwitchType[i] == false)
        {
          if (INPUTSWITCHSTATES[i] == 1)INPUTSWITCHSTATES[i] = 0;
          else INPUTSWITCHSTATES[i] = 1;
          StateSwitch[i] = 1;
        }
        else if (INPUTVALUE[i] == 0 && StateSwitch[i] == 1)StateSwitch[i] = 0;
      }
    }
    //************************************************* OUTPUT SWITCH LOGIC *************************************************/
    if (AtachSwitch[i] == true) OUTPUTSTATES[i] = INPUTSTATES[OutSwitch[i] - 1];
    //************************************************* WRITE OUTPUTS *******************************************************/
    if (OutputType[i] == true && OutAsTermostate[i] == false && OUTPUTS[i] < ALLIO){
      if(OUTPUTSTATES[i] >= 1)analogWrite(OUTPUTS[i], PWMOUTPUTVALUE[i]);
      else analogWrite(OUTPUTS[i], 0);
    }
    else if (OUTPUTS[i] < ALLIO) digitalWrite(OUTPUTS[i], OUTPUTSTATES[i]);
    //********************************************* WRITE DATA FOR DEBUG ****************************************************/
#ifdef DEBUGIO
    Serial.print("INPUTSTATES");
    Serial.print(i);
    Serial.print(":");
    Serial.println(INPUTSTATES[i]);
    Serial.print("INPUTVALUE");
    Serial.print(i);
    Serial.print(":");
    Serial.println(INPUTVALUE[i]);
    Serial.print("OUTPUTSATES");
    Serial.print(i);
    Serial.print(":");
    Serial.println(OUTPUTSTATES[i]);
#endif
  }
}

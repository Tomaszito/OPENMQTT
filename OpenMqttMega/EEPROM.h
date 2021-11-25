unsigned long previousMillisEEPROM = 0;

const int OutputStatesStartingAdressEEPROM = 0;
const int InputValueLastStartingAdressEEPROM = OutputStatesStartingAdressEEPROM + OUTPUTSINSYSTEM;
const int InputStatesStartingAdressEEPROM = InputValueLastStartingAdressEEPROM + INPUTSINSYSTEM;
const int InputSwitchStatesStartingAdressEEPROM = InputStatesStartingAdressEEPROM + INPUTSINSYSTEM;
const int InputSwitchValueLastStartingAdressEEPROM = InputSwitchStatesStartingAdressEEPROM + INPUTSINSYSTEM;
const int InputStatesLastStartingAdressEEPROM = InputSwitchValueLastStartingAdressEEPROM + INPUTSINSYSTEM;
const int HvacModeEEPROM = InputStatesLastStartingAdressEEPROM + INPUTSINSYSTEM;
const int HvacHvacTempEEPROM = HvacModeEEPROM + HVACS;
const int PowerDataEEPROM = HvacHvacTempEEPROM + HVACS;// after thet the valuse needs to be ->  xy = PowerDataEEPROM + (POWERMETERS * 4) because the power meter data needs 4 eeprom spaces instead of one
const int PwmOutputValuePwmEEPROM = PowerDataEEPROM + (POWERMETERS * 4);
const int MQTTSERIALDISABLESTAEEEPROM = PwmOutputValuePwmEEPROM + OUTPUTSINSYSTEM; //Will only use 1 epprom place

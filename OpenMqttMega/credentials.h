/**************************************************************************************************************************************************
   Hardware Setup
 **************************************************************************************************************************************************
   In that page you can set the most important settings
 * ************************************************************************************************************************************************
   You need to write yor mqtt broker (or server) adress with login and password
   After that you need to read your tempmeter adresses with a simple arduino based code.
   You can find this code in DS18b20 library
   You can connect 8 temp meter to arduino UNO - NANO - LEONARDO - MICRO, ARDUINO MEGA supports up to 18 Temp meter
   After that you can chose the pub and sub topics sub topics
   You can easily fill the pub and sub topics with your own topics
   Pub adresses only publish numbers so the on state will be 1 and the off state will be 0
   And also the sub adreses only recive numbers on state will be 1 and the off state will be 0
   The temp sensor data also numbers are integers!!!! (Does not support float!!!!!!!)
   You can set the termostats but you can set temperatures only integers
   You can chose any output as a virtual termostate you can controll valves from here the boiler and water circulator from here.
   They will start when any heater valve opens
   The virtual termostate only can control home with +-1c The heater will start if temp
   1C lover then the wanted temperature and the heater will stop when the temp 1C higher tan the wanted temp
   The output states are stored in eeprom and every 10 minutes the actual states will be refreshed (this time is needed for the eeprom to long live)
   You chan chose a On board input to be a switch for your output
   In that case you need to leave blank the input setup that you chose so if you van to operate output1 with input1 you need to leave blank the INPUT1 Setup down below
   You also need to be chosed the switch type in the output setup can be push button(counting when pushed) or normal swith(raw date)
   The input states can be raw(measured realtime) and also can be a push button with on and of state (this is also 0 and 1 data)
   You need to chose how you want to use your input
**************************************************************************************************************************************************/
//*Internet Setup*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {192, 168, 0, 194};  // <- change to match your network
//Temp sensors/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int usedTEMPMETERS = 18;//If you need more you need to change this value you need to add one more line to thermometers and also you need more variable in mqtt. So a bit compilcated
//*Mqtt connection Setup*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char mqttSERVER[] = "192.168.0.195"; // <- change to match your network
const char mqttUSERNAME[] = "mqtt"; // <- change to match your mqtt username
const char mqttPASSWORD[] = "mqtt";  // <- change to match your mqtt password
const int DisableMQTTPin = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Outputs
//  Example: const boolean  AtachSwitch1 = INPUT1; in that
//  case the out 1 will be high if the in 1 high
//  = IN....... you need to write the input that you want as a
//  button in that case you need to leave that input mqtt data
//  without any data because the input state will be same as
//  the output state.
//*********************************************************************************Outputs***********************************************************************/
//*Output 1*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut1[] PROGMEM  = "mega/subout1";  //Here you need to write your subtopic
const char  PubTopicOut1[] PROGMEM  = "mega/pubout1";  //Here you need to write your pubtopic
const boolean OutputType1 = false;                      //True = analog (only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"   False = digital
const boolean OutAsTermostate1 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch1 =  true;                   //If you wanted a switch you need to chose true
const boolean SwitchType1 = true;                      //True = normal switch   false = push button
const int     OutSwitch1 = 1;                          //Here you can chose the input that used as switch
//*Output2*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut2[] PROGMEM  = "mega/subout2";  //Here you need to write your subtopic
const char  PubTopicOut2[] PROGMEM  = "mega/pubout2";  //Here you need to write your pubtopic
const boolean OutputType2 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate2 = false;                 //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch2 = true;                   //If you wanted a switch you need to chose true
const boolean SwitchType2 = false;                     //True = normal switch   false = push button
const int     OutSwitch2 = 2;                          //Here you can chose the input that used as switch
//*Output3*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut3[] PROGMEM  = "mega/subout3";  //Here you need to write your subtopic
const char  PubTopicOut3[] PROGMEM  = "mega/pubout3";  //Here you need to write your pubtopic
const boolean OutputType3 = true;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate3 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch3 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType3 = false;                     //True = normal switch   false = push button
const int     OutSwitch3 = 0;                          //Here you can chose the input that used as switch
//*Output4*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut4 [] PROGMEM  = "mega/subout4"; //Here you need to write your subtopic
const char  PubTopicOut4 [] PROGMEM  = "mega/pubout4"; //Here you need to write your pubtopic
const boolean OutputType4 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate4 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch4 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType4 = false;                     //True = normal switch   false = push button
const int     OutSwitch4 = 0;                          //Here you can chose the input that used as switch
//*Output5*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut5 [] PROGMEM  = "mega/subout5"; //Here you need to write your subtopic
const char  PubTopicOut5 [] PROGMEM  = "mega/pubout5"; //Here you need to write your pubtopic
const boolean OutputType5 = true;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate5 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch5 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType5 = false;                     //True = normal switch   false = push button
const int     OutSwitch5 = 0;                          //Here you can chose the input that used as switch
//*Output6*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut6 [] PROGMEM  = "mega/subout6"; //Here you need to write your subtopic
const char  PubTopicOut6 [] PROGMEM  = "mega/pubout6"; //Here you need to write your pubtopic
const boolean OutputType6 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate6 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch6 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType6 = false;                     //True = normal switch   false = push button
const int     OutSwitch6 = 0;                          //Here you can chose the input that used as switch
//*Output7*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut7 [] PROGMEM  = "mega/subout7"; //Here you need to write your subtopic
const char  PubTopicOut7 [] PROGMEM  = "mega/pubout7"; //Here you need to write your pubtopic
const boolean OutputType7 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate7 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch7 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType7 = false;                     //True = normal switch   false = push button
const int     OutSwitch7 = 0;                          //Here you can chose the input that used as switch
//*Output8*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut8 [] PROGMEM  = "mega/subout8"; //Here you need to write your subtopic
const char  PubTopicOut8 [] PROGMEM  = "mega/pubout8"; //Here you need to write your pubtopic
const boolean OutputType8 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate8 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch8 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType8 = false;                     //True = normal switch   false = push button
const int     OutSwitch8 = 0;                          //Here you can chose the input that used as switch
//*Output9*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut9 [] PROGMEM  = "mega/subout9"; //Here you need to write your subtopic
const char  PubTopicOut9 [] PROGMEM  = "mega/pubout9"; //Here you need to write your pubtopic
const boolean OutputType9 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate9 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch9 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType9 = false;                     //True = normal switch   false = push button
const int     OutSwitch9 = 0;                          //Here you can chose the input that used as switch
//*Output10*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut10 [] PROGMEM  = "mega/subout10";//Here you need to write your subtopic
const char  PubTopicOut10 [] PROGMEM  = "mega/pubout10";//Here you need to write your pubtopic
const boolean OutputType10 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate10 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch10 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType10 = false;                     //True = normal switch   false = push button
const int     OutSwitch10 = 0;                          //Here you can chose the input that used as switch
//*Output 11*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut11 [] PROGMEM  = "mega/subout11";//Here you need to write your subtopic
const char  PubTopicOut11 [] PROGMEM  = "mega/pubout11";//Here you need to write your pubtopic
const boolean OutputType11 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate11 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch11 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType11 = false;                     //True = normal switch   false = push button
const int     OutSwitch11 = 0;                          //Here you can chose the input that used as switch
//*Output12*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut12 [] PROGMEM  = "mega/subout12";//Here you need to write your subtopic
const char  PubTopicOut12 [] PROGMEM  = "mega/pubout12";//Here you need to write your pubtopic
const boolean OutputType12 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate12 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch12 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType12 = false;                     //True = normal switch   false = push button
const int     OutSwitch12 = 0;                          //Here you can chose the input that used as switch
//*Output13*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut13 [] PROGMEM  = "mega/subout13";//Here you need to write your subtopic
const char  PubTopicOut13 [] PROGMEM  = "mega/pubout13";//Here you need to write your pubtopic
const boolean OutputType13 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate13 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch13 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType13 = false;                     //True = normal switch   false = push button
const int     OutSwitch13 = 0;                          //Here you can chose the input that used as switch
//*Output14*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut14 [] PROGMEM  = "mega/subout14";//Here you need to write your subtopic
const char  PubTopicOut14 [] PROGMEM  = "mega/pubout14";//Here you need to write your pubtopic
const boolean OutputType14 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate14 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch14 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType14 = false;                     //True = normal switch   false = push button
const int     OutSwitch14 = 0;                          //Here you can chose the input that used as switch
//*Output15*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut15 [] PROGMEM  = "mega/subout15";//Here you need to write your subtopic
const char  PubTopicOut15 [] PROGMEM  = "mega/pubout15";//Here you need to write your pubtopic
const boolean OutputType15 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate15 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch15 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType15 = false;                     //True = normal switch   false = push button
const int     OutSwitch15 = 0;                          //Here you can chose the input that used as switch
//*Output16*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut16 [] PROGMEM  = "mega/subout16";//Here you need to write your subtopic
const char  PubTopicOut16 [] PROGMEM  = "mega/pubout16";//Here you need to write your pubtopic
const boolean OutputType16 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate16 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch16 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType16 = false;                     //True = normal switch   false = push button
const int     OutSwitch16 = 0;                          //Here you can chose the input that used as switch
//*Output17*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut17 [] PROGMEM  = "mega/subout17";//Here you need to write your subtopic
const char  PubTopicOut17 [] PROGMEM  = "mega/pubout17";//Here you need to write your pubtopic
const boolean OutputType17 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate17 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch17 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType17 = false;                     //True = normal switch   false = push button
const int     OutSwitch17 = 0;                          //Here you can chose the input that used as switch
//*Output18*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut18 [] PROGMEM  = "mega/subout18";//Here you need to write your subtopic
const char  PubTopicOut18 [] PROGMEM  = "mega/pubout18";//Here you need to write your pubtopic
const boolean OutputType18 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate18 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch18 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType18 = false;                     //True = normal switch   false = push button
const int     OutSwitch18 = 0;                          //Here you can chose the input that used as switch
//*Output19*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut19 [] PROGMEM  = "mega/subout19";//Here you need to write your subtopic
const char  PubTopicOut19 [] PROGMEM  = "mega/pubout19";//Here you need to write your pubtopic
const boolean OutputType19 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate19 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch19 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType19 = false;                     //True = normal switch   false = push button
const int     OutSwitch19 = 0;                          //Here you can chose the input that used as switch
//*Output20*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut20 [] PROGMEM  = "mega/subout20";//Here you need to write your subtopic
const char  PubTopicOut20 [] PROGMEM  = "mega/pubout20";//Here you need to write your pubtopic
const boolean OutputType20 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate20 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch20 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType20 = false;                     //True = normal switch   false = push button
const int     OutSwitch20 = 0;                          //Here you can chose the input that used as switch
//*Output 21*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut21 [] PROGMEM  = "mega/subout21";//Here you need to write your subtopic
const char  PubTopicOut21 [] PROGMEM  = "mega/pubout21";//Here you need to write your pubtopic
const boolean OutputType21 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate21 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch21 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType21 = false;                     //True = normal switch   false = push button
const int     OutSwitch21 = 0;                          //Here you can chose the input that used as switch
//*Output22*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut22 [] PROGMEM  = "mega/subout22";//Here you need to write your subtopic
const char  PubTopicOut22 [] PROGMEM  = "mega/pubout22";//Here you need to write your pubtopic
const boolean OutputType22 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate22 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch22 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType22 = false;                     //True = normal switch   false = push button
const int     OutSwitch22 = 0;                          //Here you can chose the input that used as switch
//*Output23*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut23 [] PROGMEM  = "mega/subout23";//Here you need to write your subtopic
const char  PubTopicOut23 [] PROGMEM  = "mega/pubout23";//Here you need to write your pubtopic
const boolean OutputType23 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate23 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch23 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType23 = false;                     //True = normal switch   false = push button
const int     OutSwitch23 = 0;                          //Here you can chose the input that used as switch
//*Output24*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut24 [] PROGMEM  = "mega/subout24";//Here you need to write your subtopic
const char  PubTopicOut24 [] PROGMEM  = "mega/pubout24";//Here you need to write your pubtopic
const boolean OutputType24 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate24 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch24 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType24 = false;                     //True = normal switch   false = push button
const int     OutSwitch24 = 0;                          //Here you can chose the input that used as switch
//*Output25*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut25 [] PROGMEM  = "mega/subout25";//Here you need to write your subtopic
const char  PubTopicOut25 [] PROGMEM  = "mega/pubout25";//Here you need to write your pubtopic
const boolean OutputType25 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate25 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch25 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType25 = false;                     //True = normal switch   false = push button
const int     OutSwitch25 = 0;                          //Here you can chose the input that used as switch
//*Output26*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut26 [] PROGMEM  = "mega/subout26";//Here you need to write your subtopic
const char  PubTopicOut26 [] PROGMEM  = "mega/pubout26";//Here you need to write your pubtopic
const boolean OutputType26 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate26 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch26 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType26 = false;                     //True = normal switch   false = push button
const int     OutSwitch26 = 0;                          //Here you can chose the input that used as switch
//*Output27*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut27 [] PROGMEM  = "mega/subout27";//Here you need to write your subtopic
const char  PubTopicOut27 [] PROGMEM  = "mega/pubout27";//Here you need to write your pubtopic
const boolean OutputType27 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate27 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch27 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType27 = false;                     //True = normal switch   false = push button
const int     OutSwitch27 = 0;                          //Here you can chose the input that used as switch
//*Output28*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut28 [] PROGMEM  = "mega/subout28";//Here you need to write your subtopic
const char  PubTopicOut28 [] PROGMEM  = "mega/pubout28";//Here you need to write your pubtopic
const boolean OutputType28 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate28 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch28 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType28 = false;                     //True = normal switch   false = push button
const int     OutSwitch28 = 0;                          //Here you can chose the input that used as switch
//*Output29*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut29 [] PROGMEM  = "mega/subout29";//Here you need to write your subtopic
const char  PubTopicOut29 [] PROGMEM  = "mega/pubout29";//Here you need to write your pubtopic
const boolean OutputType29 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate29 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch29 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType29 = false;                     //True = normal switch   false = push button
const int     OutSwitch29 = 0;                          //Here you can chose the input that used as switch
//*Output30*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut30 [] PROGMEM  = "mega/subout30";//Here you need to write your subtopic
const char  PubTopicOut30 [] PROGMEM  = "mega/pubout30";//Here you need to write your pubtopic
const boolean OutputType30 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate30 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch30 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType30 = false;                     //True = normal switch   false = push button
const int     OutSwitch30 = 0;                          //Here you can chose the input that used as switch
//*Output 31*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut31 [] PROGMEM  = "mega/subout31";//Here you need to write your subtopic
const char  PubTopicOut31 [] PROGMEM  = "mega/pubout31";//Here you need to write your pubtopic
const boolean OutputType31  = false;                    //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate31 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch31 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType31 = false;                     //True = normal switch   false = push button
const int     OutSwitch31 = 0;                          //Here you can chose the input that used as switch
//*Output32*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut32 [] PROGMEM  = "mega/subout32";//Here you need to write your subtopic
const char  PubTopicOut32 [] PROGMEM  = "mega/pubout32";//Here you need to write your pubtopic
const boolean OutputType32 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate32 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch32 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType32 = false;                     //True = normal switch   false = push button
const int     OutSwitch32 = 0;                          //Here you can chose the input that used as switch
//*Output33*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut33 [] PROGMEM  = "mega/subout33";//Here you need to write your subtopic
const char  PubTopicOut33 [] PROGMEM  = "mega/pubout33";//Here you need to write your pubtopic
const boolean OutputType33 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate33 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch33 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType33 = false;                     //True = normal switch   false = push button
const int     OutSwitch33 = 0;                          //Here you can chose the input that used as switch
//*Output34*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut34 [] PROGMEM  = "mega/subout34";//Here you need to write your subtopic
const char  PubTopicOut34 [] PROGMEM  = "mega/pubout34";//Here you need to write your pubtopic
const boolean OutputType34 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate34 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch34 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType34 = false;                     //True = normal switch   false = push button
const int     OutSwitch34 = 0;                          //Here you can chose the input that used as switch
//*Output35*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut35 [] PROGMEM  = "mega/subout35";//Here you need to write your subtopic
const char  PubTopicOut35 [] PROGMEM  = "mega/pubout35";//Here you need to write your pubtopic
const boolean OutputType35 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate35 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch35 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType35 = false;                     //True = normal switch   false = push button
const int     OutSwitch35 = 0;                          //Here you can chose the input that used as switch
//*Output36*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicOut36 [] PROGMEM  = "mega/subout36";//Here you need to write your subtopic
const char  PubTopicOut36 [] PROGMEM  = "mega/pubout36";//Here you need to write your pubtopic
const boolean OutputType36 = false;                     //True = analog(only in PWM capable outputs) and have a different topic that looks like subtopic name + /brightness int that case that mean "mega/subout.../brightness" and "mega/pubout...(output number)/brightness"  False = digital
const boolean OutAsTermostate36 = false;                //Here you can chose out put to be a virtualy controlled termostate this can be used for heaters and heat valves
const boolean  AtachSwitch36 =  false;                  //If you wanted a switch you need to chose true
const boolean SwitchType36 = false;                     //True = normal switch   false = push button
const int     OutSwitch36 = 0;                          //Here you can chose the input that used as switch
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//**********************************************************************Inputs**********************************************************************************/
//*Input1*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn1 [] PROGMEM  = "mega/subin1";    //Here you need to write your subtopic
const char  PubTopicIn1 [] PROGMEM  = "mega/pubin1";    //Here you need to write your pubtopic
const boolean InputAsSwitch1 = true;                    //Here you can chose input a switch
const boolean InputSwitchType1 = true;                  //True = push button False = normal switch
const boolean InputType1 = false;                       //True = analog false = digital
const boolean AnalogMeter1 = false;                     //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input2*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn2 [] PROGMEM  = "mega/subin2";    //Here you need to write your subtopic
const char  PubTopicIn2 [] PROGMEM  = "mega/pubin2";    //Here you need to write your pubtopic
const boolean InputAsSwitch2 = true;                    //Here you can chose input a switch
const boolean InputSwitchType2 = true;                  //True = push button False = normal switch
const boolean InputType2 = false;                       //True = analog false = digital
const boolean AnalogMeter2 = false;                     //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input3*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn3 [] PROGMEM  = "mega/subin3";    //Here you need to write your subtopic
const char  PubTopicIn3 [] PROGMEM  = "mega/pubin3";    //Here you need to write your pubtopic
const boolean InputAsSwitch3 = true;                    //Here you can chose input a switch
const boolean InputSwitchType3 = true;                  //True = push button False = normal switch
const boolean InputType3 = false;                       //True = analog false = digital
const boolean AnalogMeter3 = false;                     //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input4*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn4 [] PROGMEM  = "mega/subin4";    //Here you need to write your subtopic
const char  PubTopicIn4 [] PROGMEM  = "mega/pubin4";    //Here you need to write your pubtopic
const boolean InputAsSwitch4 = true;                    //Here you can chose input a switch
const boolean InputSwitchType4 = true;                  //True = push button False = normal switch
const boolean InputType4 = false;                       //True = analog false = digital
const boolean AnalogMeter4 = false;                     //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input5*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn5 [] PROGMEM  = "mega/subin5";    //Here you need to write your subtopic
const char  PubTopicIn5 [] PROGMEM  = "mega/pubin5";    //Here you need to write your pubtopic
const boolean InputAsSwitch5 = true;                    //Here you can chose input a switch
const boolean InputSwitchType5 = true;                  //True = push button False = normal switch
const boolean InputType5 = false;                       //True = analog false = digital
const boolean AnalogMeter5 = false;                     //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input6*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn6 [] PROGMEM  = "mega/subin6";    //Here you need to write your subtopic
const char  PubTopicIn6 [] PROGMEM  = "mega/pubin6";    //Here you need to write your pubtopic
const boolean InputAsSwitch6 = true;                    //Here you can chose input a switch
const boolean InputSwitchType6 = true;                  //True = push button False = normal switch
const boolean InputType6 = false;                       //True = analog false = digital
const boolean AnalogMeter6 = false;                     //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input7*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn7 [] PROGMEM  = "mega/subin7";    //Here you need to write your subtopic
const char  PubTopicIn7 [] PROGMEM  = "mega/pubin7";    //Here you need to write your pubtopic
const boolean InputAsSwitch7 = true;                    //Here you can chose input a switch
const boolean InputSwitchType7 = true;                  //True = push button False = normal switch
const boolean InputType7 = false;                       //True = analog false = digital
const boolean AnalogMeter7 = false;                     //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input8*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn8 [] PROGMEM  = "mega/subin8";    //Here you need to write your subtopic
const char  PubTopicIn8 [] PROGMEM  = "mega/pubin8";    //Here you need to write your pubtopic
const boolean InputAsSwitch8 = true;                    //Here you can chose input a switch
const boolean InputSwitchType8 = true;                  //True = push button False = normal switch
const boolean InputType8 = false;                       //True = analog false = digital
const boolean AnalogMeter8 = false;                     //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input9*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn9 [] PROGMEM  = "mega/subin9";    //Here you need to write your subtopic
const char  PubTopicIn9 [] PROGMEM  = "mega/pubin9";    //Here you need to write your pubtopic
const boolean InputAsSwitch9 = true;                    //Here you can chose input a switch
const boolean InputSwitchType9 = true;                  //True = push button False = normal switch
const boolean InputType9 = false;                       //True = analog false = digital
const boolean AnalogMeter9 = false;                     //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input10*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn10 [] PROGMEM  = "mega/subin10";  //Here you need to write your subtopic
const char  PubTopicIn10 [] PROGMEM  = "mega/pubin10";  //Here you need to write your pubtopic
const boolean InputAsSwitch10 = true;                   //Here you can chose input a switch
const boolean InputSwitchType10 = true;                 //True = push button False = normal switch
const boolean InputType10 = false;                      //True = analog false = digital
const boolean AnalogMeter10 = false;                    //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input11*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn11 [] PROGMEM  = "mega/subin11";  //Here you need to write your subtopic
const char  PubTopicIn11 [] PROGMEM  = "mega/pubin11";  //Here you need to write your pubtopic
const boolean InputAsSwitch11 = true;                   //Here you can chose input a switch
const boolean InputSwitchType11 = true;                 //True = push button False = normal switch
const boolean InputType11 = false;                      //True = analog false = digital
const boolean AnalogMeter11 = false;                    //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input12*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn12 [] PROGMEM  = "mega/subin12";  //Here you need to write your subtopic
const char  PubTopicIn12 [] PROGMEM  = "mega/pubin12";  //Here you need to write your pubtopic
const boolean InputAsSwitch12 = true;                   //Here you can chose input a switch
const boolean InputSwitchType12 = true;                 //True = push button False = normal switch
const boolean InputType12 = false;                      //True = analog false = digital
const boolean AnalogMeter12 = false;                    //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input13*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn13 [] PROGMEM  = "mega/subin13";  //Here you need to write your subtopic
const char  PubTopicIn13 [] PROGMEM  = "mega/pubin13";  //Here you need to write your pubtopic
const boolean InputAsSwitch13 = true;                   //Here you can chose input a switch
const boolean InputSwitchType13 = true;                 //True = push button False = normal switch
const boolean InputType13 = false;                      //True = analog false = digital
const boolean AnalogMeter13 = false;                    //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input14*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn14 [] PROGMEM  = "mega/subin14";  //Here you need to write your subtopic
const char  PubTopicIn14 [] PROGMEM  = "mega/pubin14";  //Here you need to write your pubtopic
const boolean InputAsSwitch14 = true;                   //Here you can chose input a switch
const boolean InputSwitchType14 = true;                 //True = push button False = normal switch
const boolean InputType14 = false;                      //True = analog false = digital
const boolean AnalogMeter14 = false;                    //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input15*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn15 [] PROGMEM  = "mega/subin15";  //Here you need to write your subtopic
const char  PubTopicIn15 [] PROGMEM  = "mega/pubin15";  //Here you need to write your pubtopic
const boolean InputAsSwitch15 = true;                   //Here you can chose input a switch
const boolean InputSwitchType15 = true;                 //True = push button False = normal switch
const boolean InputType15 = false;                      //True = analog false = digital
const boolean AnalogMeter15 = false;                    //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input16*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn16 [] PROGMEM  = "mega/subin16";            //Here you need to write your subtopic
const char  PubTopicIn16 [] PROGMEM  = "mega/pubin16";            //Here you need to write your pubtopic
const boolean InputAsSwitch16 = true;        //Here you can chose input a switch
const boolean InputSwitchType16 = true;      //True = push button False = normal switch
const boolean InputType16 = false;                  //True = analog false = digital
const boolean AnalogMeter16 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input17*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn17 [] PROGMEM  = "mega/subin17";            //Here you need to write your subtopic
const char  PubTopicIn17 [] PROGMEM  = "mega/pubin17";            //Here you need to write your pubtopic
const boolean InputAsSwitch17 = true;        //Here you can chose input a switch
const boolean InputSwitchType17 = true;      //True = push button False = normal switch
const boolean InputType17 = false;                  //True = analog false = digital
const boolean AnalogMeter17 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input18*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn18 [] PROGMEM  = "mega/subin18";            //Here you need to write your subtopic
const char  PubTopicIn18 [] PROGMEM  = "mega/pubin18";            //Here you need to write your pubtopic
const boolean InputAsSwitch18 = true;        //Here you can chose input a switch
const boolean InputSwitchType18 = true;      //True = push button False = normal switch
const boolean InputType18 = false;                  //True = analog false = digital
const boolean AnalogMeter18 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input19*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn19 [] PROGMEM  = "mega/subin19";            //Here you need to write your subtopic
const char  PubTopicIn19 [] PROGMEM  = "mega/pubin19";            //Here you need to write your pubtopic
const boolean InputAsSwitch19 = true;        //Here you can chose input a switch
const boolean InputSwitchType19 = true;      //True = push button False = normal switch
const boolean InputType19 = false;                  //True = analog false = digital
const boolean AnalogMeter19 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input20*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn20 [] PROGMEM  = "mega/subin20";            //Here you need to write your subtopic
const char  PubTopicIn20 [] PROGMEM  = "mega/pubin20";            //Here you need to write your pubtopic
const boolean InputAsSwitch20 = true;        //Here you can chose input a switch
const boolean InputSwitchType20 = true;      //True = push button False = normal switch
const boolean InputType20 = false;                  //True = analog false = digital
const boolean AnalogMeter20 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input21*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn21 [] PROGMEM  = "mega/subin21";            //Here you need to write your subtopic
const char  PubTopicIn21 [] PROGMEM  = "mega/pubin21";            //Here you need to write your pubtopic
const boolean InputAsSwitch21 = true;        //Here you can chose input a switch
const boolean InputSwitchType21 = true;      //True = push button False = normal switch
const boolean InputType21 = false;                  //True = analog false = digital
const boolean AnalogMeter21 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input22*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn22 [] PROGMEM  = "mega/subin22";            //Here you need to write your subtopic
const char  PubTopicIn22 [] PROGMEM  = "mega/pubin22";            //Here you need to write your pubtopic
const boolean InputAsSwitch22 = true;        //Here you can chose input a switch
const boolean InputSwitchType22 = true;      //True = push button False = normal switch
const boolean InputType22 = false;                  //True = analog false = digital
const boolean AnalogMeter22 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input23*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn23 [] PROGMEM  = "mega/subin23";            //Here you need to write your subtopic
const char  PubTopicIn23 [] PROGMEM  = "mega/pubin23";            //Here you need to write your pubtopic
const boolean InputAsSwitch23 = true;        //Here you can chose input a switch
const boolean InputSwitchType23 = true;      //True = push button False = normal switch
const boolean InputType23 = false;                  //True = analog false = digital
const boolean AnalogMeter23 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input24*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn24 [] PROGMEM  = "mega/subin24";            //Here you need to write your subtopic
const char  PubTopicIn24 [] PROGMEM  = "mega/pubin24";            //Here you need to write your pubtopic
const boolean InputAsSwitch24 = true;        //Here you can chose input a switch
const boolean InputSwitchType24 = true;      //True = push button False = normal switch
const boolean InputType24 = false;                  //True = analog false = digital
const boolean AnalogMeter24 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input25*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn25 [] PROGMEM  = "mega/subin25";            //Here you need to write your subtopic
const char  PubTopicIn25 [] PROGMEM  = "mega/pubin25";            //Here you need to write your pubtopic
const boolean InputAsSwitch25 = true;        //Here you can chose input a switch
const boolean InputSwitchType25 = true;      //True = push button False = normal switch
const boolean InputType25 = false;                  //True = analog false = digital
const boolean AnalogMeter25 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input26*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn26 [] PROGMEM  = "mega/subin26";            //Here you need to write your subtopic
const char  PubTopicIn26 [] PROGMEM  = "mega/pubin26";            //Here you need to write your pubtopic
const boolean InputAsSwitch26 = true;        //Here you can chose input a switch
const boolean InputSwitchType26 = true;      //True = push button False = normal switch
const boolean InputType26 = false;                  //True = analog false = digital
const boolean AnalogMeter26 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
//*Input27*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicIn27 [] PROGMEM  = "mega/subin27";            //Here you need to write your subtopic
const char  PubTopicIn27 [] PROGMEM  = "mega/pubin27";            //Here you need to write your pubtopic
const boolean InputAsSwitch27 = true;        //Here you can chose input a switch
const boolean InputSwitchType27 = true;      //True = push button False = normal switch
const boolean InputType27 = false;                  //True = analog false = digital
const boolean AnalogMeter27 = false;            //true = analog  meter false = no meter You can only chose analog meters here  The value will be 0-1023 (10bit )
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************************Temperature and humidity sensors*********************************************************************************/
//The message will look like this --> {"name": "xxxx", "id": "xxxx", "temperature": "xxxx", "humidity": "xxxx"}
#define ONE_WIRE_BUS 9 //The one wire bus is needed for DS18b20!!!
//*Temp1*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp1 [] PROGMEM  = "mega/pubtempsensor1";                    //Here you need to write your pubtopic
const char  PubTopicHumidity1 [] PROGMEM  = "mega/pubhumiditysensor1";           //Here you need to write your pubtopic
const char  TempSensorName1 [] PROGMEM  = "Temp1";                               //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId1 [] PROGMEM  = "00xx";                                  //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType1 = true;                                            //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER1 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94}; //If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor1  = false;                                          //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp1//YOU NEED TO REMOVE "//" TO DEFINE DHT!!!             //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE1 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin1 = 0;                                                    //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp2*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp2 [] PROGMEM  = "mega/pubtempsensor2";                    //Here you need to write your pubtopic
const char  PubTopicHumidity2 [] PROGMEM  = "mega/pubhumiditysensor2";           //Here you need to write your pubtopic
const char  TempSensorName2 [] PROGMEM  = "Temp2";                               //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId2 [] PROGMEM  = "00xx";                                  //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType2 = true;                                            //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER2 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94}; //If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor2  = false;                                          //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp2                                                       //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE2 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin2 = 0;                                                    //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp3*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp3 [] PROGMEM  = "mega/pubtempsensor3";                    //Here you need to write your pubtopic
const char  PubTopicHumidity3 [] PROGMEM  = "mega/pubhumiditysensor3";           //Here you need to write your pubtopic
const char  TempSensorName3 [] PROGMEM  = "Temp3";                               //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId3 [] PROGMEM  = "00xx";                                  //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType3 = true;                                            //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER3 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94}; //If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor3  = false;                                          //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp3                                                       //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE3 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin3 = 0;                                                    //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp4*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp4 [] PROGMEM  = "mega/pubtempsensor4";                    //Here you need to write your pubtopic
const char  PubTopicHumidity4 [] PROGMEM  = "mega/pubhumiditysensor4";           //Here you need to write your pubtopic
const char  TempSensorName4 [] PROGMEM  = "Temp4";                               //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId4 [] PROGMEM  = "00xx";                                  //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType4 = true;                                            //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER4 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94}; //If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor4  = false;                                          //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp4                                                       //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE4 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin4 = 0;                                                    //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp5*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp5 [] PROGMEM  = "mega/pubtempsensor5";                    //Here you need to write your pubtopic
const char  PubTopicHumidity5 [] PROGMEM  = "mega/pubhumiditysensor5";           //Here you need to write your pubtopic
const char  TempSensorName5 [] PROGMEM  = "Temp5";                               //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId5 [] PROGMEM  = "00xx";                                  //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType5 = true;                                            //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER5 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94}; //If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor5  = false;                                          //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp5                                                       //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE6 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin5 = 0;                                                    //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp6*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp6 [] PROGMEM  = "mega/pubtempsensor6";                    //Here you need to write your pubtopic
const char  PubTopicHumidity6 [] PROGMEM  = "mega/pubhumiditysensor6";           //Here you need to write your pubtopic
const char  TempSensorName6 [] PROGMEM  = "Temp6";                               //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId6 [] PROGMEM  = "00xx";                                  //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType6 = true;                                            //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER6 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94}; //If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor6  = false;                                          //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp6                                                       //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE6 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin6 = 0;                                                    //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp7*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp7 [] PROGMEM  = "mega/pubtempsensor7";                    //Here you need to write your pubtopic
const char  PubTopicHumidity7 [] PROGMEM  = "mega/pubhumiditysensor7";           //Here you need to write your pubtopic
const char  TempSensorName7 [] PROGMEM  = "Temp7";                               //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId7 [] PROGMEM  = "00xx";                                  //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType7 = true;                                            //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER7 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94}; //If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor7  = false;                                          //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp7                                                       //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE7 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin7 = 0;                                                    //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp8*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp8 [] PROGMEM  = "mega/pubtempsensor8";                    //Here you need to write your pubtopic
const char  PubTopicHumidity8 [] PROGMEM  = "mega/pubhumiditysensor8";           //Here you need to write your pubtopic
const char  TempSensorName8 [] PROGMEM  = "Temp8";                               //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId8 [] PROGMEM  = "00xx";                                  //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType8 = true;                                            //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER8 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94}; //If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor8  = false;                                          //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp8                                                       //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE8 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin8 = 0;                                                    //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp9*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp9 [] PROGMEM  = "mega/pubtempsensor9";                    //Here you need to write your pubtopic
const char  PubTopicHumidity9 [] PROGMEM  = "mega/pubhumiditysensor9";           //Here you need to write your pubtopic
const char  TempSensorName9 [] PROGMEM  = "Temp9";                               //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId9 [] PROGMEM  = "00xx";                                  //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType9 = true;                                            //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER9 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94}; //If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor9  = false;                                          //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp9                                                       //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE9 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin9 = 0;                                                    //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp10*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp10 [] PROGMEM  = "mega/pubtempsensor10";                  //Here you need to write your pubtopic
const char  PubTopicHumidity10 [] PROGMEM  = "mega/pubhumiditysensor10";         //Here you need to write your pubtopic
const char  TempSensorName10 [] PROGMEM  = "Temp10";                             //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId10 [] PROGMEM  = "00xx";                                 //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType10 = true;                                           //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER10 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94};//If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor10  = false;                                         //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp10                                                      //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE10 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin10 = 0;                                                   //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp11*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp11 [] PROGMEM  = "mega/pubtempsensor11";                  //Here you need to write your pubtopic
const char  PubTopicHumidity11 [] PROGMEM  = "mega/pubhumiditysensor11";         //Here you need to write your pubtopic
const char  TempSensorName11 [] PROGMEM  = "Temp11";                             //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId11 [] PROGMEM  = "00xx";                                 //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType11 = true;                                           //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER11 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94};//If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor11  = false;                                         //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp11                                                      //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE11 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin11 = 0;                                                   //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp12*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp12 [] PROGMEM  = "mega/pubtempsensor12";                  //Here you need to write your pubtopic
const char  PubTopicHumidity12 [] PROGMEM  = "mega/pubhumiditysensor12";         //Here you need to write your pubtopic
const char  TempSensorName12 [] PROGMEM  = "Temp12";                             //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId12 [] PROGMEM  = "00xx";                                 //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType12 = true;                                           //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER12 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94};//If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor12  = false;                                         //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp12                                                      //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE12 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin12 = 0;                                                   //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp13*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp13 [] PROGMEM  = "mega/pubtempsensor13";                  //Here you need to write your pubtopic
const char  PubTopicHumidity13 [] PROGMEM  = "mega/pubhumiditysensor13";         //Here you need to write your pubtopic
const char  TempSensorName13 [] PROGMEM  = "Temp13";                             //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId13 [] PROGMEM  = "00xx";                                 //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType13 = true;                                           //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER13 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94};//If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor13  = false;                                         //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp13                                                      //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE13 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin13 = 0;                                                   //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp14*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp14 [] PROGMEM  = "mega/pubtempsensor14";                  //Here you need to write your pubtopic
const char  PubTopicHumidity14 [] PROGMEM  = "mega/pubhumiditysensor14";         //Here you need to write your pubtopic
const char  TempSensorName14 [] PROGMEM  = "Temp14";                             //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId14 [] PROGMEM  = "00xx";                                 //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType14 = true;                                           //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER14 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94};//If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor14  = false;                                         //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp14                                                      //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE14 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin14 = 0;                                                   //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp15*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp15 [] PROGMEM  = "mega/pubtempsensor15";                  //Here you need to write your pubtopic
const char  PubTopicHumidity15 [] PROGMEM  = "mega/pubhumiditysensor15";         //Here you need to write your pubtopic
const char  TempSensorName15 [] PROGMEM  = "Temp15";                             //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId15 [] PROGMEM  = "00xx";                                 //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType15 = true;                                           //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER15 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94};//If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor15  = false;                                         //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp15                                                      //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE15 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin15 = 0;                                                   //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp16*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp16 [] PROGMEM  = "mega/pubtempsensor16";                  //Here you need to write your pubtopic
const char  PubTopicHumidity16 [] PROGMEM  = "mega/pubhumiditysensor16";         //Here you need to write your pubtopic
const char  TempSensorName16 [] PROGMEM  = "Temp16";                             //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId16 [] PROGMEM  = "00xx";                                 //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType16 = true;                                           //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER16 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94};//If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor16  = false;                                         //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp16                                                      //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE16 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin16 = 0;                                                   //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp17*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp17 [] PROGMEM  = "mega/pubtempsensor17";                  //Here you need to write your pubtopic
const char  PubTopicHumidity17 [] PROGMEM  = "mega/pubhumiditysensor17";         //Here you need to write your pubtopic
const char  TempSensorName17 [] PROGMEM  = "Temp17";                             //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId17 [] PROGMEM  = "00xx";                                 //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType17 = true;                                           //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER17 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94};//If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor17  = false;                                         //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp17                                                      //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE17 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin17 = 0;                                                   //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//*Temp18*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicTemp18 [] PROGMEM  = "mega/pubtempsensor18";                  //Here you need to write your pubtopic
const char  PubTopicHumidity18 [] PROGMEM  = "mega/pubhumiditysensor18";         //Here you need to write your pubtopic
const char  TempSensorName18 [] PROGMEM  = "Temp18";                             //Here you can name your temp sensor for example "kitchen temperature" this will help you in debugg
const char  TempSensorId18 [] PROGMEM  = "00xx";                                 //Here you can write your temp sensor id this can be helpful for debug or double checking who published the temp data
const boolean TempSensorType18 = true;                                           //True = DS18B20 False = lm35/dht11 --if TempSensorPin  need to be filled up
const uint8_t TEMPMETER18 [8] = {0x28, 0x8B, 0x8D, 0x76, 0xE0, 0x01, 0x3C, 0x94};//If ds18b20 choosed you need to fill this with your sensor adress!!!!!!!!!!!!!
const boolean LM35TempSensor18  = false;                                         //True = LM35 False = you need to chose thid if you want to use ds18b20 or dht11!!!
//#define       DHT11Temp18                                                      //If defined DHT11    else = LM35  Only dht11 will publish hudimity data
//#define       DHTTYPE18 DHT11                                                   //Here you can chose your dht model
const int TempSensorPin18 = 0;                                                   //You write here the chosen input number Example: const int TempSensorPin = INPUT1; The choosen input settings needs to be blank!!!!!!
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************Heating / Cooling system set up****************************************************************/
const int HVACS = 9;// This can be lower if you dont use 9 heater you should write the number os your setup bacause the software will run faster
const int DigitalTermostateAndPumpOutput = OUTPUT1;// Here you chose the heat pump ad boiler termostate relay OUTPUT. You need to chose as const boolean OutAsTermostateXY... = true  
//*HVAC1*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicHvacTemp1 [] PROGMEM  = "mega/pubhvactemp1";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicHvacTemp1 [] PROGMEM  = "mega/subhvactemp1";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicHvacMode1 [] PROGMEM  = "mega/pubhvacmode1";   //Here you can write your pubtopic for the actual mode 
const char SubTopicHvacMode1 [] PROGMEM  = "mega/subhvacmode1";   //Here you can write your subtopic for the actual mode
const char HvacName1         [] PROGMEM  = "";                    //Here you can write your Hvac Name
const char HvacId1           [] PROGMEM  = "00xx";                //Here you can write your Hvac Id
const char HvacRoom1         [] PROGMEM  = "";                    //Here you can write your Hvac Room where you use it
const int  HvacTempsensor1 = 0;                                   //You can chose here the HVAC TEMP sensor here but for the virtual termostate output you need to chose the output pin and that same temp sensor (the temp sensor connect the hvac output logic here!!!!!!!!)
const int  HvacOutput1 = 0;                                       //You can chose the temp valve output pin here
//*HVAC2*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicHvacTemp2 [] PROGMEM  = "mega/pubhvactemp2";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicHvacTemp2 [] PROGMEM  = "mega/subhvactemp2";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicHvacMode2 [] PROGMEM  = "mega/pubhvacmode2";   //Here you can write your pubtopic for the actual mode 
const char SubTopicHvacMode2 [] PROGMEM  = "mega/subhvacmode2";   //Here you can write your subtopic for the actual mode
const char HvacName2         [] PROGMEM  = "";                    //Here you can write your Hvac Name
const char HvacId2           [] PROGMEM  = "00xx";                //Here you can write your Hvac Id
const char HvacRoom2         [] PROGMEM  = "";                    //Here you can write your Hvac Room where you use it
const int  HvacTempsensor2 = 0;                                   //You can chose here the HVAC TEMP sensor here but for the virtual termostate output you need to chose the output pin and that same temp sensor (the temp sensor connect the hvac output logic here!!!!!!!!)
const int  HvacOutput2 = 0;                                       //You can chose the temp valve output pin here
//*HVAC3*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicHvacTemp3 [] PROGMEM  = "mega/pubhvactemp3";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicHvacTemp3 [] PROGMEM  = "mega/subhvactemp3";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicHvacMode3 [] PROGMEM  = "mega/pubhvacmode3";   //Here you can write your pubtopic for the actual mode 
const char SubTopicHvacMode3 [] PROGMEM  = "mega/subhvacmode3";   //Here you can write your subtopic for the actual mode
const char HvacName3         [] PROGMEM  = "";                    //Here you can write your Hvac Name
const char HvacId3           [] PROGMEM  = "00xx";                //Here you can write your Hvac Id
const char HvacRoom3         [] PROGMEM  = "";                    //Here you can write your Hvac Room where you use it
const int  HvacTempsensor3 = 0;                                   //You can chose here the HVAC TEMP sensor here but for the virtual termostate output you need to chose the output pin and that same temp sensor (the temp sensor connect the hvac output logic here!!!!!!!!)
const int  HvacOutput3 = 0;                                       //You can chose the temp valve output pin here
//*HVAC4*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicHvacTemp4 [] PROGMEM  = "mega/pubhvactemp4";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicHvacTemp4 [] PROGMEM  = "mega/subhvactemp4";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicHvacMode4 [] PROGMEM  = "mega/pubhvacmode4";   //Here you can write your pubtopic for the actual mode 
const char SubTopicHvacMode4 [] PROGMEM  = "mega/subhvacmode4";   //Here you can write your subtopic for the actual mode
const char HvacName4         [] PROGMEM  = "";                    //Here you can write your Hvac Name
const char HvacId4           [] PROGMEM  = "00xx";                //Here you can write your Hvac Id
const char HvacRoom4         [] PROGMEM  = "";                    //Here you can write your Hvac Room where you use it
const int  HvacTempsensor4 = 0;                                   //You can chose here the HVAC TEMP sensor here but for the virtual termostate output you need to chose the output pin and that same temp sensor (the temp sensor connect the hvac output logic here!!!!!!!!)
const int  HvacOutput4 = 0;                                       //You can chose the temp valve output pin here
//*HVAC5*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicHvacTemp5 [] PROGMEM  = "mega/pubhvactemp5";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicHvacTemp5 [] PROGMEM  = "mega/subhvactemp5";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicHvacMode5 [] PROGMEM  = "mega/pubhvacmode5";   //Here you can write your pubtopic for the actual mode 
const char SubTopicHvacMode5 [] PROGMEM  = "mega/subhvacmode5";   //Here you can write your subtopic for the actual mode
const char HvacName5         [] PROGMEM  = "";                    //Here you can write your Hvac Name
const char HvacId5           [] PROGMEM  = "00xx";                //Here you can write your Hvac Id
const char HvacRoom5         [] PROGMEM  = "";                    //Here you can write your Hvac Room where you use it
const int  HvacTempsensor5 = 0;                                   //You can chose here the HVAC TEMP sensor here but for the virtual termostate output you need to chose the output pin and that same temp sensor (the temp sensor connect the hvac output logic here!!!!!!!!)
const int  HvacOutput5 = 0;                                       //You can chose the temp valve output pin here
//*HVAC6*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicHvacTemp6 [] PROGMEM  = "mega/pubhvactemp6";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicHvacTemp6 [] PROGMEM  = "mega/subhvactemp6";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicHvacMode6 [] PROGMEM  = "mega/pubhvacmode6";   //Here you can write your pubtopic for the actual mode 
const char SubTopicHvacMode6 [] PROGMEM  = "mega/subhvacmode6";   //Here you can write your subtopic for the actual mode
const char HvacName6         [] PROGMEM  = "";                    //Here you can write your Hvac Name
const char HvacId6           [] PROGMEM  = "00xx";                //Here you can write your Hvac Id
const char HvacRoom6         [] PROGMEM  = "";                    //Here you can write your Hvac Room where you use it
const int  HvacTempsensor6 = 0;                                   //You can chose here the HVAC TEMP sensor here but for the virtual termostate output you need to chose the output pin and that same temp sensor (the temp sensor connect the hvac output logic here!!!!!!!!)
const int  HvacOutput6 = 0;                                       //You can chose the temp valve output pin here
//*HVAC7*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicHvacTemp7 [] PROGMEM  = "mega/pubhvactemp7";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicHvacTemp7 [] PROGMEM  = "mega/subhvactemp7";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicHvacMode7 [] PROGMEM  = "mega/pubhvacmode7";   //Here you can write your pubtopic for the actual mode 
const char SubTopicHvacMode7 [] PROGMEM  = "mega/subhvacmode7";   //Here you can write your subtopic for the actual mode
const char HvacName7         [] PROGMEM  = "";                    //Here you can write your Hvac Name
const char HvacId7           [] PROGMEM  = "00xx";                //Here you can write your Hvac Id
const char HvacRoom7         [] PROGMEM  = "";                    //Here you can write your Hvac Room where you use it
const int  HvacTempsensor7 = 0;                                   //You can chose here the HVAC TEMP sensor here but for the virtual termostate output you need to chose the output pin and that same temp sensor (the temp sensor connect the hvac output logic here!!!!!!!!)
const int  HvacOutput7 = 0;                                       //You can chose the temp valve output pin here
//*HVAC8*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicHvacTemp8 [] PROGMEM  = "mega/pubhvactemp8";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicHvacTemp8 [] PROGMEM  = "mega/subhvactemp8";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicHvacMode8 [] PROGMEM  = "mega/pubhvacmode8";   //Here you can write your pubtopic for the actual mode 
const char SubTopicHvacMode8 [] PROGMEM  = "mega/subhvacmode8";   //Here you can write your subtopic for the actual mode
const char HvacName8         [] PROGMEM  = "";                    //Here you can write your Hvac Name
const char HvacId8           [] PROGMEM  = "00xx";                //Here you can write your Hvac Id
const char HvacRoom8         [] PROGMEM  = "";                    //Here you can write your Hvac Room where you use it
const int  HvacTempsensor8 = 0;                                   //You can chose here the HVAC TEMP sensor here but for the virtual termostate output you need to chose the output pin and that same temp sensor (the temp sensor connect the hvac output logic here!!!!!!!!)
const int  HvacOutput8 = 0;                                       //You can chose the temp valve output pin here
//*HVAC9*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicHvacTemp9 [] PROGMEM  = "mega/pubhvactemp9";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicHvacTemp9 [] PROGMEM  = "mega/subhvactemp9";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicHvacMode9 [] PROGMEM  = "mega/pubhvacmode9";   //Here you can write your pubtopic for the actual mode 
const char SubTopicHvacMode9 [] PROGMEM  = "mega/subhvacmode9";   //Here you can write your subtopic for the actual mode
const char HvacName9         [] PROGMEM  = " ";                   //Here you can write your Hvac Name
const char HvacId9           [] PROGMEM  = "00xx";                //Here you can write your Hvac Id
const char HvacRoom9         [] PROGMEM  = "";                    //Here you can write your Hvac Room where you use it
const int  HvacTempsensor9 = 0;                                   //You can chose here the HVAC TEMP sensor here but for the virtual termostate output you need to chose the output pin and that same temp sensor (the temp sensor connect the hvac output logic here!!!!!!!!)
const int  HvacOutput9 = 0;                                       //You can chose the temp valve output pin here
//******************************************************************************************************************************************************************************************************/
//*****************************************************************************************************Impulse Based Energy Meter***********************************************************************/
//******************************************************************************************************************************************************************************************************/
//The paylod will look like this {"name" = "xyz","id" = "xyz", "power" = "measured numbers only", "unit_of_measurement" = "xyz"}
//Energy Meter 1//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicPowerMeter1 [] PROGMEM = "mega/pubpowerstate1"; //Mqtt publishing topic
const char PowerMeterName1 [] PROGMEM = "Main Utility Meter";      //Your device name
const char PowerMeterId1 [] PROGMEM = "01";                        //Your dewice Id
const char PowerMeterUnitOfMesurement1 [] PROGMEM = "KW/h";        //This only for energy meters
const int  PowerMeterSensorPin1 = 0;                               //This pin will work digitaly you need a simple circuit like this: https://arduinogetstarted.com/tutorials/arduino-light-sensor but you need a potmeter instead of a resistor and the circuit is nned to set properly for each sensor
const int  ImpulsInOneUnit1 = 1000;                                  //You can see the value in your utility power meter this value is usaly see uner your led 
//Energy Meter 2//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicPowerMeter2 [] PROGMEM = "mega/pubpowerstate2"; //Mqtt publishing topic
const char PowerMeterName2 [] PROGMEM = "Solar Power Meter";       //Your device name
const char PowerMeterId2 [] PROGMEM = "02";                        //Your dewice Id
const char PowerMeterUnitOfMesurement2 [] PROGMEM = "KW/h";        //This only for energy meters
const int  PowerMeterSensorPin2 = 0;                               //This pin will work digitaly you need a simple circuit like this: https://arduinogetstarted.com/tutorials/arduino-light-sensor but you need a potmeter instead of a resistor and the circuit is nned to set properly for each sensor
const int  ImpulsInOneUnit2 = 1000;                                  //You can see the value in your utility power meter this value is usaly see uner your led 
//Energy Meter 3//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicPowerMeter3 [] PROGMEM = "mega/pubpowerstate3"; //Mqtt publishing topic
const char PowerMeterName3 [] PROGMEM = "Main Utility Meter";      //Your device name
const char PowerMeterId3 [] PROGMEM = "03";                        //Your dewice Id
const char PowerMeterUnitOfMesurement3 [] PROGMEM = "KW/h";        //This only for energy meters
const int  PowerMeterSensorPin3 = 0;                               //This pin will work digitaly you need a simple circuit like this: https://arduinogetstarted.com/tutorials/arduino-light-sensor but you need a potmeter instead of a resistor and the circuit is nned to set properly for each sensor
const int  ImpulsInOneUnit3 = 1000;                                  //You can see the value in your utility power meter this value is usaly see uner your led 
//*****************************************************************************************************************************************************************************************************/
//******************************************************************************************************CAN EXPANDER SETUP*****************************************************************************/
//*****************************************************************************************************************************************************************************************************/
//The Server just send and recive data dont do anything with that data you need to set te can module separately
//*****************************************************************************************************************************************************************************************************/
//******************************************************************************************************CAN EXPANDER OUTPUT SETUP**********************************************************************/
//*****************************************************************************************************************************************************************************************************/
//If you have more output than 9 you need to continue this pattern for example:
//Can OUTXX/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//const char  SubTopicCanOutXX[] PROGMEM  = "can/suboutXX"; //Here you need to write your subtopic
//const char  PubTopicCanOutXX[] PROGMEM  = "can/puboutXX"; //Here you need to write your pubtopic
//const char  CanOutCommandXX[] PROGMEM = "EOXX=";        //The server will send and recive data to this name this is made possible with a int to char converstaion. That means we can send 8 characters at one time
//AND you also need to change how many outputs in your system in can.h CanOutputs xx (all can outputs)
const char  CanOutPrefix[] = "EO"; //expansion This is needed for faster can response. EO means ExpanderOutput.
//Can OUT1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicCanOut1[] PROGMEM  = "can/subout1"; //Here you need to write your subtopic
const char  PubTopicCanOut1[] PROGMEM  = "can/pubout1"; //Here you need to write your pubtopic
const char  CanOutCommand1[]  PROGMEM = "EO1=";        //The server will send and recive data to this name this is made possible with a int to char converstaion. That means we can send 8 characters at one time
//Can OUT2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicCanOut2[] PROGMEM  = "can/subout2"; //Here you need to write your subtopic
const char  PubTopicCanOut2[] PROGMEM  = "can/pubout2"; //Here you need to write your pubtopic
const char  CanOutCommand2[]  PROGMEM = "EO2=";        //The server will send and recive data to this name this is made possible with a int to char converstaion. That means we can send 8 characters at one time
//Can OUT3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicCanOut3[] PROGMEM  = "can/subout3"; //Here you need to write your subtopic
const char  PubTopicCanOut3[] PROGMEM  = "can/pubout3"; //Here you need to write your pubtopic
const char  CanOutCommand3[] PROGMEM = "EO3=";        //The server will send and recive data to this name this is made possible with a int to char converstaion. That means we can send 8 characters at one time
//Can OUT4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicCanOut4[] PROGMEM  = "can/subout4"; //Here you need to write your subtopic
const char  PubTopicCanOut4[] PROGMEM  = "can/pubout4"; //Here you need to write your pubtopic
const char  CanOutCommand4[]  PROGMEM = "EO4=";        //The server will send and recive data to this name this is made possible with a int to char converstaion. That means we can send 8 characters at one time
//Can OUT5/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicCanOut5[] PROGMEM  = "can/subout5"; //Here you need to write your subtopic
const char  PubTopicCanOut5[] PROGMEM  = "can/pubout5"; //Here you need to write your pubtopic
const char  CanOutCommand5[]  PROGMEM = "EO5=";        //The server will send and recive data to this name this is made possible with a int to char converstaion. That means we can send 8 characters at one time
//Can OUT6/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicCanOut6[] PROGMEM  = "can/subout6"; //Here you need to write your subtopic
const char  PubTopicCanOut6[] PROGMEM  = "can/pubout6"; //Here you need to write your pubtopic
const char  CanOutCommand6[]  PROGMEM = "EO6=";        //The server will send and recive data to this name this is made possible with a int to char converstaion. That means we can send 8 characters at one time
//Can OUT7/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicCanOut7[] PROGMEM  = "can/subout7"; //Here you need to write your subtopic
const char  PubTopicCanOut7[] PROGMEM  = "can/pubout7"; //Here you need to write your pubtopic
const char  CanOutCommand7[]  PROGMEM = "EO7=";        //The server will send and recive data to this name this is made possible with a int to char converstaion. That means we can send 8 characters at one time
//Can OUT8/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicCanOut8[] PROGMEM  = "can/subout8"; //Here you need to write your subtopic
const char  PubTopicCanOut8[] PROGMEM  = "can/pubout8"; //Here you need to write your pubtopic
const char  CanOutCommand8[]  PROGMEM = "EO8=";        //The server will send and recive data to this name this is made possible with a int to char converstaion. That means we can send 8 characters at one time
//Can OUT9/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char  SubTopicCanOut9[] PROGMEM  = "can/subout9"; //Here you need to write your subtopic
const char  PubTopicCanOut9[] PROGMEM  = "can/pubout9"; //Here you need to write your pubtopic
const char  CanOutCommand9[]  PROGMEM = "EO9=";        //The server will send and recive data to this name this is made possible with a int to char converstaion. That means we can send 8 characters at one time
//*****************************************************************************************************************************************************************************************************/
//******************************************************************************************************CAN EXPANDER INPUT SETUP***********************************************************************/
//*****************************************************************************************************************************************************************************************************/
//If you have more input than 9 you need to continue this pattern for example:
//Can INXX/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//const char SubTopicCanInXX[] PROGMEM = "can/subinXX";
//const char PubTopicCanInXX[] PROGMEM = "can/pubinXX";
//const char CanInCommandXX[] PROGMEM = "EIXX=";
//AND you also need to change how many INputs in your system in can.h CanInputs xx (all can inputs)
const char  CanInPrefix[] = "EI";   //This simplyfying is needed for faster can response ei means ExpanderInput.
//Can IN1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char SubTopicCanIn1[] PROGMEM = "can/subin1";
const char PubTopicCanIn1[] PROGMEM = "can/pubin1";
const char CanInCommand1[]  PROGMEM = "EI1=";
//Can IN2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char SubTopicCanIn2[] PROGMEM = "can/subin2";
const char PubTopicCanIn2[] PROGMEM = "can/pubin2";
const char CanInCommand2[]  PROGMEM = "EI2=";
//Can IN3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char SubTopicCanIn3[] PROGMEM = "can/subin3";
const char PubTopicCanIn3[] PROGMEM = "can/pubin3";
const char CanInCommand3[]  PROGMEM = "EI3=";
//Can IN4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char SubTopicCanIn4[] PROGMEM = "can/subin4";
const char PubTopicCanIn4[] PROGMEM = "can/pubin4";
const char CanInCommand4[]  PROGMEM = "EI4=";
//Can IN5/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char SubTopicCanIn5[] PROGMEM = "can/subin5";
const char PubTopicCanIn5[] PROGMEM = "can/pubin5";
const char CanInCommand5[]  PROGMEM = "EI5=";
//Can IN6/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char SubTopicCanIn6[] PROGMEM = "can/subin6";
const char PubTopicCanIn6[] PROGMEM = "can/pubin6";
const char CanInCommand6[]  PROGMEM = "EI6=";
//Can IN7/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char SubTopicCanIn7[] PROGMEM = "can/subin7";
const char PubTopicCanIn7[] PROGMEM = "can/pubin7";
const char CanInCommand7[]  PROGMEM = "EI7=";
//Can IN8/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char SubTopicCanIn8[] PROGMEM = "can/subin8";
const char PubTopicCanIn8[] PROGMEM = "can/pubin8";
const char CanInCommand8[]  PROGMEM = "EI8=";
//Can IN9/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char SubTopicCanIn9[] PROGMEM = "can/subin9";
const char PubTopicCanIn9[] PROGMEM = "can/pubin9";
const char CanInCommand9[]  PROGMEM = "EI9=";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************************************************************************************************************************************************************************************/
//*****************************************************************************CAN EXPANDER TEMPERATURE AND HUMIDITY SETUP*****************************************************************************/
//*****************************************************************************************************************************************************************************************************/
//If you have more tempsensor or humidity sensor than 9 you need to continue this pattern for example:
//Can Temp an Humidity
//const char PubTopicCanTemp[] PROGMEM     = "can/pubtemp";
//const char PubTopicCanHumidity[] PROGMEM = "can/pubhumidity";
//const char CanInCommandTemp[] PROGMEM = "TP=";
//const char CanInCommandHumidity[] PROGMEM = "HU=";
//AND you also need to change how many INputs in your system in can.h CanInputs xx (all can inputs)
//And you need to add the new values in to the "SubTopicCanOut[]etc......" variables
const char CanTempPrefix[] = "ET"; //This is needed for faster can response.
const char CanHumidityPrefix[] = "EH"; //This is needed for faster can response.
//Can Temp an Humidity1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanTemp1[]       PROGMEM = "can/pubtemp1";
const char PubTopicCanHumidity1[]   PROGMEM = "can/pubhumidity1";
const char CanTempSensorName1[]     PROGMEM = "CanTemp1";
const char CanTempSensorId1[]       PROGMEM = "00xx";
const char CanInCommandTemp1[]      PROGMEM = "ET1=";
const char CanInCommandHumidity1[]  PROGMEM = "EH1=";
//Can Temp an Humidity2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanTemp2[]       PROGMEM = "can/pubtemp2";
const char PubTopicCanHumidity2[]   PROGMEM = "can/pubhumidity2";
const char CanTempSensorName2[]     PROGMEM = "CanTemp2";
const char CanTempSensorId2[]       PROGMEM = "00xx";
const char CanInCommandTemp2[]      PROGMEM = "ET2=";
const char CanInCommandHumidity2[]  PROGMEM = "EH2=";
//Can Temp an Humidity3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanTemp3[]       PROGMEM = "can/pubtemp3";
const char PubTopicCanHumidity3[]   PROGMEM = "can/pubhumidity3";
const char CanTempSensorName3[]     PROGMEM = "CanTemp3";
const char CanTempSensorId3[]       PROGMEM = "00xx";
const char CanInCommandTemp3[]      PROGMEM = "EH3=";
const char CanInCommandHumidity3[]  PROGMEM = "HU3=";
//Can Temp an Humidity4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanTemp4[]       PROGMEM = "can/pubtemp4";
const char PubTopicCanHumidity4[]   PROGMEM = "can/pubhumidity4";
const char CanTempSensorName4[]     PROGMEM = "CanTemp4";
const char CanTempSensorId4[]       PROGMEM = "00xx";
const char CanInCommandTemp4[]      PROGMEM = "ET4=";
const char CanInCommandHumidity4[]  PROGMEM = "EH4=";
//Can Temp an Humidity5/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanTemp5[]       PROGMEM = "can/pubtemp5";
const char PubTopicCanHumidity5[]   PROGMEM = "can/pubhumidity5";
const char CanTempSensorName5[]     PROGMEM = "CanTemp5";
const char CanTempSensorId5[]       PROGMEM = "00xx";
const char CanInCommandTemp5[]      PROGMEM = "ET5=";
const char CanInCommandHumidity5[]  PROGMEM = "EH5=";
//Can Temp an Humidity6/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanTemp6[]       PROGMEM = "can/pubtemp6";
const char PubTopicCanHumidity6[]   PROGMEM = "can/pubhumidity6";
const char CanTempSensorName6[]     PROGMEM = "CanTemp6";
const char CanTempSensorId6[]       PROGMEM = "00xx";
const char CanInCommandTemp6[]      PROGMEM = "ET6=";
const char CanInCommandHumidity6[]  PROGMEM = "EH6=";
//Can Temp an Humidity7/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanTemp7[]       PROGMEM = "can/pubtemp7";
const char PubTopicCanHumidity7[]   PROGMEM = "can/pubhumidity7";
const char CanTempSensorName7[]     PROGMEM = "CanTemp7";
const char CanTempSensorId7[]       PROGMEM = "00xx";
const char CanInCommandTemp7[]      PROGMEM = "ET7=";
const char CanInCommandHumidity7[]  PROGMEM = "EH7=";
//Can Temp an Humidity8/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanTemp8[]       PROGMEM = "can/pubtemp8";
const char PubTopicCanHumidity8[]   PROGMEM = "can/pubhumidity8";
const char CanTempSensorName8[]     PROGMEM = "CanTemp8";
const char CanTempSensorId8[]       PROGMEM = "00xx";
const char CanInCommandTemp8[]      PROGMEM = "ET8=";
const char CanInCommandHumidity8[]  PROGMEM = "EH8=";
//Can Temp an Humidity9/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanTemp9[]       PROGMEM = "can/pubtemp9";
const char PubTopicCanHumidity9[]   PROGMEM = "can/pubhumidity9";
const char CanTempSensorName9[]     PROGMEM = "CanTemp9";
const char CanTempSensorId9[]       PROGMEM = "00xx";
const char CanInCommandTemp9[]      PROGMEM = "ET9=";
const char CanInCommandHumidity9[]  PROGMEM = "EH9=";
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************************************************************************************************************************************************************************************/
//*************************************************************************************************CAN EXPANDER HVAC SETUP*****************************************************************************/
//*****************************************************************************************************************************************************************************************************/
const int CANHVACS = 8;// This can be lower if you dont use 8 heater you should write the number os your setup bacause the software will run faster
const char CanHvacPrefix[] = "EH"; //This is needed for faster can response.
//*CanHVAC1*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanHvacTemp1 [] PROGMEM  = "can/pubhvactemp1";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicCanHvacTemp1 [] PROGMEM  = "can/subhvactemp1";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicCanHvacMode1 [] PROGMEM  = "can/pubhvacmode1";   //Here you can write your pubtopic for the actual mode 
const char SubTopicCanHvacMode1 [] PROGMEM  = "can/subhvacmode1";   //Here you can write your subtopic for the actual mode
const char CanHvacTemp1[]          PROGMEM  = "EHT1=";              //Can command
const char CanHvacMode1[]          PROGMEM  = "EHM1=";              //Can command
//*CanHVAC2*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanHvacTemp2 [] PROGMEM  = "can/pubhvactemp2";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicCanHvacTemp2 [] PROGMEM  = "can/subhvactemp2";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicCanHvacMode2 [] PROGMEM  = "can/pubhvacmode2";   //Here you can write your pubtopic for the actual mode 
const char SubTopicCanHvacMode2 [] PROGMEM  = "can/subhvacmode2";   //Here you can write your subtopic for the actual mode
const char CanHvacTemp2[]          PROGMEM  = "EHT2=";              //Can command
const char CanHvacMode2[]          PROGMEM  = "EHM2=";              //Can command
//*CanHVAC3*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanHvacTemp3 [] PROGMEM  = "can/pubhvactemp3";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicCanHvacTemp3 [] PROGMEM  = "can/subhvactemp3";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicCanHvacMode3 [] PROGMEM  = "can/pubhvacmode3";   //Here you can write your pubtopic for the actual mode 
const char SubTopicCanHvacMode3 [] PROGMEM  = "can/subhvacmode3";   //Here you can write your subtopic for the actual mode
const char CanHvacTemp3[]          PROGMEM  = "EHT3=";              //Can command
const char CanHvacMode3[]          PROGMEM  = "EHM3=";              //Can command
//*CanHVAC4*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanHvacTemp4 [] PROGMEM  = "can/pubhvactemp4";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicCanHvacTemp4 [] PROGMEM  = "can/subhvactemp4";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicCanHvacMode4 [] PROGMEM  = "can/pubhvacmode4";   //Here you can write your pubtopic for the actual mode 
const char SubTopicCanHvacMode4 [] PROGMEM  = "can/subhvacmode4";   //Here you can write your subtopic for the actual mode
const char CanHvacTemp4[]          PROGMEM  = "EHT4=";              //Can command
const char CanHvacMode4[]          PROGMEM  = "EHM4=";              //Can command
//*CanHVAC5*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanHvacTemp5 [] PROGMEM  = "can/pubhvactemp5";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicCanHvacTemp5 [] PROGMEM  = "can/subhvactemp5";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicCanHvacMode5 [] PROGMEM  = "can/pubhvacmode5";   //Here you can write your pubtopic for the actual mode 
const char SubTopicCanHvacMode5 [] PROGMEM  = "can/subhvacmode5";   //Here you can write your subtopic for the actual mode
const char CanHvacTemp5[]          PROGMEM  = "EHT5=";              //Can command
const char CanHvacMode5[]          PROGMEM  = "EHM5=";              //Can command
//*CanHVAC6*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanHvacTemp6 [] PROGMEM  = "can/pubhvactemp6";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicCanHvacTemp6 [] PROGMEM  = "can/subhvactemp6";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicCanHvacMode6 [] PROGMEM  = "can/pubhvacmode6";   //Here you can write your pubtopic for the actual mode 
const char SubTopicCanHvacMode6 [] PROGMEM  = "can/subhvacmode6";   //Here you can write your subtopic for the actual mode
const char CanHvacTemp6[]          PROGMEM  = "EHT6=";              //Can command
const char CanHvacMode6[]          PROGMEM  = "EHM6=";              //Can command
//*CanHVAC7*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanHvacTemp7 [] PROGMEM  = "can/pubhvactemp7";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicCanHvacTemp7 [] PROGMEM  = "can/subhvactemp7";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicCanHvacMode7 [] PROGMEM  = "can/pubhvacmode7";   //Here you can write your pubtopic for the actual mode 
const char SubTopicCanHvacMode7 [] PROGMEM  = "can/subhvacmode7";   //Here you can write your subtopic for the actual mode
const char CanHvacTemp7[]          PROGMEM  = "EHT7=";              //Can command
const char CanHvacMode7[]          PROGMEM  = "EHM7=";              //Can command
//*CanHVAC8*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char PubTopicCanHvacTemp8 [] PROGMEM  = "can/pubhvactemp8";   //Here you need to write your pubtopic to send your wanted temperature
const char SubTopicCanHvacTemp8 [] PROGMEM  = "can/subhvactemp8";   //Here you need to write your Subtopic to get your wanted temperature
const char PubTopicCanHvacMode8 [] PROGMEM  = "can/pubhvacmode8";   //Here you can write your pubtopic for the actual mode 
const char SubTopicCanHvacMode8 [] PROGMEM  = "can/subhvacmode8";   //Here you can write your subtopic for the actual mode
const char CanHvacTemp8[]          PROGMEM  = "EHT8=";              //Can command
const char CanHvacMode8[]          PROGMEM  = "EHM8=";              //Can command

//Hvac Variables and some experienced setup

const int usedHEATERS = 8;
const int Heatofset =  1;//That means the temp valves wont start until the temperature does not fall from the offset temperature. That means required (temperature - offset temperature)
const int HeatTimeOut = 120000;//You can set up in this place to how many times needs to be passed between to heating cycle this is tetted up to 2 min basedon miliseconds
const int RealayOnState = 0;//This is gives 0V when output needs to be on. This is works well with chinese relay boards
const int RealayOffState = 1;//This is gives 5V when output needs to be off. This is works well with chinese relay boards

int HvacTemp[HVACS];//The Heating system will want to reach this temperatures
int HvacMode[HVACS];
int HvacPower[HVACS];
int HeatingState[usedHEATERS];//This value stores the last state of the heating true:active heating------false:inactive heating
int deviceId;
int heatPumpState;
int boilerState;
int BoilerAndHeatPumpState;

unsigned long ElapsedTime;


const char *const PubTopicHvacTemp[] PROGMEM = {
  PubTopicHvacTemp1,
  PubTopicHvacTemp2,
  PubTopicHvacTemp3,
  PubTopicHvacTemp4,
  PubTopicHvacTemp5,
  PubTopicHvacTemp6,
  PubTopicHvacTemp7,
  PubTopicHvacTemp8,
  PubTopicHvacTemp9
};

const char *const SubTopicHvacTemp[] PROGMEM = {
  SubTopicHvacTemp1,
  SubTopicHvacTemp2,
  SubTopicHvacTemp3,
  SubTopicHvacTemp4,
  SubTopicHvacTemp5,
  SubTopicHvacTemp6,
  SubTopicHvacTemp7,
  SubTopicHvacTemp8,
  SubTopicHvacTemp9
};

const char *const  SubTopicHvacMode[] PROGMEM = {
   SubTopicHvacMode1,
   SubTopicHvacMode2,
   SubTopicHvacMode3,
   SubTopicHvacMode4,
   SubTopicHvacMode5,
   SubTopicHvacMode6,
   SubTopicHvacMode7,
   SubTopicHvacMode8,
   SubTopicHvacMode9
};

const char *const  PubTopicHvacMode[] PROGMEM = {
   PubTopicHvacMode1,
   PubTopicHvacMode2,
   PubTopicHvacMode3,
   PubTopicHvacMode4,
   PubTopicHvacMode5,
   PubTopicHvacMode6,
   PubTopicHvacMode7,
   PubTopicHvacMode8,
   PubTopicHvacMode9
};

const char *const  HvacName[] PROGMEM = {
  HvacName1,
  HvacName2,
  HvacName3,
  HvacName4,
  HvacName5,
  HvacName6,
  HvacName7,
  HvacName8,
  HvacName9
};

const char *const  HvacId[] PROGMEM = {
  HvacId1,
  HvacId2,
  HvacId3,
  HvacId4,
  HvacId5,
  HvacId6,
  HvacId7,
  HvacId8,
  HvacId9,
};

const char *const  HvacRoom[] PROGMEM = {
  HvacRoom1,
  HvacRoom2,
  HvacRoom3,
  HvacRoom4,
  HvacRoom5,
  HvacRoom6,
  HvacRoom7,
  HvacRoom8,
  HvacRoom9
};

const int HvacOutput[] = {
  HvacOutput1,
  HvacOutput2,
  HvacOutput3,
  HvacOutput4,
  HvacOutput5,
  HvacOutput6,
  HvacOutput7,
  HvacOutput8,
  HvacOutput9
};

const int HvacTempsensor[] = {
  HvacTempsensor1,
  HvacTempsensor2,
  HvacTempsensor3,
  HvacTempsensor4,
  HvacTempsensor5,
  HvacTempsensor6,
  HvacTempsensor7,
  HvacTempsensor8,
  HvacTempsensor9
};

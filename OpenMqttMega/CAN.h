#define CanModules 1
#define MessageLenght 8
#define CanOutputs 9
#define CanInputs 9
#define CanTempSensors 9
#define CanHumiditySensors 9
#define CanHvacs 4
#define CanDataBuffer 100

int BeQuietSended = 0;
int SendData = 0;
int CanStatesOut[CanOutputs];
int CanStatesIn[CanInputs];
int CanHvacModeState[CanHvacs];
int CanHvacTempState[CanHvacs];
int CanStatesTemp[CanTempSensors];
int CanStatesHumidity[CanHumiditySensors];
int recivedRawData[MessageLenght][CanDataBuffer];

boolean DataAsked = false;
boolean DataArriwed = false;
boolean CanOutputChanged = false;
boolean CanInputChanged = false;
boolean CanHvacChanged = false;
boolean ServerOutputChanged = false;
boolean ServerInputChanged = false;
boolean ServerHvacChanged = false;
boolean ServerTemperatureAsked = false;
boolean ServerHumidityAsked = false;

unsigned long BeQuietMillis = 0;
unsigned long SendDataMillis = 0;
unsigned long CanTimeOut = 0;

char CanData[MessageLenght] = {0, 0, 0, 0, 0, 0, 0, 0};
char recived[MessageLenght];

struct can_frame canMsg;

MCP2515 mcp2515(MCPSS);

const char *const SubTopicCanOut[] PROGMEM = {
  SubTopicCanOut1,
  SubTopicCanOut2,
  SubTopicCanOut3,
  SubTopicCanOut4,
  SubTopicCanOut5,
  SubTopicCanOut6,
  SubTopicCanOut7,
  SubTopicCanOut8,
  SubTopicCanOut9
};

const char *const PubTopicCanOut[] PROGMEM = {
  PubTopicCanOut1,
  PubTopicCanOut2,
  PubTopicCanOut3,
  PubTopicCanOut4,
  PubTopicCanOut5,
  PubTopicCanOut6,
  PubTopicCanOut7,
  PubTopicCanOut8,
  PubTopicCanOut9
};

const char *const CanOutCommand[] PROGMEM = {
  CanOutCommand1,
  CanOutCommand2,
  CanOutCommand3,
  CanOutCommand4,
  CanOutCommand5,
  CanOutCommand6,
  CanOutCommand7,
  CanOutCommand8,
  CanOutCommand9
};

const char *const SubTopicCanIn[] PROGMEM = {
  SubTopicCanIn1,
  SubTopicCanIn2,
  SubTopicCanIn3,
  SubTopicCanIn4,
  SubTopicCanIn5,
  SubTopicCanIn6,
  SubTopicCanIn7,
  SubTopicCanIn8,
  SubTopicCanIn9
};

const char *const PubTopicCanIn[] PROGMEM = {
  PubTopicCanIn1,
  PubTopicCanIn2,
  PubTopicCanIn3,
  PubTopicCanIn4,
  PubTopicCanIn5,
  PubTopicCanIn6,
  PubTopicCanIn7,
  PubTopicCanIn8,
  PubTopicCanIn9
};

const char *const CanInCommand[] PROGMEM = {
  CanInCommand1,
  CanInCommand2,
  CanInCommand3,
  CanInCommand4,
  CanInCommand5,
  CanInCommand6,
  CanInCommand7,
  CanInCommand8,
  CanInCommand9
};

const char *const PubTopicCanTemp[] PROGMEM = {
  PubTopicCanTemp1,
  PubTopicCanTemp2,
  PubTopicCanTemp3,
  PubTopicCanTemp4,
  PubTopicCanTemp5,
  PubTopicCanTemp6,
  PubTopicCanTemp7,
  PubTopicCanTemp8,
  PubTopicCanTemp9
};

const char *const PubTopicCanHumidity[] PROGMEM = {
  PubTopicCanHumidity1,
  PubTopicCanHumidity2,
  PubTopicCanHumidity3,
  PubTopicCanHumidity4,
  PubTopicCanHumidity5,
  PubTopicCanHumidity6,
  PubTopicCanHumidity7,
  PubTopicCanHumidity8,
  PubTopicCanHumidity9
};

const char *const CanCommandTemp[] PROGMEM = {
  CanInCommandTemp1,
  CanInCommandTemp2,
  CanInCommandTemp3,
  CanInCommandTemp4,
  CanInCommandTemp5,
  CanInCommandTemp6,
  CanInCommandTemp7,
  CanInCommandTemp8,
  CanInCommandTemp9
};

const char *const CanCommandHumidity[] PROGMEM = {
  CanInCommandHumidity1,
  CanInCommandHumidity2,
  CanInCommandHumidity3,
  CanInCommandHumidity4,
  CanInCommandHumidity5,
  CanInCommandHumidity6,
  CanInCommandHumidity7,
  CanInCommandHumidity8,
  CanInCommandHumidity9
};

const char *const CanTempSensorName[] PROGMEM = {
  CanTempSensorName1,
  CanTempSensorName2,
  CanTempSensorName3,
  CanTempSensorName4,
  CanTempSensorName5,
  CanTempSensorName6,
  CanTempSensorName7,
  CanTempSensorName8,
  CanTempSensorName9
};

const char *const CanTempSensorId[] PROGMEM = {
  CanTempSensorId1,
  CanTempSensorId2,
  CanTempSensorId3,
  CanTempSensorId4,
  CanTempSensorId5,
  CanTempSensorId6,
  CanTempSensorId7,
  CanTempSensorId8,
  CanTempSensorId9
};

//ServerOut=..........
const char  CanServerOut1[] PROGMEM  = "SO1=";
const char  CanServerOut2[] PROGMEM  = "SO2=";
const char  CanServerOut3[] PROGMEM  = "SO3=";
const char  CanServerOut4[] PROGMEM  = "SO4=";
const char  CanServerOut5[] PROGMEM  = "SO5=";
const char  CanServerOut6[] PROGMEM  = "SO6=";
const char  CanServerOut7[] PROGMEM  = "SO7=";
const char  CanServerOut8[] PROGMEM  = "SO8=";
const char  CanServerOut9[] PROGMEM  = "SO9=";
const char  CanServerOut10[] PROGMEM  = "SO10=";
const char  CanServerOut11[] PROGMEM  = "SO11=";
const char  CanServerOut12[] PROGMEM  = "SO12=";
const char  CanServerOut13[] PROGMEM  = "SO13=";
const char  CanServerOut14[] PROGMEM  = "SO14=";
const char  CanServerOut15[] PROGMEM  = "SO15=";
const char  CanServerOut16[] PROGMEM  = "SO16=";
const char  CanServerOut17[] PROGMEM  = "SO17=";
const char  CanServerOut18[] PROGMEM  = "SO18=";
const char  CanServerOut19[] PROGMEM  = "SO19=";
const char  CanServerOut20[] PROGMEM  = "SO20=";
const char  CanServerOut21[] PROGMEM  = "SO21=";
const char  CanServerOut22[] PROGMEM  = "SO22=";
const char  CanServerOut23[] PROGMEM  = "SO23=";
const char  CanServerOut24[] PROGMEM  = "SO24=";
const char  CanServerOut25[] PROGMEM  = "SO25=";
const char  CanServerOut26[] PROGMEM  = "SO26=";
const char  CanServerOut27[] PROGMEM  = "SO27=";
const char  CanServerOut28[] PROGMEM  = "SO28=";
const char  CanServerOut29[] PROGMEM  = "SO29=";
const char  CanServerOut30[] PROGMEM  = "SO30=";
const char  CanServerOut31[] PROGMEM  = "SO31=";
const char  CanServerOut32[] PROGMEM  = "SO32=";
const char  CanServerOut33[] PROGMEM  = "SO33=";
const char  CanServerOut34[] PROGMEM  = "SO34=";
const char  CanServerOut35[] PROGMEM  = "SO35=";
const char  CanServerOut36[] PROGMEM  = "SO36=";
const char  CanServerOut37[] PROGMEM  = "SO37=";
const char  CanServerOut38[] PROGMEM  = "SO38=";
const char  CanServerOut39[] PROGMEM  = "SO39=";
const char  CanServerOut40[] PROGMEM  = "SO40=";
const char  CanServerOut41[] PROGMEM  = "SO41=";
const char  CanServerOut42[] PROGMEM  = "SO42=";
const char  CanServerOut43[] PROGMEM  = "SO43=";
const char  CanServerOut44[] PROGMEM  = "SO44=";
const char  CanServerOut45[] PROGMEM  = "SO45=";
const char  CanServerOut46[] PROGMEM  = "SO46=";
const char  CanServerOut47[] PROGMEM  = "SO47=";
const char  CanServerOut48[] PROGMEM  = "SO48=";
const char  CanServerOut49[] PROGMEM  = "SO49=";
const char  CanServerOut50[] PROGMEM  = "SO50=";
const char  CanServerOut51[] PROGMEM  = "SO51=";
const char  CanServerOut52[] PROGMEM  = "SO52=";
const char  CanServerOut53[] PROGMEM  = "SO53=";
const char  CanServerOut54[] PROGMEM  = "SO54=";
const char  CanServerOut55[] PROGMEM  = "SO55=";
const char  CanServerOut56[] PROGMEM  = "SO56=";
const char  CanServerOut57[] PROGMEM  = "SO57=";
const char  CanServerOut58[] PROGMEM  = "SO58=";
const char  CanServerOut59[] PROGMEM  = "SO59=";
const char  CanServerOut60[] PROGMEM  = "SO60=";
const char  CanServerOut61[] PROGMEM  = "SO61=";
const char  CanServerOut62[] PROGMEM  = "SO62=";
const char  CanServerOut63[] PROGMEM  = "SO63=";
const char  CanServerOut64[] PROGMEM  = "SO64=";
const char  CanServerOut65[] PROGMEM  = "SO65=";
const char  CanServerOut66[] PROGMEM  = "SO66=";
const char  CanServerOut67[] PROGMEM  = "SO67=";
const char  CanServerOut68[] PROGMEM  = "SO68=";
const char  CanServerOut69[] PROGMEM  = "SO69=";
const char  CanServerOut70[] PROGMEM  = "SO70=";
const char  CanServerOut71[] PROGMEM  = "SO71=";
const char  CanServerOut72[] PROGMEM  = "SO72=";
const char  CanServerOut73[] PROGMEM  = "SO73=";
const char  CanServerOut74[] PROGMEM  = "SO74=";
const char  CanServerOut75[] PROGMEM  = "SO75=";
const char  CanServerOut76[] PROGMEM  = "SO76=";
const char  CanServerOut77[] PROGMEM  = "SO77=";
const char  CanServerOut78[] PROGMEM  = "SO78=";
const char  CanServerOut79[] PROGMEM  = "SO79=";
const char  CanServerOut80[] PROGMEM  = "SO80=";
const char  CanServerOut81[] PROGMEM  = "SO81=";
const char  CanServerOut82[] PROGMEM  = "SO82=";
const char  CanServerOut83[] PROGMEM  = "SO83=";
const char  CanServerOut84[] PROGMEM  = "SO84=";
const char  CanServerOut85[] PROGMEM  = "SO85=";
const char  CanServerOut86[] PROGMEM  = "SO86=";
const char  CanServerOut87[] PROGMEM  = "SO87=";
const char  CanServerOut88[] PROGMEM  = "SO88=";
const char  CanServerOut89[] PROGMEM  = "SO89=";
const char  CanServerOut90[] PROGMEM  = "SO90=";
const char  CanServerOut91[] PROGMEM  = "SO91=";
const char  CanServerOut92[] PROGMEM  = "SO92=";
const char  CanServerOut93[] PROGMEM  = "SO93=";
const char  CanServerOut94[] PROGMEM  = "SO94=";
const char  CanServerOut95[] PROGMEM  = "SO95=";
const char  CanServerOut96[] PROGMEM  = "SO96=";
const char  CanServerOut97[] PROGMEM  = "SO97=";
const char  CanServerOut98[] PROGMEM  = "SO98=";
const char  CanServerOut99[] PROGMEM  = "SO99=";
const char  CanServerOut100[] PROGMEM  = "SO100=";


const char *const CanServerOut[] PROGMEM = {
  CanServerOut1,
  CanServerOut2,
  CanServerOut3,
  CanServerOut4,
  CanServerOut5,
  CanServerOut6,
  CanServerOut7,
  CanServerOut8,
  CanServerOut9,
  CanServerOut10,
  CanServerOut11,
  CanServerOut12,
  CanServerOut13,
  CanServerOut14,
  CanServerOut15,
  CanServerOut16,
  CanServerOut17,
  CanServerOut18,
  CanServerOut19,
  CanServerOut20,
  CanServerOut21,
  CanServerOut22,
  CanServerOut23,
  CanServerOut24,
  CanServerOut25,
  CanServerOut26,
  CanServerOut27,
  CanServerOut28,
  CanServerOut29,
  CanServerOut30,
  CanServerOut31,
  CanServerOut32,
  CanServerOut33,
  CanServerOut34,
  CanServerOut35,
  CanServerOut36,
  CanServerOut37,
  CanServerOut38,
  CanServerOut39,
  CanServerOut40,
  CanServerOut41,
  CanServerOut42,
  CanServerOut43,
  CanServerOut44,
  CanServerOut45,
  CanServerOut46,
  CanServerOut47,
  CanServerOut48,
  CanServerOut49,
  CanServerOut50,
  CanServerOut51,
  CanServerOut52,
  CanServerOut53,
  CanServerOut54,
  CanServerOut55,
  CanServerOut56,
  CanServerOut57,
  CanServerOut58,
  CanServerOut59,
  CanServerOut60,
  CanServerOut61,
  CanServerOut62,
  CanServerOut63,
  CanServerOut64,
  CanServerOut65,
  CanServerOut66,
  CanServerOut67,
  CanServerOut68,
  CanServerOut69,
  CanServerOut70,
  CanServerOut71,
  CanServerOut72,
  CanServerOut73,
  CanServerOut74,
  CanServerOut75,
  CanServerOut76,
  CanServerOut77,
  CanServerOut78,
  CanServerOut79,
  CanServerOut80,
  CanServerOut81,
  CanServerOut82,
  CanServerOut83,
  CanServerOut84,
  CanServerOut85,
  CanServerOut86,
  CanServerOut87,
  CanServerOut88,
  CanServerOut89,
  CanServerOut90,
  CanServerOut91,
  CanServerOut92,
  CanServerOut93,
  CanServerOut94,
  CanServerOut95,
  CanServerOut96,
  CanServerOut97,
  CanServerOut98,
  CanServerOut99,
  CanServerOut100
};
//ServerIn=........//ServerOut=..........
const char  CanServerIn1[] PROGMEM  = "SI1=";
const char  CanServerIn2[] PROGMEM  = "SI2=";
const char  CanServerIn3[] PROGMEM  = "SI3=";
const char  CanServerIn4[] PROGMEM  = "SI4=";
const char  CanServerIn5[] PROGMEM  = "SI5=";
const char  CanServerIn6[] PROGMEM  = "SI6=";
const char  CanServerIn7[] PROGMEM  = "SI7=";
const char  CanServerIn8[] PROGMEM  = "SI8=";
const char  CanServerIn9[] PROGMEM  = "SI9=";
const char  CanServerIn10[] PROGMEM  = "SI10=";
const char  CanServerIn11[] PROGMEM  = "SI11=";
const char  CanServerIn12[] PROGMEM  = "SI12=";
const char  CanServerIn13[] PROGMEM  = "SI13=";
const char  CanServerIn14[] PROGMEM  = "SI14=";
const char  CanServerIn15[] PROGMEM  = "SI15=";
const char  CanServerIn16[] PROGMEM  = "SI16=";
const char  CanServerIn17[] PROGMEM  = "SI17=";
const char  CanServerIn18[] PROGMEM  = "SI18=";
const char  CanServerIn19[] PROGMEM  = "SI19=";
const char  CanServerIn20[] PROGMEM  = "SI20=";
const char  CanServerIn21[] PROGMEM  = "SI21=";
const char  CanServerIn22[] PROGMEM  = "SI22=";
const char  CanServerIn23[] PROGMEM  = "SI23=";
const char  CanServerIn24[] PROGMEM  = "SI24=";
const char  CanServerIn25[] PROGMEM  = "SI25=";
const char  CanServerIn26[] PROGMEM  = "SI26=";
const char  CanServerIn27[] PROGMEM  = "SI27=";
const char  CanServerIn28[] PROGMEM  = "SI28=";
const char  CanServerIn29[] PROGMEM  = "SI29=";
const char  CanServerIn30[] PROGMEM  = "SI30=";
const char  CanServerIn31[] PROGMEM  = "SI31=";
const char  CanServerIn32[] PROGMEM  = "SI32=";
const char  CanServerIn33[] PROGMEM  = "SI33=";
const char  CanServerIn34[] PROGMEM  = "SI34=";
const char  CanServerIn35[] PROGMEM  = "SI35=";
const char  CanServerIn36[] PROGMEM  = "SI36=";
const char  CanServerIn37[] PROGMEM  = "SI37=";
const char  CanServerIn38[] PROGMEM  = "SI38=";
const char  CanServerIn39[] PROGMEM  = "SI39=";
const char  CanServerIn40[] PROGMEM  = "SI40=";
const char  CanServerIn41[] PROGMEM  = "SI41=";
const char  CanServerIn42[] PROGMEM  = "SI42=";
const char  CanServerIn43[] PROGMEM  = "SI43=";
const char  CanServerIn44[] PROGMEM  = "SI44=";
const char  CanServerIn45[] PROGMEM  = "SI45=";
const char  CanServerIn46[] PROGMEM  = "SI46=";
const char  CanServerIn47[] PROGMEM  = "SI47=";
const char  CanServerIn48[] PROGMEM  = "SI48=";
const char  CanServerIn49[] PROGMEM  = "SI49=";
const char  CanServerIn50[] PROGMEM  = "SI50=";
const char  CanServerIn51[] PROGMEM  = "SI51=";
const char  CanServerIn52[] PROGMEM  = "SI52=";
const char  CanServerIn53[] PROGMEM  = "SI53=";
const char  CanServerIn54[] PROGMEM  = "SI54=";
const char  CanServerIn55[] PROGMEM  = "SI55=";
const char  CanServerIn56[] PROGMEM  = "SI56=";
const char  CanServerIn57[] PROGMEM  = "SI57=";
const char  CanServerIn58[] PROGMEM  = "SI58=";
const char  CanServerIn59[] PROGMEM  = "SI59=";
const char  CanServerIn60[] PROGMEM  = "SI60=";
const char  CanServerIn61[] PROGMEM  = "SI61=";
const char  CanServerIn62[] PROGMEM  = "SI62=";
const char  CanServerIn63[] PROGMEM  = "SI63=";
const char  CanServerIn64[] PROGMEM  = "SI64=";
const char  CanServerIn65[] PROGMEM  = "SI65=";
const char  CanServerIn66[] PROGMEM  = "SI66=";
const char  CanServerIn67[] PROGMEM  = "SI67=";
const char  CanServerIn68[] PROGMEM  = "SI68=";
const char  CanServerIn69[] PROGMEM  = "SI69=";
const char  CanServerIn70[] PROGMEM  = "SI70=";
const char  CanServerIn71[] PROGMEM  = "SI71=";
const char  CanServerIn72[] PROGMEM  = "SI72=";
const char  CanServerIn73[] PROGMEM  = "SI73=";
const char  CanServerIn74[] PROGMEM  = "SI74=";
const char  CanServerIn75[] PROGMEM  = "SI75=";
const char  CanServerIn76[] PROGMEM  = "SI76=";
const char  CanServerIn77[] PROGMEM  = "SI77=";
const char  CanServerIn78[] PROGMEM  = "SI78=";
const char  CanServerIn79[] PROGMEM  = "SI79=";
const char  CanServerIn80[] PROGMEM  = "SI80=";
const char  CanServerIn81[] PROGMEM  = "SI81=";
const char  CanServerIn82[] PROGMEM  = "SI82=";
const char  CanServerIn83[] PROGMEM  = "SI83=";
const char  CanServerIn84[] PROGMEM  = "SI84=";
const char  CanServerIn85[] PROGMEM  = "SI85=";
const char  CanServerIn86[] PROGMEM  = "SI86=";
const char  CanServerIn87[] PROGMEM  = "SI87=";
const char  CanServerIn88[] PROGMEM  = "SI88=";
const char  CanServerIn89[] PROGMEM  = "SI89=";
const char  CanServerIn90[] PROGMEM  = "SI90=";
const char  CanServerIn91[] PROGMEM  = "SI91=";
const char  CanServerIn92[] PROGMEM  = "SI92=";
const char  CanServerIn93[] PROGMEM  = "SI93=";
const char  CanServerIn94[] PROGMEM  = "SI94=";
const char  CanServerIn95[] PROGMEM  = "SI95=";
const char  CanServerIn96[] PROGMEM  = "SI96=";
const char  CanServerIn97[] PROGMEM  = "SI97=";
const char  CanServerIn98[] PROGMEM  = "SI98=";
const char  CanServerIn99[] PROGMEM  = "SI99=";
const char  CanServerIn100[] PROGMEM  = "SO100=";

const char *const CanServerIn[] PROGMEM = {
  CanServerIn1,
  CanServerIn2,
  CanServerIn3,
  CanServerIn4,
  CanServerIn5,
  CanServerIn6,
  CanServerIn7,
  CanServerIn8,
  CanServerIn9,
  CanServerIn10,
  CanServerIn11,
  CanServerIn12,
  CanServerIn13,
  CanServerIn14,
  CanServerIn15,
  CanServerIn16,
  CanServerIn17,
  CanServerIn18,
  CanServerIn19,
  CanServerIn20,
  CanServerIn21,
  CanServerIn22,
  CanServerIn23,
  CanServerIn24,
  CanServerIn25,
  CanServerIn26,
  CanServerIn27,
  CanServerIn28,
  CanServerIn29,
  CanServerIn30,
  CanServerIn31,
  CanServerIn32,
  CanServerIn33,
  CanServerIn34,
  CanServerIn35,
  CanServerIn36,
  CanServerIn37,
  CanServerIn38,
  CanServerIn39,
  CanServerIn40,
  CanServerIn41,
  CanServerIn42,
  CanServerIn43,
  CanServerIn44,
  CanServerIn45,
  CanServerIn46,
  CanServerIn47,
  CanServerIn48,
  CanServerIn49,
  CanServerIn50,
  CanServerIn51,
  CanServerIn52,
  CanServerIn53,
  CanServerIn54,
  CanServerIn55,
  CanServerIn56,
  CanServerIn57,
  CanServerIn58,
  CanServerIn59,
  CanServerIn60,
  CanServerIn61,
  CanServerIn62,
  CanServerIn63,
  CanServerIn64,
  CanServerIn65,
  CanServerIn66,
  CanServerIn67,
  CanServerIn68,
  CanServerIn69,
  CanServerIn70,
  CanServerIn71,
  CanServerIn72,
  CanServerIn73,
  CanServerIn74,
  CanServerIn75,
  CanServerIn76,
  CanServerIn77,
  CanServerIn78,
  CanServerIn79,
  CanServerIn80,
  CanServerIn81,
  CanServerIn82,
  CanServerIn83,
  CanServerIn84,
  CanServerIn85,
  CanServerIn86,
  CanServerIn87,
  CanServerIn88,
  CanServerIn89,
  CanServerIn90,
  CanServerIn91,
  CanServerIn92,
  CanServerIn93,
  CanServerIn94,
  CanServerIn95,
  CanServerIn96,
  CanServerIn97,
  CanServerIn98,
  CanServerIn99,
  CanServerIn100
};
const char  CanServerHvacTemp1[] PROGMEM  = "SHT1=";
const char  CanServerHvacTemp2[] PROGMEM  = "SHT2=";
const char  CanServerHvacTemp3[] PROGMEM  = "SHT3=";
const char  CanServerHvacTemp4[] PROGMEM  = "SHT4=";
const char  CanServerHvacTemp5[] PROGMEM  = "SHT5=";
const char  CanServerHvacTemp6[] PROGMEM  = "SHT6=";
const char  CanServerHvacTemp7[] PROGMEM  = "SHT7=";
const char  CanServerHvacTemp8[] PROGMEM  = "SHT8=";
const char  CanServerHvacTemp9[] PROGMEM  = "SHT9=";
const char  CanServerHvacTemp10[] PROGMEM  = "SHT10=";
const char  CanServerHvacTemp11[] PROGMEM  = "SHT11=";
const char  CanServerHvacTemp12[] PROGMEM  = "SHT12=";
const char  CanServerHvacTemp13[] PROGMEM  = "SHT13=";
const char  CanServerHvacTemp14[] PROGMEM  = "SHT14=";
const char  CanServerHvacTemp15[] PROGMEM  = "SHT15=";
const char  CanServerHvacTemp16[] PROGMEM  = "SHT16=";
const char  CanServerHvacTemp17[] PROGMEM  = "SHT17=";
const char  CanServerHvacTemp18[] PROGMEM  = "SHT18=";
const char  CanServerHvacTemp19[] PROGMEM  = "SHT19=";
const char  CanServerHvacTemp20[] PROGMEM  = "SHT20=";
//ServerHvacTemp=...
const char *const CanServerHvacTemp[] PROGMEM = {
  CanServerHvacTemp1,
  CanServerHvacTemp2,
  CanServerHvacTemp3,
  CanServerHvacTemp4,
  CanServerHvacTemp5,
  CanServerHvacTemp6,
  CanServerHvacTemp7,
  CanServerHvacTemp8,
  CanServerHvacTemp9,
  CanServerHvacTemp10,
  CanServerHvacTemp11,
  CanServerHvacTemp12,
  CanServerHvacTemp13,
  CanServerHvacTemp14,
  CanServerHvacTemp15,
  CanServerHvacTemp16,
  CanServerHvacTemp17,
  CanServerHvacTemp18,
  CanServerHvacTemp19,
  CanServerHvacTemp20
};

const char  CanServerHvacMode1[] PROGMEM  = "SHM1=";
const char  CanServerHvacMode2[] PROGMEM  = "SHM2=";
const char  CanServerHvacMode3[] PROGMEM  = "SHM3=";
const char  CanServerHvacMode4[] PROGMEM  = "SHM4=";
const char  CanServerHvacMode5[] PROGMEM  = "SHM5=";
const char  CanServerHvacMode6[] PROGMEM  = "SHM6=";
const char  CanServerHvacMode7[] PROGMEM  = "SHM7=";
const char  CanServerHvacMode8[] PROGMEM  = "SHM8=";
const char  CanServerHvacMode9[] PROGMEM  = "SHM9=";
const char  CanServerHvacMode10[] PROGMEM  = "SHM10=";
const char  CanServerHvacMode11[] PROGMEM  = "SHM11=";
const char  CanServerHvacMode12[] PROGMEM  = "SHM12=";
const char  CanServerHvacMode13[] PROGMEM  = "SHM13=";
const char  CanServerHvacMode14[] PROGMEM  = "SHM14=";
const char  CanServerHvacMode15[] PROGMEM  = "SHM15=";
const char  CanServerHvacMode16[] PROGMEM  = "SHM16=";
const char  CanServerHvacMode17[] PROGMEM  = "SHM17=";
const char  CanServerHvacMode18[] PROGMEM  = "SHM18=";
const char  CanServerHvacMode19[] PROGMEM  = "SHM19=";
const char  CanServerHvacMode20[] PROGMEM  = "SHM20=";
//ServerHvacMode=...
const char *const CanServerHvacMode[] PROGMEM = {
  CanServerHvacMode1,
  CanServerHvacMode2,
  CanServerHvacMode3,
  CanServerHvacMode4,
  CanServerHvacMode5,
  CanServerHvacMode6,
  CanServerHvacMode7,
  CanServerHvacMode8,
  CanServerHvacMode9,
  CanServerHvacMode10,
  CanServerHvacMode11,
  CanServerHvacMode12,
  CanServerHvacMode13,
  CanServerHvacMode14,
  CanServerHvacMode15,
  CanServerHvacMode16,
  CanServerHvacMode17,
  CanServerHvacMode18,
  CanServerHvacMode19,
  CanServerHvacMode20
};
const char  CanServerTemperature1[] PROGMEM  = "ST1=";
const char  CanServerTemperature2[] PROGMEM  = "ST2=";
const char  CanServerTemperature3[] PROGMEM  = "ST3=";
const char  CanServerTemperature4[] PROGMEM  = "ST4=";
const char  CanServerTemperature5[] PROGMEM  = "ST5=";
const char  CanServerTemperature6[] PROGMEM  = "ST6=";
const char  CanServerTemperature7[] PROGMEM  = "ST7=";
const char  CanServerTemperature8[] PROGMEM  = "ST8=";
const char  CanServerTemperature9[] PROGMEM  = "ST9=";
const char  CanServerTemperature10[] PROGMEM  = "ST10=";
const char  CanServerTemperature11[] PROGMEM  = "ST11=";
const char  CanServerTemperature12[] PROGMEM  = "ST12=";
const char  CanServerTemperature13[] PROGMEM  = "ST13=";
const char  CanServerTemperature14[] PROGMEM  = "ST14=";
const char  CanServerTemperature15[] PROGMEM  = "ST15=";
const char  CanServerTemperature16[] PROGMEM  = "ST16=";
const char  CanServerTemperature17[] PROGMEM  = "ST17=";
const char  CanServerTemperature18[] PROGMEM  = "ST18=";
//ServerTemperature=...
const char *const CanServerTemperature[] PROGMEM = {
  CanServerTemperature1,
  CanServerTemperature2,
  CanServerTemperature3,
  CanServerTemperature4,
  CanServerTemperature5,
  CanServerTemperature6,
  CanServerTemperature7,
  CanServerTemperature8,
  CanServerTemperature9,
  CanServerTemperature10,
  CanServerTemperature11,
  CanServerTemperature12,
  CanServerTemperature13,
  CanServerTemperature14,
  CanServerTemperature15,
  CanServerTemperature16,
  CanServerTemperature17,
  CanServerTemperature18
};

const char  CanServerHumidity1[] PROGMEM  = "SH1=";
const char  CanServerHumidity2[] PROGMEM  = "SH2=";
const char  CanServerHumidity3[] PROGMEM  = "SH3=";
const char  CanServerHumidity4[] PROGMEM  = "SH4=";
const char  CanServerHumidity5[] PROGMEM  = "SH5=";
const char  CanServerHumidity6[] PROGMEM  = "SH6=";
const char  CanServerHumidity7[] PROGMEM  = "SH7=";
const char  CanServerHumidity8[] PROGMEM  = "SH8=";
const char  CanServerHumidity9[] PROGMEM  = "SH9=";
const char  CanServerHumidity10[] PROGMEM  = "SH10=";
const char  CanServerHumidity11[] PROGMEM  = "SH11=";
const char  CanServerHumidity12[] PROGMEM  = "SH12=";
const char  CanServerHumidity13[] PROGMEM  = "SH13=";
const char  CanServerHumidity14[] PROGMEM  = "SH14=";
const char  CanServerHumidity15[] PROGMEM  = "SH15=";
const char  CanServerHumidity16[] PROGMEM  = "SH16=";
const char  CanServerHumidity17[] PROGMEM  = "SH17=";
const char  CanServerHumidity18[] PROGMEM  = "SH18=";
//ServerHumidity=...
const char *const CanServerHumidity[] PROGMEM = {
 CanServerHumidity1,
 CanServerHumidity2,
 CanServerHumidity3,
 CanServerHumidity4,
 CanServerHumidity5,
 CanServerHumidity6,
 CanServerHumidity7,
 CanServerHumidity8,
 CanServerHumidity9,
 CanServerHumidity10,
 CanServerHumidity11,
 CanServerHumidity12,
 CanServerHumidity13,
 CanServerHumidity14,
 CanServerHumidity15,
 CanServerHumidity16,
 CanServerHumidity17,
 CanServerHumidity18
};

const char *const PubTopicCanHvacTemp[] PROGMEM = {
  PubTopicCanHvacTemp1,
  PubTopicCanHvacTemp2,
  PubTopicCanHvacTemp3,
  PubTopicCanHvacTemp4,
  PubTopicCanHvacTemp5,
  PubTopicCanHvacTemp6,
  PubTopicCanHvacTemp7,
  PubTopicCanHvacTemp8
};

const char *const SubTopicCanHvacTemp[] PROGMEM = {
  SubTopicCanHvacTemp1,
  SubTopicCanHvacTemp2,
  SubTopicCanHvacTemp3,
  SubTopicCanHvacTemp4,
  SubTopicCanHvacTemp5,
  SubTopicCanHvacTemp6,
  SubTopicCanHvacTemp7,
  SubTopicCanHvacTemp8
};

const char *const PubTopicCanHvacMode[] PROGMEM = {
  PubTopicCanHvacMode1,
  PubTopicCanHvacMode2,
  PubTopicCanHvacMode3,
  PubTopicCanHvacMode4,
  PubTopicCanHvacMode5,
  PubTopicCanHvacMode6,
  PubTopicCanHvacMode7,
  PubTopicCanHvacMode8
};

const char *const SubTopicCanHvacMode[] PROGMEM = {
  SubTopicCanHvacMode1,
  SubTopicCanHvacMode2,
  SubTopicCanHvacMode3,
  SubTopicCanHvacMode4,
  SubTopicCanHvacMode5,
  SubTopicCanHvacMode6,
  SubTopicCanHvacMode7,
  SubTopicCanHvacMode8
};

const char *const CanHvacTemp[] PROGMEM = {
  CanHvacTemp1,
  CanHvacTemp2,
  CanHvacTemp3,
  CanHvacTemp4,
  CanHvacTemp5,
  CanHvacTemp6,
  CanHvacTemp7,
  CanHvacTemp8
};

const char *const CanHvacMode[] PROGMEM = {
  CanHvacMode1,
  CanHvacMode2,
  CanHvacMode3,
  CanHvacMode4,
  CanHvacMode5,
  CanHvacMode6,
  CanHvacMode7,
  CanHvacMode8
};

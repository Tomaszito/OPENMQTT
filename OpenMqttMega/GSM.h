// PIN Number
#define PINNUMBER ""
/*Itt tudjuk bevinni az APN-t (hozzáférési pont neve):
• Havidíjas előfizetés esetén: internet.vodafone.net vagy standardnet.vodafone.net
• Feltöltőkártya esetén: vitamax.internet.vodafone.net vagy
vitamax.snet.vodafone.net
• A betárcsázási számot: *99#*/
// APN data
#define GPRS_APN       "GPRS_APN" // replace your GPRS APN
#define GPRS_LOGIN     "login"    // replace with your GPRS login
#define GPRS_PASSWORD  "*99#" 
// initialize the library instance
GSMClient gsmclient;
GPRS gprs;
GSM gsmAccess;

char server[] = "arduino.cc";
char path[] = "/asciilogo.txt";
int port = 80; // port 80 is the default for HTTP

#ifdef GSMMQTT
void GsmInitalization(){
  boolean notConnected = true;

  while (notConnected) {
    if ((gsmAccess.begin(PINNUMBER) == GSM_READY) &
        (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY)) {
      notConnected = false;
      Serial.println(F("Gsm Connection succesful");
    } else {
      Serial.println(F("Gsm connection failed!!!"));
      delay(1000);
    }
  }
}

void GsmLoop(){
  
}
#endif

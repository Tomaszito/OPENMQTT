#ifdef DHT11
void DHT11Setup() {
#ifdef  DHT11Temp1
  dht1.begin();
#endif
#ifdef  DHT11Temp2
  dht2.begin();
#endif
#ifdef  DHT11Temp3
  dht3.begin();
#endif
#ifdef  DHT11Temp4
  dht4.begin();
#endif
#ifdef  DHT11Temp5
  dht5.begin();
#endif
#ifdef  DHT11Temp6
  dht6.begin();
#endif
#ifdef  DHT11Temp7
  dht7.begin();
#endif
#ifdef  DHT11Temp8
  dht8.begin();
#endif
#ifdef  DHT11Temp9
  dht9.begin();
#endif
#ifdef  DHT11Temp10
  dht10.begin();
#endif
#ifdef  DHT11Temp11
  dht11.begin();
#endif
#ifdef  DHT11Temp12
  dht12.begin();
#endif
#ifdef  DHT11Temp13
  dht13.begin();
#endif
#ifdef  DHT11Temp14
  dht14.begin();
#endif
#ifdef  DHT11Temp15
  dht15.begin();
#endif
#ifdef  DHT11Temp16
  dht16.begin();
#endif
#ifdef  DHT11Temp17
  dht17.begin();
#endif
#ifdef  DHT11Temp18
  dht18.begin();
#endif
}

void DHT11Loop() {
#ifdef  DHT11Temp1
tempState[0] = dht1.readTemperature();
hudimitystate[0] = dht1.readHumidity();
#endif
#ifdef  DHT11Temp2
tempState[1] = dht2.readTemperature();
hudimitystate[1] = dht2.readHumidity();
#endif
#ifdef  DHT11Temp3
tempState[2] = dht3.readTemperature();
hudimitystate[2] = dht3.readHumidity();
#endif
#ifdef  DHT11Temp4
tempState[3] = dht4.readTemperature();
hudimitystate[3] = dht4.readHumidity();
#endif
#ifdef  DHT11Temp5
tempState[4] = dht5.readTemperature();
hudimitystate[4] = dht5.readHumidity();
#endif
#ifdef  DHT11Temp6
tempState[5] = dht6.readTemperature();
hudimitystate[5] = dht6.readHumidity();
#endif
#ifdef  DHT11Temp7
tempState[6] = dht7.readTemperature();
hudimitystate[6] = dht7.readHumidity();
#endif
#ifdef  DHT11Temp8
tempState[7] = dht8.readTemperature();
hudimitystate[7] = dht8.readHumidity();
#endif
#ifdef  DHT11Temp9
tempState[8] = dht9.readTemperature();
hudimitystate[8] = dht9.readHumidity();
#endif
#ifdef  DHT11Temp10
tempState[9] = dht10.readTemperature();
hudimitystate[9] = dht10.readHumidity();
#endif
#ifdef  DHT11Temp11
tempState[10] = dht11.readTemperature();
hudimitystate[10] = dht11.readHumidity();
#endif
#ifdef  DHT11Temp12
tempState[11] = dht12.readTemperature();
hudimitystate[11] = dht12.readHumidity();
#endif
#ifdef  DHT11Temp13
tempState[12] = dht13.readTemperature();
hudimitystate[12] = dht13.readHumidity();
#endif
#ifdef  DHT11Temp14
tempState[13] = dht14.readTemperature();
hudimitystate[13] = dht14.readHumidity();
#endif
#ifdef  DHT11Temp15
tempState[14] = dht15.readTemperature();
hudimitystate[14] = dht15.readHumidity();
#endif
#ifdef  DHT11Temp16
tempState[15] = dht16.readTemperature();
hudimitystate[15] = dht16.readHumidity();
#endif
#ifdef  DHT11Temp17
tempState[16] = dht17.readTemperature();
hudimitystate[16] = dht17.readHumidity();
#endif
#ifdef  DHT11Temp18
tempState[17] = dht18.readTemperature();
hudimitystate[17] = dht18.readHumidity();
#endif
#ifdef DHTDEBUG
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));
  #endif
}
#endif

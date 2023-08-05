// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)


float dHT22_humid;
float dHT22_temp;
float dHT22_temp2;
float palokaasut;
int ovien_avaukset_per_vrk;
int ovien_Avaustaajuus;

void initProperties(){

  ArduinoCloud.addProperty(dHT22_humid, READ, 10 * SECONDS, NULL);
  ArduinoCloud.addProperty(dHT22_temp, READ, 10 * SECONDS, NULL);
  ArduinoCloud.addProperty(dHT22_temp2, READ, 10 * SECONDS, NULL);
  ArduinoCloud.addProperty(palokaasut, READ, 10 * SECONDS, NULL);
  ArduinoCloud.addProperty(ovien_avaukset_per_vrk, READ, 10 * SECONDS, NULL);
  ArduinoCloud.addProperty(ovien_Avaustaajuus, READ, 10 * SECONDS, NULL);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

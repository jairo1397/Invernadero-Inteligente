// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "a97a680f-df1a-4c6d-b42f-01ddd459c3f7";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onRelayBombaChange();
void onRelayFocoChange();

float humedad;
float temperatura;
int humedad_suelo;
bool relay_bomba;
bool relay_foco;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(humedad, READ, ON_CHANGE, NULL, 1);
  ArduinoCloud.addProperty(temperatura, READ, ON_CHANGE, NULL, 1);
  ArduinoCloud.addProperty(humedad_suelo, READ, ON_CHANGE, NULL, 1);
  ArduinoCloud.addProperty(relay_bomba, READWRITE, ON_CHANGE, onRelayBombaChange);
  ArduinoCloud.addProperty(relay_foco, READWRITE, ON_CHANGE, onRelayFocoChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

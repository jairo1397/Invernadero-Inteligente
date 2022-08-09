#include "arduino_secrets.h"

#include <DHTesp.h>
#include "thingProperties.h"
DHTesp dht;
#define relay_bomb 26
#define relay_foc 27

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  dht.setup(15,DHTesp::DHT11);
  pinMode(relay_bomb, OUTPUT);
  pinMode(relay_foc, OUTPUT);
  }

void loop() {
  ArduinoCloud.update();
  // Your code here 
  temperatura = dht.getTemperature();
  humedad = dht.getHumidity();
  humedad_suelo=analogRead(34);
  delay(5000);
  
}

void onRelayBombaChange(){
  if (relay_bomba && humedad_suelo>3500 ){
    digitalWrite(relay_bomb, HIGH);
    delay(5000);
  } else {
    digitalWrite(relay_bomb, LOW);
  }
}


void onRelayFocoChange(){
  if (relay_foco){
    digitalWrite(relay_foc, HIGH);
  } else {
    digitalWrite(relay_foc, LOW);
  }
}







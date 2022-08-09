#include "arduino_secrets.h"// Importar los datos con el que se conecta a Internet

#include <DHTesp.h> //Una biblioteca Arduino para leer la familia DHT de sensores de temperatura y humedad.
#include "thingProperties.h"// importar donde esta declarada las variables y funciones

DHTesp dht; //Creamos una instancia de DHTesp

//Asignacion de pines de los relay para la bomba de agua y el foco
#define relay_bomb 26 
#define relay_foc 27

#define pinSensorDT11 15
#define pinSensorHumedadSuelo 34

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);//Nivel de informacion, el máximo es 4 y el mínimo es cero. Para hoy, lo estableceremos en 2.
  ArduinoCloud.printDebugInfo();// La función ArduinoCloud.printDebugInfo() le permite obtener más información
  // relacionada con el estado de la red y la conexión y errores de IoT Cloud. 
  
  //Asingacion del pin del sensor DT11
  dht.setup(pinSensorDT11,DHTesp::DHT11);
  
  pinMode(relay_bomb, OUTPUT);
  pinMode(relay_foc, OUTPUT);
  }

void loop() {

  ArduinoCloud.update();

  // Obtener los valores de temperatura y humedad del DHT11
  temperatura = dht.getTemperature();
  humedad = dht.getHumidity();

  //Obtener el valor de humedad del suelo
  humedad_suelo=analogRead(pinSensorHumedadSuelo);

  onRelayBombaChange();
  onRelayFocoChange();

  delay(5000);
  
}

void onRelayBombaChange(){

  // va de 0 (muy mojado) a 5000 (muy seco)
  if (relay_bomba || humedad_suelo>3500){
    digitalWrite(relay_bomb, LOW); // Se prende
  } else {
    if(humedad_suelo < 2500){
       digitalWrite(relay_bomb, HIGH);// Se apaga   
    }
  }
}

void onRelayFocoChange(){
  if (relay_foco || temperatura<20){
    digitalWrite(relay_foc, LOW); // Se prende
  } else {
    if(temperatura>=21){
    digitalWrite(relay_foc, HIGH); // Se apaga
    }
  }
}






//datos
#include "datos.h"
#include "ledyBuzzer.hpp"
#include "pantalla.hpp"
#include "sensor.hpp"
#include "ConfigWifi.hpp"
#include "SendDatos.hpp"


void setup(){
  Serial.begin(9600); // abre puerto serie para comunicarse
  inicializarAccesorios(); //cambiar pines, chocan con la comunicación de la pantalla OLED
  inicializarDisplay();
  Wsetup();
  inicializarSensor();
  Mqttsetup();
}

void loop(){
  checkButton();
  trabajoSensor();
  mqttLoop();
}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h> // manejo de wifi de wemos
#include <MHZ19_uart.h>  // incluye librería para manejo del sensor de CO2
#include <DHT.h>

#define PIN_CONEXION D3// A cuál pin está conectado el lector
#define TIPO_SENSOR DHT22 // Puede ser DHT11 también

DHT dht22(PIN_CONEXION, TIPO_SENSOR);
float humedad, temperatura = 0;
int tempInt;

// Network SSID - nombre de la red wifi y clave
const char* ssid = "Espora-A125"; //"2.4GHz-DBZ";  // nombre de la red
const char* password = "A125espora";  // clave
WiFiServer server(80);  // crea un servicio que escucha conecciones entrantes de un puerto específico

//#define OLED_RESET 4
// Definir constantes
#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 64 // alto pantalla OLED
 
// Objeto de la clase Adafruit_SSD1306
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1); //conecta D1 y D2

const int rx_pin = D4;  //Serial rx pin no
const int tx_pin = D5; //Serial tx pin no
const int buzzer = D7 ; // pin del buzzer, rx
const int dhtDato = D3; //pin del dht, D0
int cnt = 0; // cuenta LOOPS

//datos de los leds
const int led_R = D6 ; // control LED ROJO
const int led_V = D7 ; // control LED VERDE
const int led_A = D8 ; // control LED AZUL
boolean anodoComun0 = true;   // Led RGB (ánodo común)

const int cal_pin = D8;  // entrada pulsador calibración, tx
//***********************

MHZ19_uart mhz19; // asigna medidor al sensor

int co2ppm;

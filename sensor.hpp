#include "Wifi.hpp"

void inicializarSensor(){
    empezaelWifi();

  mhz19.begin(rx_pin, tx_pin); // inicializa el sensor de CO2
  dht22.begin(); //inicializa el sensor de temp y humedad
  /*
       MH-Z19 has automatic calibration procedure. the MH-Z19 executing automatic calibration, its do zero point(stable gas environment (400ppm)) judgement.
       The automatic calibration cycle is every 24 hours after powered on.
       If you use this sensor in door, you execute `setAutoCalibration(false).
  */
  mhz19.setAutoCalibration(false);

  presentacionDisplay();
  tone(buzzer, 55,100); // pitido de 55Hz indicando que funciona normal, calentando
}

void calibrar()
{
   definirColor(0, 0, 255, anodoComun0); //PRENDE LED AZUL
   displayCalibracionInicio(); //indica que empieza la calibración, demora y donde ubicar el equipo.
   displayEsperaMediaHora();   //pantalla donde se espera y se cuenta media hora. Antes de la calibración.

  // paso media hora
  mhz19.calibrateZero();       //Calibra
  displayPrimeraCalibracion(); //avisa y espera un minuto

  mhz19.calibrateZero();       //Calibra por segunda vez por las dudas
  displaySegundaCalibracion(); //avisa y espera 10 segundos, también avisa el fin de la calibración
}

void trabajoSensor(){
  /*if (digitalRead(cal_pin) == LOW) { // si detecta el botón de calibrar apretado, calibra
      calibrar();
  }*/
  int co2ppm = mhz19.getPPM(); // mide CO2
  humedad = dht22.readHumidity();
  temperatura = dht22.readTemperature();

  displayMedicionCO2(co2ppm);   //  Muestra medición de CO2
  displayMedicionTemp();  //  Muestra medición de temperatura
  displayMedicionHumedad();
  Serial.println(co2ppm); // escribe en el puerto serie el valor de CO2
  mostrarValorEnWeb(co2ppm); //muestro el valor por la pagina html
  
//  Emite un sonido y escribe en función del resultado
    int tono = co2ppm / 100;
    display.setCursor(0, 48);
    display.print("R: ");

    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");
    
    switch (tono){
    case 3: // menor a 600ppm, 55Hz, 0.1 seg
       display.println("BAJO"); 
       display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo      
       definirColor(0, 50, 0,anodoComun0); // PRENDE LED VERDE
       break;
    case 4: // menor a 600ppm, 55Hz, 0.1 seg
       display.println("BAJO");
       display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo  
       definirColor(0, 50, 0,anodoComun0); // PRENDE LED VERDE
       break;
    case 5: // menor a 600ppm, 55Hz, 0.1 seg
//       tone(buzzer, 55,100);
       display.println("BAJO");
       display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo       
       definirColor(0, 50, 0,anodoComun0); // PRENDE LED VERDE
       break;
    case 6: // menor a 700ppm, 55Hz, 0.1 seg// menor a 600ppm
//       tone(buzzer, 55,100);
       display.println("BAJO");
       display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo  
       definirColor(0, 50, 0,anodoComun0); // PRENDE LED VERDE
       break;
    case 7: // menor a 800ppm, 55Hz, 0.1 seg
       tone(buzzer, 55,100);
       display.println("MEDIO");
       display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo     
       definirColor(255, 50, 0,anodoComun0); // PRENDE LED AMARILLO (pongo 50 en lugar de 255 para compensar ls diferencia de tensión en directa del diodo rojo)
       break;
    case 8: // menor a 900ppm, 110Hz, 1 seg
       tone(buzzer, 110,1000);
       display.println("ALTO");
       display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo     
       definirColor(255, 0, 0,anodoComun0); // PRENDE LED ROJO
       break;
    case 9: // menor a 1000ppm, 220Hz, 2 seg
       tone(buzzer, 220,2000);
       display.println("ALTO");
       display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo       
       definirColor(255, 0, 0,anodoComun0); // PRENDE LED ROJO
       break;
    case 10: // menor a 1100ppm, 440Hz, 2 seg
       tone(buzzer, 440,2000); 
       display.println("ALTO");
       display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo       
       definirColor(255, 0, 0,anodoComun0); // PRENDE LED ROJO
       break;
    case 11: // menor a 120ppm, 880Hz, 2 seg
       tone(buzzer, 880,2000); 
       display.println("ALTO!!");
       display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo      
       definirColor(255, 0, 0,anodoComun0); // PRENDE LED ROJO
       break;
    default: // menor a 1300ppm, 880Hz, 4 seg
       tone(buzzer, 880,4000);
       display.println("ALTO!!!");
       display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo      
       definirColor(255, 0, 0,anodoComun0); // PRENDE LED ROJO
       break;
    }
  delay(10000); //demora 10 seg entre mediciones
}

void inicializarDisplay(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Limpiar buffer
  display.clearDisplay();
  // Tamaño del texto
  display.setTextSize(1); 
  /*controla el tamaño del texto 
  1: unos 12 caracteres por linea,
  2: unos 10 caracteres por linea,
  3: unos 7 caracteres por linea, 2 lineas y media
  4: unos 6 caracteres por linea, 2 lineas justo
  5: unos 4 caracteres por linea, 1 linea y media
  6: unos 3 caracteres por linea, 1 linea y cuarto
  7: unos 3 caracteres por linea, 1 linea y octavo
  8: unos 2 caracteres en pantalla
  9: unos 2 caracteres en pantalla
  10: unos 2 caracteres en pantalla, recortados
  */
  // Color del texto
  display.setTextColor(SSD1306_WHITE);
}

void displayEncabezado(){// dibuja Encabezado
    display.clearDisplay();  // borra pantalla
    display.setTextSize(2);
    display.setCursor(0, 0); // Ubicamos el cursor 
    display.println("SiCoBioNa"); // Cada minuto muestra el valor
    display.setCursor(36, 16); // Ubicamos el cursor
    display.setTextSize(3); 
    display.println("UNQ"); // Cada minuto muestra el valor
    display.setTextSize(1);
    display.setCursor(0,38); // muestra indicación de que está calentando   
    display.println("MEDIDOR de CO2");    // Escribe texto
    display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
    cnt = 0; // vuelve a empezar LOS LOOPS
}

void presentacionDisplay(){
  // Escribimos el Mensaje en el display.
  display.setCursor(0, 0); // Ubicamos el cursor en la primera posición(columna:0) de la primera línea(fila:0)
  //Activar página de código 437
  display.cp437(true);
  //Escribir el carácter ¡ dos veces
  display.write(173);
  display.println("INICIANDO!");
  display.display();
  delay(1000); // espera 5 segundos
  display.clearDisplay();
  display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
  // se presenta 
  displayEncabezado();
  delay(1000); // espera 5 segundos  
  display.setTextSize(1); 
  display.setCursor(0,46); 
  display.println("Calentando");
  display.println("Espere 1 minuto");
  display.display(); //envía lo anterior al display  
  delay(60000); // espera 1 minuto
}


void displayCalibracionInicio(){
  // se presenta
  display.clearDisplay();
  display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
  display.setCursor(0,0);
  display.println("CALIBRACION");
  display.setCursor(0,16);
  display.println("DEMORA 30 MIN");  
  display.setCursor(0,31);
  display.println("PONER EL EQUIPO");
  display.setCursor(0,46);
  display.println("AL AIRE LIBRE");
  display.display();
  delay(1000); // Espera 30 segundos,
  display.clearDisplay();
  display.setCursor(0,16);
  display.println("COMIENZA");
  display.println("CALIBRACION");
  display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
  delay(1000); // Espera 10 segundos
}

void displayEsperaMediaHora(){
  const int waitingMinutes = 30; //cantidad de minutos a esperar
  long waitingSeconds = waitingMinutes * 60L; // cantidad de segundos a esperar
  int minute = 0;
  int second = 0;
  while (--waitingSeconds >= 0) { // espera media hora
    display.clearDisplay();
    display.setTextSize(2); //Cambia el tamaño de fuente
    display.setCursor(0,0);
    display.println("CALIBRANDO"); //
    minute = waitingSeconds/60;
    second = waitingSeconds%60;
    if(minute<=9){
      display.setCursor(0,16);
      display.println("0"); // muestra los minutos
      display.setCursor(12,16);
      display.println(minute); // muestra los minutos
    }else{
      display.setCursor(0,16);
      display.println(minute); // muestra los segundos
    }
    display.setCursor(24,16);
    display.println(":"); //
    if(second<=9){
      display.setCursor(36,16);
      display.println("0"); // muestra los segundos
      display.setCursor(48,16);
      display.println(second); // muestra los segundos
    }else{
      display.setCursor(36,16);
      display.println(second); // muestra los segundos
    }
    display.setCursor(72,16); // Ubicamos el cursor
    tempInt = int(dht22.readTemperature());
    display.print(tempInt);
    display.write(167);
    display.print("C");
    display.setCursor(0,32); // Ubicamos el cursor 
    display.println("CO");    // Escribe texto
    display.setTextSize(1); //Cambia el tamaño de fuente
    display.setCursor(24,41); // Ubicamos el cursor 
    display.println("2");    // Escribe texto
    display.setTextSize(2); //Cambia el tamaño de fuente
    display.setCursor(28,33); // Ubicamos el cursor 
    display.println(":");    // Escribe texto
    display.setCursor(35,33); // Ubicamos el cursor 
    display.println(mhz19.getPPM()); // Escribe CO2
    display.setTextSize(1); //Cambia el tamaño de fuente
    display.setCursor(88,40); // Ubicamos el cursor 
    display.println("ppm"); // Escribe texto
    display.setTextSize(2);
    display.setCursor(0,50); // Ubicamos el cursor 
    display.print("H:");
    display.print(dht22.readHumidity());
    display.print("%");
    display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
    delay(1000); // Espera 1 segundo
  }
}

void displayPrimeraCalibracion(){
  display.clearDisplay();     // borra pantalla
  display.setCursor(0,0);
  display.println("PRIMERA");
  display.setCursor(0,16);
  display.println("CALIBRACION");
  display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
  delay(60000); // Espera 60 segundos
}
void displaySegundaCalibracion(){  
  display.clearDisplay();  // borra pantalla  
  display.setCursor(0,0);
  display.println("SEGUNDA");
  display.setCursor(0,16);
  display.println("CALIBRACION");    // Escribe texto
  display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
  delay(10000); // Espera 10 segundos
  display.clearDisplay();  
  display.setCursor(0,16);
  display.println("CALIBRACION");    // Escribe texto
  display.println("TERMINADA");      // Escribe texto
  display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
  delay(10000); // Espera 10 segundos 
}

void displayMedicionCO2(int co2ppm){
  display.clearDisplay();  // borra pantalla
  display.setTextSize(2); // pone en tamaño doble
  display.setCursor(0,0); // Ubicamos el cursor 
  display.print("CO");    // Escribe texto
  display.setTextSize(1); //Cambia el tamaño de fuente
  display.setCursor(24,9); // Ubicamos el cursor 
  display.print("2");    // Escribe texto
  display.setTextSize(2); //Cambia el tamaño de fuente
  display.setCursor(28,0); // Ubicamos el cursor 
  display.print(":");    // Escribe texto
  display.print(co2ppm);
  display.setTextSize(1); //Cambia el tamaño de fuente
  display.setCursor(88,5); // Ubicamos el cursor 
  display.println("ppm");
  display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
}

void displayMedicionTemp(){
  display.setTextSize(2); //Cambia el tamaño de fuente
  display.setCursor(0, 16);
  display.print("T: ");
  display.print(temperatura);
  display.write(167);
  display.println("C");
  display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
}
void displayMedicionHumedad(){
  display.setCursor(0, 32);
  display.print("H: ");
  display.print(humedad);
  display.println("%");
  display.display(); //envía lo anterior al display, si se usa luego de un clearDisplay borra todo
}

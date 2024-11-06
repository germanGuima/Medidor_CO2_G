void empezaelWifi(){
  delay(10);
  
   Serial.printf("Servidor Web Iniciado, abra %s en un navegador web\n", WiFi.localIP().toString().c_str()); // avisa que se abrió la el puerto y da el número
  server.begin();
}
// prepara página web para mandar a un cliente (servidor web)

String prepararPaginaWeb(int co2ppm){
  String htmlPage;  
  htmlPage.reserve(1024);               // prevent ram fragmentation
  htmlPage = F("HTTP/1.1 200 OK\r\n"
               "Content-Type: text/html\r\n"
               "Connection: close\r\n"  // the connection will be closed after completion of the response
               "Refresh: 5\r\n"         // refresh the page automatically every 5 sec
               "\r\n"
               "<!DOCTYPE HTML>"
               "<html>"
               "CO2:  ");
  htmlPage += co2ppm; // imprime el valor de CO2
  htmlPage += F("ppm");
  htmlPage += F("\t");
  htmlPage += F("Humedad:  ");
  htmlPage += humedad;
  htmlPage += F("%");
  htmlPage += F("\t");
  htmlPage += F("Temperatura:  ");
  htmlPage += temperatura;
  htmlPage += F("   C");
  htmlPage += F("\r\n");
return htmlPage;
}

void mostrarValorEnWeb(int co2ppm){
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
//*    Serial.println("\n[Client connected]");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String line = client.readStringUntil('\r');
//*        Serial.print(line);
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          client.println(prepararPaginaWeb(co2ppm));
          break;
        }
      }
    }

    while (client.available()) {
      // but first, let client finish its request
      // that's diplomatic compliance to protocols
      // (and otherwise some clients may complain, like curl)
      // (that is an example, prefer using a proper webserver library)
      client.read();
    }

    // close the connection:
    client.stop();
//*    Serial.println("[Client disconnected]");
  }
  
  if(WiFi.status() == WL_DISCONNECTED){  // si se desconectó
      Serial.println("Se perdió la conexion WiFi! Reiniciando..."); // avisa que se perdió la conexión de wifi
    }
}
/* */


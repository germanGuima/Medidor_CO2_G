
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <ArduinoJson.h>


const char *mqtt_broker = "4a98668d55074575a6e66b180cc7b6b2.s1.eu.hivemq.cloud"; // broker address
const char *topic = "a"; // define topic 
const char *mqtt_username = "german"; // username for authentication
const char *mqtt_password = "German1234"; // password for authentication
const int mqtt_port = 8883; // port of MQTT over TCP
/*Print the topic name to the serial port and then print every byte of received messages.*/

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

WiFiClientSecure espClient;
PubSubClient client(espClient);


void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}
//seteo del Mqtt ,intenta conectar al broker 
void Mqttsetup(){
espClient.setInsecure(); 
client.setServer(mqtt_broker, mqtt_port);
client.setCallback(callback);
 
       while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
        Serial.println("Connected to MQTT broker.");
    } else {
        Serial.print("Failed to connect to MQTT broker, rc=");
        Serial.print(client.state());
        Serial.println(" Retrying in 5 seconds.");
        delay(5000);
    }
  }
    client.publish(topic, "Inicio esp8266"); // publish to the topic
    client.subscribe(topic); // subscribe from the topic
}



/************* Connect to MQTT Broker ***********/
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "esp32Client-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");

      client.subscribe("led_state");   // subscribe the topics here

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


/**** Method for Publishing MQTT Messages **********/
void publishMessage(const char* topic, String payload , boolean retained){
  if (client.publish(topic, payload.c_str(), true))
      Serial.println("Message publised ["+String(topic)+"]: "+payload);
}

//publica cada X segundos (5) ,humedad id ,lugar
void mqttLoop(){

  if (!client.connected()) reconnect(); // check if client is connected
  client.loop();

//read DHT11 temperature and humidity reading

  DynamicJsonDocument doc(1024);
  doc["deviceId"] = "NodeMCU";
 // doc["siteId"] = "Labo1";
  doc["humedad"] =    roundf( humedad);
  doc["temperatura"] = roundf( temperatura);
  doc["Co2_ppm"] =  mhz19.getPPM();
  char mqtt_message[128];
  serializeJson(doc, mqtt_message);

  publishMessage("a", mqtt_message, true);

  delay(5000);


}

 
#include "PubSubClient.h"
#include "WiFi.h";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;
char topico[50];

const char* ssid = "XuxaPark";
const char* password = "aquelala";
const char* mqtt_server = "broker.hivemq.com"; 
const int port = 1883;

int sensorVaga1 = 19;
int sensorVaga2 = 18;
int sensorVaga3 = 21;
int LED_BUILTIN = 2;

void setup_wifi(){
    delay(10);
    WiFi.begin(ssid,password);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   }
 }

void setup() {

  Serial.begin(115200);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  //client.subscribe("Unifor/Estacionamento/Vaga/");
  
  pinMode(sensorVaga1,INPUT);
  pinMode(sensorVaga2,INPUT);
  pinMode(sensorVaga3,INPUT);
  pinMode(LED_BUILTIN,OUTPUT);

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32HelderVictor")) {
      Serial.println("connected");
      // Subscribe
      //client.subscribe("Topico/Estacionamento/UNIFOR/"+i);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
   if(!client.connected()){
     reconnect();
   }
   client.loop();

  if(!digitalRead(sensorVaga1)){
    
    //ocupado
    //enviar pro broker uma string (sensorVaga + 1 ou 0) 
    
      //JOEL//
    //sprintf(msg, "Teste valor: %d", sensorVaga1);
    //client.publish("TopicoEstacionamentoUNIFOR", msg);
      //JOEL//

    char tempString[8];
    sprintf(tempString, "%d", 42);
    client.publish("Unifor/Estacionamento/Vaga/1", tempString);
    digitalWrite(LED_BUILTIN,HIGH);
  }
  
}

/*
  PROJECT: Uni Parking.
   
  SPECIAL THANKS:
  - Paulo Cirillo Souza Barbosa;
  - Joel Sotero da Cunha Neto.
  
  TEAM MEMBERS:
  - Caio Sampaio Oliveira;
  - Eric da Silva Maia;
  - Helder Andrade de Andrade;
  - João Gabriel Cunha Jataí;
  - Ramon Feitosa Rodrigues;
  - Victor Kauan Lima de Oliveira.
*/

#include "PubSubClient.h"
#include "WiFi.h";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;
char topico[50];

const char* ssid = "MeElimina100or";
const char* password = "senhaforte";
const char* mqtt_server = "broker.hivemq.com"; 
const int port = 1883;

int sensorVaga1 = 18;
int sensorVaga2 = 21;
int sensorVaga3 = 19;
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
  
  pinMode(sensorVaga1,INPUT);
  pinMode(sensorVaga2,INPUT);
  pinMode(sensorVaga3,INPUT);
  pinMode(LED_BUILTIN,OUTPUT);

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESP32HelderVictor")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if(!client.connected())
   reconnect();
  
  client.loop();
  
  if (!digitalRead(sensorVaga1)) {
    char mensagemVagaOcupada[1];
    sprintf(mensagemVagaOcupada, "1");
    client.publish("Unifor/Estacionamento/Vaga/1", mensagemVagaOcupada);
  } else {
    char mensagemVagaLivre[1];
    sprintf(mensagemVagaLivre, "0");
    client.publish("Unifor/Estacionamento/Vaga/1", mensagemVagaLivre);
  }

  if (!digitalRead(sensorVaga2)) {
    char mensagemVagaOcupada[1];
    sprintf(mensagemVagaOcupada, "1");
    client.publish("Unifor/Estacionamento/Vaga/2", mensagemVagaOcupada);
  } else {
    char mensagemVagaLivre[1];
    sprintf(mensagemVagaLivre, "0");
    client.publish("Unifor/Estacionamento/Vaga/2", mensagemVagaLivre);
  }

  if (!digitalRead(sensorVaga3)) {
    char mensagemVagaOcupada[1];
    sprintf(mensagemVagaOcupada, "1");
    client.publish("Unifor/Estacionamento/Vaga/3", mensagemVagaOcupada);
  } else {
    char mensagemVagaLivre[1];
    sprintf(mensagemVagaLivre, "0");
    client.publish("Unifor/Estacionamento/Vaga/3", mensagemVagaLivre);
  }

  delay(1000);
}

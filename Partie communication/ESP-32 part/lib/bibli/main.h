#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <esp_camera.h>
#include <Base64.h>

#define TXp2 12
#define RXp2 13


// adresse IP de la VM
IPAddress server(20, 203, 148, 167);

// objet WIFI
WiFiClient wifiClient;

// objet MQTT
PubSubClient client(wifiClient);

String messageTemp;



// Variables globales

bool newData = false;
String strArrayOutput[4];
String strArray[20];
int StringCount = 0;
bool var = true;
int available = 0;
// pour éviter d'encombrer l'envoi de données
bool EtatOld;
// variable temporisation
int tempstemp = 0;
bool traitement = false;
bool firstPassage = true;
String strOutput;

void Publish(void);


void cutString(String data);
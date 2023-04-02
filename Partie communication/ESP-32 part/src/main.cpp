#include <main.h>

// fonction appelée quand une variable MQTT est actualisée (où l'on est subscribe)
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // reconstitution du message
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    messageTemp += (char)payload[i];
  }

  // choix de la variable à actualiser
  if (String(topic) == "sae/joystick/vertical")
  {
    strArrayOutput[0] = messageTemp;
  }
  if (String(topic) == "sae/joystick/horizontal")
  {
    strArrayOutput[1] = messageTemp;
  }
  if (String(topic) == "sae/data/led")
  {
    strArrayOutput[2] = messageTemp;
  }
  if (String(topic) == "sae/data/buzzer")
  {
    strArrayOutput[3] = messageTemp;
  }
}

// tant que le client n'est pas connecté, on essaie de se connecter
void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect - nom de l'appareil : "esp32" - nom d'utilisateur : "admin" - mot de passe : "Bonjourmarius&"
    if (client.connect("esp32", "admin", "Bonjourmarius&"))
    {
      Serial.println("connected");
      //... and resubscribe
      client.subscribe("sae/joystick/horizontal");
      client.subscribe("sae/joystick/vertical");
      client.subscribe("sae/data/led");
      client.subscribe("sae/data/buzzer");
    }
    else
    {
      // print the error
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial2.begin(19200, SERIAL_8N1, RXp2, TXp2);

  // PARAMETRES WIFI
  // station mode -> mode slave
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  // connexion au réseau wifi du téléphone : ssid -> "test", password -> "123456789"
  WiFi.begin("test", "123456789");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }

  // PARAMETRES MQTT
  // connexion au serveur
  client.setServer(server, 1883);
  // définition de la fonction à appeler lorsqu'une variable est actualisée
  client.setCallback(callback);

  // Permettre au système de s'en sortir
  delay(1500);
}

void loop()
{
  // condition validée au début lors du premier passage dans la boucle
  if (firstPassage)
  {
    digitalWrite(33, HIGH);
    delay(10);
    digitalWrite(33, LOW);

    //remplissage du tableau de sortie avec des valeurs par défaut
    for (int iBcl = 0; iBcl < 4; iBcl++)
    {
      strArrayOutput[iBcl] = "0";
    }
    //envoi des valeurs par défaut
    strOutput = (strArrayOutput[0] + " " + strArrayOutput[1] + " " + strArrayOutput[2] + " " + strArrayOutput[3]);
    Serial2.print(strOutput + '\n');
    firstPassage = false;
  }

  // si donnée reçue
  if (Serial2.available() > 0)
  {
    message = Serial2.readStringUntil('\n');
    analogWrite(4, 1);
    delay(10);
    analogWrite(4, 0);

    // découpage du message
    cutString(message);

    //publication MQTT
    Publish();


    digitalWrite(33, LOW);
    delay(10);
    digitalWrite(33, HIGH);

    //valeurs actualisées dans la fonction callback
    strOutput = (strArrayOutput[0] + " " + strArrayOutput[1] + " " + strArrayOutput[2] + " " + strArrayOutput[3]);
    Serial2.print(strOutput + '\n');
  }

  // reconnexion si déconnexion
  if (!client.connected())
  {
    reconnect();
  }

  // Serial.println(data);

  // led de fonctionnement sur node red
  client.publish("sae/data/fct", "1");

  // gére WIFI
  client.loop();

  // utile ? je ne pense pas
  delay(50);
}
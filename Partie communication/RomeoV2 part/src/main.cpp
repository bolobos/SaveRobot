#include <Arduino.h>

void cutString(String data)
{
  String strArray[20];
  while (data.length() > 0)
  {
    int index = data.indexOf(' ');
    if (index == -1) // No space found
    {
      strArray[StringCount++] = data;
      break;
    }
    else
    {
      strArray[StringCount++] = data.substring(0, index);
      data = data.substring(index + 1);
    }
  }
}

void setup()
{
  // initialisation liaison série
  Serial1.begin(115200, SERIAL_8N1);
  pinMode(LED_BUILTIN, OUTPUT);
}

// string venant de l'esp32
String message;

// tableau de string pour la réception (à changer en float si besoin)
String strArrayRecep[10];
String strArrayEnvoi[10];

// compteur
int StringCount = 0;

void loop()
{
  // analogWrite(LED_BUILTIN, 0);
  //  digitalWrite(8, HIGH);
  //  analogWrite(LED_BUILTIN, 50);

  if (Serial1.available() > 0)
  {
    // lecture bloquante jusqu'au retour à la ligne
    message = Serial1.readStringUntil('\n');
    analogWrite(LED_BUILTIN, 100);
    delay(20);
    analogWrite(LED_BUILTIN, 0);
    delay(10);

    digitalWrite(LED_BUILTIN_RX, LOW);
    delay(10);
    digitalWrite(LED_BUILTIN_RX, HIGH);

    cutString(message);

    // A RESPECTER
    // strArray[0] -> joystick vertical
    // strArray[1] -> joystick horizontal
    // strArray[2] -> led
    // strArray[3] -> buzzer

    // Partie envoi

    // A RESPECTER
    // strArrayEnvoi[0] -> buzzer
    // strArrayEnvoi[1] -> position devant (front)
    // strArrayEnvoi[2] -> position derrière (back)
    // strArrayEnvoi[3] -> luminosité
    // strArrayEnvoi[4] -> led

    //Valeurs typiques
    strArrayEnvoi[0] = "true";
    strArrayEnvoi[1] = "3";
    strArrayEnvoi[2] = "3";
    strArrayEnvoi[3] = "254";
    strArrayEnvoi[4] = "1";

    String strOutput = (strArrayEnvoi[0] + " " + strArrayEnvoi[1] + " " + strArrayEnvoi[2] + " " + strArrayEnvoi[3] + " " + strArrayEnvoi[4] + "\n");
    digitalWrite(LED_BUILTIN_TX, LOW);
    delay(10);
    digitalWrite(LED_BUILTIN_TX, HIGH);
    Serial1.print(strOutput);
  }

  delay(10);
}

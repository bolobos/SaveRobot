#include <MesFonctions.h>

TEtat Etat;


// Contrôle PWM simple
int E1 = 5; // Contrôle vitesse moteur 1
int E2 = 6; // Contrôle vitesse moteur 2
int M1 = 4; // Contrôle direction moteur 1
int M2 = 7; // Contrôle direction moteur 2

void avancer(char x_char_vitesseM1,char x_char_vitesseM2){
  digitalWrite(M1, HIGH);                 //sens moteur 1
  digitalWrite(M2, HIGH);                 //sens moteur 2
  analogWrite(E1, x_char_vitesseM1);      //vitesse moteur 1
  analogWrite(E2, x_char_vitesseM2);      //vitesse moteur 2
}

void reculer(char x_char_vitesseM1,char x_char_vitesseM2){
  digitalWrite(M1, LOW);                  //sens moteur 1
  digitalWrite(M2, LOW);                  //sens moteur 2
  analogWrite(E1, x_char_vitesseM1);      //vitesse moteur 1
  analogWrite(E2, x_char_vitesseM2);      //vitesse moteur 2
}

void tournerGauche(char x_char_vitesseM1,char x_char_vitesseM2){
  digitalWrite(M1, LOW);                  //sens moteur 1
  digitalWrite(M2, HIGH);                 //sens moteur 2
  analogWrite(E1, x_char_vitesseM1);      //vitesse moteur 1
  analogWrite(E2, x_char_vitesseM2);      //vitesse moteur 2
}

void tournerDroite(char x_char_vitesseM1,char x_char_vitesseM2){
  digitalWrite(M1, HIGH);                 //sens moteur 1
  digitalWrite(M2, LOW);                  //sens moteur 2
  analogWrite(E1, x_char_vitesseM1);      //vitesse moteur 1
  analogWrite(E2, x_char_vitesseM2);      //vitesse moteur 2
}

void stop(void) // Stop
{
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
}

void setup(void)
{
  int i;
  for (i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }

  Serial.begin(19200); // Définit vitesse de transmission série
  
}
void loop(void)
{
  switch()

  /*if (Serial.available())
  {
    char val = Serial.read();
    if (val != -1)
    {
      switch (val)
      {
      case 'w':            // En avant
        advance(255, 255); // en avant vitesse max
        break;

      case 's':             // En arrière
        back_off(255, 255); // en arrière vitesse max
        break;
      case 'a': // Tourne à gauche
        turn_L(100, 100);
        break;
      case 'd': // Tourne à droite
        turn_R(100, 100);
        break;
      case 'z':
        Serial.println("Bonjour !");
        break;
      case 'x':
        stop();
        break;
      }
    }
    else
      stop();
  }*/
}
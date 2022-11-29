#include <MesFonctions.h>


CConvAN MyClass;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MyClass.InitCan8();
}

void loop() {
  // put your main code here, to run repeatedly:

}
  //Programme test joystick
  int sensorValue1 = analogRead(A0);
  int sensorValue2 = analogRead(A1);
 
  Serial.print("The X and Y coordinate is:");
  Serial.print(sensorValue1, DEC);
  Serial.print(",");
  Serial.println(sensorValue2, DEC);
  Serial.println(" ");
  delay(200);
  
  //passage vrai code
  uint8_t var = MyClass.ConvAN8();

  /*********************************************************************************************************************/
  //Programme test moteur (vitesse tout ou rien)
  int E1 = 5; // Contrôle vitesse moteur 1
  int E2 = 6; // Contrôle vitesse moteur 2
  int M1 = 4; // Contrôle direction moteur 1
  int M2 = 7; // Contrôle direction moteur 2

  void stop(void) //Stop
  {
  digitalWrite(E1,LOW);
  digitalWrite(E2,LOW);
  }
  void advance(char a,char b) // En avant
  {
  analogWrite (E1,a); // Contrôle de vitesse en PWM
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
  }
  void back_off (char a,char b) // En arrière
  {
  analogWrite (E1,a);
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
  }
  void turn_L (char a,char b) // Tourne à gauche
  {
  analogWrite (E1,a);
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
  }
  void turn_R (char a,char b) // Tourne à droite
  {
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
  }



  /**********************************************************************************************************************/

  //Programme test capteur ultrason
  Ultrasonic ultrasonic(7);

  long RangeInInches;
  long RangeInCentimeters;

  Serial.println("The distance to obstacles in front is: ");
  RangeInInches = ultrasonic.MeasureInInches();
  Serial.print(RangeInInches);//0~157 inches
  Serial.println(" inch");
  delay(250);

  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.print(RangeInCentimeters);//0~400cm
  Serial.println(" cm");
  delay(250);

  /**********************************************************************************************************************/



// à refaire mon infrarouge


#include <MesFonctions.h>


CConvAN MyClass;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MyClass.InitCan8();
}

void loop() {
  // put your main code here, to run repeatedly:
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
}

  //Programme test capteur ultrason
 

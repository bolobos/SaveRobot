#include <MesFonctions.h>

CConvAN MyClass;

void setup()
{
  Serial.begin(9600);
  MyClass.InitCan16(0);
}

void loop()
{
  int value = CConvAN.ConvAN16()
  int value = analogRead(A2);
  value = map(value, 0, 800, 0, 10);
  delay(100);
}
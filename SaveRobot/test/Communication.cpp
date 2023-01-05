#include <MesFonctions.h>

int g_int_josselin = 0;

float result = 0;

bool var = true; //-> premier rising edge

void ValideInterruptTOV1(){
  TCCR1A=0b00000000;
  TCCR1B=0b00000100;
  TCCR1C=0b00000000;
  TCNT1=3036;//fais l'interruption tout les 1 seconde
  TIMSK1=0b00000001;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //PB2
  DDRD = 0x00;

  noInterrupts();           // disable all interrupts

  //INT0
  EICRA = 0x03;             //rising edge
  EIMSK = 0x01;
  
  //Timer 1
  ValideInterruptTOV1();
  interrupts();            // enable all interrupts



}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Temps en ms : ");
  Serial.println(result);
  delay(1000);

}








ISR(INT0_vect) //interruption canal 1
{

  if (var) {
    TCNT1=3036;
    EICRA = 0x02; //falling edge
    var = !var;
  }
  else {
    result = (float)TCNT1 - 3036;
    result = result * 0.016;


    EICRA = 0x03; //rising edge
    var = !var;
  }
  
}

/*ISR(TIMER1_OVF_vect){

}*/
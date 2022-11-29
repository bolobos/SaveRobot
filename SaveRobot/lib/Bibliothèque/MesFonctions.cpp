#include <MesFonctions.h>
int l_int_var = 0;

void CConvAN::InitCan8(){

  //3 registres de configuration de l'entrée analogique
  ADCSRA = 0x84; // division facteur à 16, activer l'adc
  ADMUX = 0x61; // ADC1, left ajust, AVcc
  ADCSRB = 0x08; //  Analog Comparator Multiplexed Input -> config
}

void CConvAN::InitCan16(){

  //3 registres de configuration de l'entrée analogique
  ADCSRA = 0x84; // division facteur à 16, activer l'adc
  ADMUX = 0x41; // ADC1, AVcc sur l'extérieur
  ADCSRB = 0x08; // Analog Comparator Multiplexed Input -> config
}

uint8_t CConvAN::ConvAN8(){
  ADCSRA = (ADCSRA|0X40);
  do{}while((ADCSRA & 0x40) == 0x40);
  return ADCH;
}

uint16_t CConvAN::ConvAN16(){
  uint16_t l_uint16_var = 0;
  ADCSRA = (ADCSRA|0X40);
  do{}while((ADCSRA & 0x40) == 0x40);
  l_uint16_var = ( ADCL | (ADCH << 8));
  return l_uint16_var;
}


/*
void LiaisonSerie::InitCar(){

  //TO DO : registres à revoir
  UCSR1A = 0x22;
  UCSR1B = 0x10;
  UCSR1C = 0x06;
  UBRR1 = 103;  // 16 bits
}

char LiaisonSerie::litCar(){
  char l_char_c;
  do{}while((UCSR1A & MSK_VERIF) != MSK_VERIF);
  return l_char_c;
}

void LiaisonSerie::ecritCar(char x_char_c){
  do{}while((UCSR1A & MSK_VERIF) != MSK_VERIF);
  UDR1 = x_char_c;
}
*/

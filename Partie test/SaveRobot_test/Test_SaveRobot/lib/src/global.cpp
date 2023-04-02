#include <global.h>
int l_int_var = 0;
int g_int_tempBuzzer = 0;

void CConvAN::InitCan8()
{

  // 3 registres de configuration de l'entrée analogique
  ADCSRA = 0x84; // division facteur à 16, activer l'adc
  ADMUX = 0x61;  // ADC1, left ajust, AVcc
  ADCSRB = 0x08; //  Analog Comparator Multiplexed Input -> config
}

void CConvAN::InitCan16(int x_int_adcport)
{

  // 3 registres de configuration de l'entrée analogique
  ADCSRA = 0x84;                         // division facteur à 16, activer l'adc
  ADMUX = x_int_adcport and (1 << 0x41); // ADC1, AVcc sur l'extérieur
  ADCSRB = 0x08;                         // Analog Comparator Multiplexed Input -> config
}

uint8_t CConvAN::ConvAN8()
{
  ADCSRA = (ADCSRA | 0X40);
  do
  {
  } while ((ADCSRA & 0x40) == 0x40);
  return ADCH;
}

uint16_t CConvAN::ConvAN16()
{
  uint16_t l_uint16_var = 0;
  ADCSRA = (ADCSRA | 0X40);
  do
  {
  } while ((ADCSRA & 0x40) == 0x40);
  l_uint16_var = (ADCL | (ADCH << 8));
  return l_uint16_var;
}


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


void InitTimer1(void)
{
  TCCR1B = B00000100; //On choisit le prescaler a 256
  TCNT1 = 3036; 
}

void InitTimer3(void)
{
  TCCR3B = B00000100;//On choisit le prescaler a 256
  TCNT3 = 3036; 
}

void InitMouvements(void) //Permet d'initialiser les ports des moteurs
{
  int i; 
  for (i = 4; i <= 7; i++)
  {
    pinMode(i, OUTPUT);
  }
}
void InitReste(void)
{
  DDRD = 0x00;
  DDRF = B00000011;
  pinMode(13, INPUT);
}


void avancer(char x_char_vitesseM1, char x_char_vitesseM2)
{
  int E1 = 5; // Contrôle vitesse moteur 1
  int E2 = 6; // Contrôle vitesse moteur 2

  analogWrite(E1, x_char_vitesseM1); // vitesse moteur 1
  analogWrite(E2, x_char_vitesseM2); // vitesse moteur 2
}

float MiseEnFormeAcceleration(int16_t x_int16_TCNT)
{
  float l_float_result = x_int16_TCNT;
  l_float_result = l_float_result - 195; // On soustrait la valeur en position 0 du joystick
  l_float_result = l_float_result / 26; // On divise par la valeur maximum
  if ((l_float_result > -0.16) && (l_float_result < 0.16)) // On enleve le bruit du capteur 
  {
    l_float_result = 0;
  }
  if (l_float_result > 1) //Limitation aux valeurs maximums souhaitées
  {
    l_float_result = 1;
  }
  if (l_float_result < -1) //Limitation aux valeurs maximums souhaitées
  {
    l_float_result = -1;
  }
  return (l_float_result);
}

float MiseEnFormeDirection(int16_t x_int16_TCNT) // Meme procédure que pour toutes les mises en formes 
{
  float l_float_result = x_int16_TCNT;
  l_float_result = l_float_result - 195;
  l_float_result = -(l_float_result / 25);
  if ((l_float_result > -0.1) && (l_float_result < 0.1))
  {
    l_float_result = 0;
  }
  if (l_float_result > 1)
  {
    l_float_result = 1;
  }
  if (l_float_result < -1)
  {
    l_float_result = -1;
  }
  return (l_float_result);
}

void InitInterupt1Et3(void)
{
  noInterrupts(); // disable all interrupts
  EIMSK = 0x0C;
  EICRA = 0xF0; // Fronts montants pour INT2 et 3
  interrupts(); // enable all interrupts
}

void ApplicationMouvement(float x_float_ResultACC, float x_float_ResultDirec, float x_float_Inclinaison, float x_float_DistAv, float x_float_DistAr)
{

  int M1 = 4; // Contrôle direction moteur 1
  int M2 = 7; // Contrôle direction moteur 2
  float l_float_VChenilleG = 0;
  float l_float_VChenilleD = 0;
  float l_float_Provisoir = 0;
  float l_float_Provisoir2 = 0;
  l_float_Provisoir = x_float_ResultACC;
  if (l_float_Provisoir > 0) // On regarde si on souhaite avancer ou reculer et on affecte le sens des moteurs
  {
    digitalWrite(M1, HIGH); // sens moteur 1
    digitalWrite(M2, HIGH); // sens moteur 2
  }
  else if (l_float_Provisoir < 0)
  {
    digitalWrite(M1, LOW); // sens moteur 1
    digitalWrite(M2, LOW); // sens moteur 2
    l_float_Provisoir = -l_float_Provisoir; 
  }

  if (x_float_ResultDirec < 0) // si on veux aller a gauche alors on reduit la vitesse de la chenille droite
  {
    l_float_Provisoir2 = 1 - (-x_float_ResultDirec);
    l_float_VChenilleD = l_float_Provisoir2 * 255 * l_float_Provisoir;
    l_float_VChenilleG = l_float_Provisoir * 255;
  }
  else if (x_float_ResultDirec > 0)// On reduit la vitesse de la chenille gauche
  {
    l_float_Provisoir2 = 1 - x_float_ResultDirec;
    l_float_VChenilleD = l_float_Provisoir * 255;
    l_float_VChenilleG = l_float_Provisoir2 * 255 * l_float_Provisoir;
  }
  else // pas de direction donc meme vitesse pour les deux chenilles
  {
    l_float_VChenilleG = l_float_Provisoir * 255;
    l_float_VChenilleD = l_float_Provisoir * 255;
  }

  if ((l_float_Provisoir == 0) && (x_float_DistAv >= 0.5) && (x_float_DistAr >= 0.5)) // Si on veux tourner sur place 
  {
    if (x_float_ResultDirec < 0) // Pour tourner sur place on met une chenille dans un sens et une dans l'autre
    {
      l_float_Provisoir2 = -x_float_ResultDirec;
      digitalWrite(M1, HIGH); // sens moteur 1
      digitalWrite(M2, LOW);  // sens moteur 2
      l_float_VChenilleG = l_float_Provisoir2 * 255;
      l_float_VChenilleD = l_float_Provisoir2 * 255; 
    }
    else if (x_float_ResultDirec > 0)
    {
      l_float_Provisoir2 = x_float_ResultDirec;
      digitalWrite(M1, LOW);  // sens moteur 1
      digitalWrite(M2, HIGH); // sens moteur 2
      l_float_VChenilleG = l_float_Provisoir2 * 255;
      l_float_VChenilleD = l_float_Provisoir2 * 255;
    }
  }

  if (x_float_DistAv < 0.5)// Si on est proche d'un obstacle a l'avant alors on force a reculer
  {
    digitalWrite(M1, LOW); // sens moteur 1
    digitalWrite(M2, LOW); // sens moteur 2
    l_float_VChenilleG = l_float_VChenilleG * x_float_Inclinaison * 0.5;// on reduit la vitesse par deux car on est proche d'un obstacle
    l_float_VChenilleD = l_float_VChenilleD * x_float_Inclinaison * 0.5; 
  }
  else if (x_float_DistAr < 0.5)// Si on est proche d'un obstacle a l'arrière alors on force a avancer
  {
    digitalWrite(M1, HIGH); // sens moteur 1
    digitalWrite(M2, HIGH); // sens moteur 2
    l_float_VChenilleG = l_float_VChenilleG * x_float_Inclinaison * 0.5;// on reduit la vitesse par deux car on est proche d'un obstacle
    l_float_VChenilleD = l_float_VChenilleD * x_float_Inclinaison * 0.5;
  }
  else// Ici on est a distance résonable d'un obstacle alors on reduit juste sa vitesse proportionnellement a la distance avec l'objet
  {
    l_float_VChenilleG = l_float_VChenilleG * x_float_Inclinaison * x_float_DistAr * x_float_DistAv;
    l_float_VChenilleD = l_float_VChenilleD * x_float_Inclinaison * x_float_DistAr * x_float_DistAv;
  }
  avancer(l_float_VChenilleG, l_float_VChenilleD); // On applique aux moteurs
}


float getDistance(uint8_t x_uint8_pin)
{
  int sensor_value = 0;
  int sum = 0;
  // read the analog in value:
  for (int i = 0; i < 20; i++) // On mesure 20 fois pour plus de précision
  {
    sensor_value = analogRead(x_uint8_pin);
    sum += sensor_value;
  }
  sensor_value = sum / 20;
  float voltage;
  voltage = (float)sensor_value * ADC_REF / 1024;
  return voltage;
}

BMI088 bmi088(BMI088_ACC_ADDRESS, BMI088_GYRO_ADDRESS);

float getAngle(void)
{
  float ax = 0, ay = 0, az = 0;
  bmi088.getAcceleration(&ax, &ay, &az);
  float inclination = 180.0 * acos(az / sqrt(ax * ax + ay * ay + az * az)) / M_PI; // Formule qui converties les accélerations en un angle
  return (inclination);
}

void InitAngle(void)
{
  Wire.begin();
  Serial.begin(9600);
  while (1)
  {
    if (bmi088.isConnection())
    {
      bmi088.initialize();
      break;
    }
    delay(2000);
  }
}

float MiseEnFormeInclinaison(int16_t x_uint16_Valcapteur)// Meme procédure que pour toutes les mises en formes 
{
  float l_float_Incl;
  if (x_uint16_Valcapteur > 90)
  {
    x_uint16_Valcapteur = 90;
  }
  if (x_uint16_Valcapteur <= 10)
  {
    x_uint16_Valcapteur = 0;
  }
  l_float_Incl = (1 - ((float)x_uint16_Valcapteur / 90.0));
  if (l_float_Incl <= 0.4)
  {
    l_float_Incl = 0.4;
  }
  return (l_float_Incl);
}

float MiseEnFormeDistance(float x_float_Valcapteur)// Meme procédure que pour toutes les mises en formes 
{
  float l_float_Dist;
  if (x_float_Valcapteur < 0.5)
  {
    x_float_Valcapteur = 0;
  }
  l_float_Dist = 1 - ((x_float_Valcapteur / 4));
  if (l_float_Dist < 0.5)
  {
    l_float_Dist = 0;
  }

  return (l_float_Dist);
}

CConvAN FonctionsPre;

void InitLumiere(void)
{

  FonctionsPre.InitCan16(1); // ADC 1 correspondant à la pin A4
  DDRB = 0xA0;               // PB7 en sortie

  // utilisation du timer 0 pour la PWM, par le biais de OC0A
  TCCR0A = 0B10000011; // FAST PWM
  TCCR0B = 0B00000100;

  OCR0A = 255; //Rapport cyclique
}

void Lumiere(void)
{

  float val = (float)FonctionsPre.ConvAN16();
  val = (100 - val / 10) / 100;

  val = ((int)(val * (float)255)); // PWM variable, commande led

  if (val < 125.00) //Seuil ou on eteint totalement la lampe 
  {
    OCR0A = 0;
  }
  else if (val > 225) // Seuil ou on allume la lampe a fond
  {
    OCR0A = 255;
  }
  else
  {
    OCR0A = (int)(255 * (float)(1 - (225 - val) / 110)); // Allumage progressif de la lampe en fonction de la luminosité
  }
}

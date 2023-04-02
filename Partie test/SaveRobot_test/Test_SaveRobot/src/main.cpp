#include <global.h>

bool var = true;  //-> premier rising edge
bool var2 = true; //-> premier rising edge
float g_float_resultat = 0;

BMI088 bmi089(BMI088_ACC_ADDRESS, BMI088_GYRO_ADDRESS);

// Standard PWM DC control
int E1 = 5; // M1 Speed Control
int E2 = 6; // M2 Speed Control
int M1 = 4; // M1 Direction Control
int M2 = 7; // M1 Direction Control

typedef enum
{
  Init,
  Moteurs,
  Ampoule,
  IRCapteurs,
  Photoresistance,
  Communication,
  Buzzer,
  Accelerometre,
  Global
} TypeTest;

TypeTest m_test;

bool g_bool_BP1;
char g_char_var;
bool varBuzz = true;
bool var3 = true; //-> premier
bool varAmp = true;
int temp;
int tempAmp;
int sensor_value = 0;
int sum = 0;
float voltage;
int tempBuzz;

// programme global
float g_float_ResultACC = 0;
float g_float_ResultDirec = 0;
bool varISR = true;  //-> premier rising edge
bool varISR2 = true; //-> premier rising edge
int g_int_ValButton = 0;

void setup1()
{
  InitAngle();
  InitMouvements();
  InitReste();
  InitInterupt1Et3();
  InitTimer1();
  InitTimer3();
  InitLumiere();
}

void loop1()
{
  g_int_ValButton = pulseIn(A0, HIGH, 50000); // Temps a l'état haut du bouton
  if (g_int_ValButton > 1500)
  {
    DDRB = 0xA0;  // Si le bouton est activé alors on allume le timer
    PORTB = 0x20; // On assure le coup en mettant le port en sortie et en coupant le
  }
  else
  {
    PORTB = 0x00; // On assure le coup en mettant le port en sortie et en metant le port a 0
    DDRB = 0x80;  // mais ce n'est pas forcement nécessaire
  }
  // On applique le mouvement avec toutes les informations
  ApplicationMouvement(g_float_ResultACC, g_float_ResultDirec, MiseEnFormeInclinaison(getAngle()), MiseEnFormeDistance(getDistance(A1)), MiseEnFormeDistance(getDistance(A2)));
}

void Reset(void)
{
  // INIT Moteurs
  var3 = true;
  analogWrite(E1, 0); // PWM Speed Control
  digitalWrite(M1, HIGH);
  analogWrite(E2, 0); // PWM Speed Control
  digitalWrite(M2, HIGH);

  // INIT Ampoule
  //OCR0A = 255;
  varAmp = true;
  tempAmp = 0;
  PORTB = PORTB & 0x7F;

  // INIT IRCapteurs

  // INIT Buzzer
  varBuzz = true;
  tempBuzz = 0;
}

void setup()
{
  m_test = Init;
  InitMouvements();
  DDRD = 0x00; // d12 en entrée
  DDRC = 0x80; // d13 en sortie
  DDRB = 0xA0; // d11 en sortie -> Ampoule + Buzzer
  Serial.begin(9600);
  InitTimer1();
  InitTimer3();
  InitInterupt1Et3();

  InitAngle();
  /*
  // Init lumière
  //  utilisation du timer 0 pour la PWM, par le biais de OC0A
  TCCR0A = 0B10000011; // FAST PWM
  TCCR0B = 0B00000100;
  */
  Reset();
}

void loop()
{
  Serial.println(m_test);
  /*
  if (var3){
    temp = millis();
    var3=!var3;
  }


  if ((millis()-temp)>500){
    Serial.println(m_test);
    var3=!var3;
  }
  */
  if (Serial.available())
  {
    g_char_var = Serial.read();

    if (g_char_var == 'A')
    {
      m_test = Init;
      Reset();
    }
    else if (g_char_var == 'B')
    {
      m_test = Moteurs;
      Reset();
    }
    else if (g_char_var == 'C')
    {
      m_test = Ampoule;
      Reset();
    }
    else if (g_char_var == 'D')
    {
      m_test = IRCapteurs;
      Reset();
    }
    else if (g_char_var == 'E')
    {
      m_test = Photoresistance;
      Reset();
    }
    else if (g_char_var == 'F')
    {
      m_test = Communication;
      Reset();
    }
    else if (g_char_var == 'G')
    {
      m_test = Buzzer;
      Reset();
    }
    else if (g_char_var == 'H')
    {
      m_test = Accelerometre;
      Reset();
    }
    else if (g_char_var == 'I')
    {
      m_test = Global;
      Reset();
    }
    else if (g_char_var == 'X')
    {
      m_test = Init;
      Reset();
    }
  }

  switch (m_test)
  {
  case Init:
    // mettre seulement une entrée à 1 via l'automate (D12), et ressort à 1 sur une sortie de l'aurduino prise par l'automate (D13)
    // OU RIEN METTRE
    // PORTC = PORTC | (PIND & 0x80);

    break;

  case Moteurs:
    // 2 modes de fonctionnement : V1 et V2 -> bloquant pas grave (ou autre graphe d'état)

    if (var3)
    {
      temp = millis();
      var3 = !var3;
    }

    /*noInterrupts(); // disable all interrupts
    EIMSK = 0x0C;
    EICRA = 0xF0; // Fronts montants pour INT2 et 3
    interrupts(); // enable all interrupts*/
    if ((millis() - temp) < 1000)
    {
      analogWrite(E1, 255); // PWM Speed Control
      digitalWrite(M1, HIGH);
      analogWrite(E2, 255);
      digitalWrite(M2, HIGH);
    }

    else if ((millis() - temp) < 2000)
    {
      analogWrite(E1, 255); // PWM Speed Control
      digitalWrite(M1, LOW);
      analogWrite(E2, 255);
      digitalWrite(M2, LOW);
    }

    else if ((millis() - temp) < 3000)
    {
      analogWrite(E1, 255); // PWM Speed Control
      digitalWrite(M1, HIGH);
      analogWrite(E2, 255);
      digitalWrite(M2, LOW);
    }

    else if ((millis() - temp) < 4000)
    {
      analogWrite(E1, 255); // PWM Speed Control
      digitalWrite(M1, LOW);
      analogWrite(E2, 255);
      digitalWrite(M2, HIGH);
    }

    else if ((millis() - temp) < 5000)
    {
      for (int i = 0; i < 255; i++)
      {
        analogWrite(E1, i); // PWM Speed Control
        digitalWrite(M1, HIGH);
        analogWrite(E2, i);
        digitalWrite(M2, HIGH);
        delay(4);
      }
    }

    else
    {
      analogWrite(E1, 255); // PWM Speed Control
      digitalWrite(M1, HIGH);
      analogWrite(E2, 255);
      digitalWrite(M2, HIGH);
    }

    break;

  case Ampoule: // D11

    // DONE

    // vérification visuelle, programme : allumage progressif de l'ampoule puis tension maximale pdt 5 secondes puis extinction
    // PWM
    PORTB = PORTB | 0x80 ;
    /*
    if (varAmp)
    {
      temp = millis();
      varAmp = !varAmp;
    }

    if ((millis() - temp) > 11) // 2805 ms (11*255)
    {
      if (tempAmp < 255)
      {
        tempAmp++;
        OCR0A = tempAmp;
      }
      else
      {
        OCR0A = 255;
      }
    }
    Serial.println(OCR0A);
    */
    break;

  case IRCapteurs:

    // rien car information directement sur l'automate

    // mise en place de la tension de sortie sur une pin étant connecté à l'automate
    // vérification graphique LabView, pin connecté à l'automate

    break;

  case Photoresistance:
    // rien car information directement sur l'automate

    break;
  case Communication:
    // rien car information directement sur l'automate
    // vérification graphique LabView, pins connecte a l'automate

    break;
  case Buzzer:
    // son PWM continu mesurer à l'aide d'un micro
    // a changer

    if (varBuzz)
    {
      tempBuzz = millis();
      varBuzz = !varBuzz;
    }

    if ((millis() - tempBuzz) > 1500)
    {
      DDRB = 0xA0;  // Si le bouton est activé alors on allume le timer 1010 0000
      PORTB = 0x20; // On assure le coup en mettant le port en sortie et en coupant le 0010 0000
      varBuzz = !varBuzz;
    }
    else
    {
      PORTB = 0x00; // On assure le coup en mettant le port en sortie et en metant le port a 0  0000 0000
      DDRB = 0x80;  // mais ce n'est pas forcement nécessaire 1000 0000
    }

    break;

  case Accelerometre:
    // vérification graphique LabView, pins connecté à l'automate
    float ax = 0, ay = 0, az = 0;
    bmi089.getAcceleration(&ax, &ay, &az);
    float inclination = 180.0 * acos(az / sqrt(ax * ax + ay * ay + az * az)) / M_PI; // Formule qui converties les accélerations en un angle
    // TODO :faire un retour sur une PIN
    break;
  case Global:
    // test en 2 fois, 1ère fois : communication, 2ème fois : tout le reste
    // tous les tests sont effectués à la suite
    setup1();
    loop1();
    break;
  default:
    break;
  }
}

ISR(INT3_vect) // interruption canal 1 correspond a l'accélération
{
  if (m_test == Global)
  {
    if (varISR) // on utilise la variable afin de chercher un front montant puis un descendant
    {
      TCNT1 = 3036;
      EICRA = EICRA & 0xBF; // falling edge
      varISR = !varISR;
    }
    else
    {
      EICRA = EICRA | 0x40; // rising edge
      varISR = !varISR;
      g_float_ResultACC = (MiseEnFormeAcceleration(TCNT1)); // On traite la valeur afin d'avoir quelque chose en par exemple entre -1 et 1;
    }
  }
}

ISR(INT2_vect) // Meme procéder que pour l'accéleration mais avec le timer 3. Ici on mesure le joystick de direction
{
  if (m_test == Global)
  {
    if (varISR2)
    {
      TCNT3 = 3036;
      EICRA = EICRA & 0xEF; // falling edge
      varISR2 = !varISR2;
    }
    else
    {
      EICRA = EICRA | 0x10; // rising edge
      varISR2 = !varISR2;
      g_float_ResultDirec = (MiseEnFormeDirection(TCNT3)); // On traite la valeur afin d'avoir quelque chose en par exemple entre -1 et 1;
    }
  }
}
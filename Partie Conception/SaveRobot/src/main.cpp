#include <MesFonctions.h>

float g_float_ResultACC = 0;
float g_float_ResultDirec = 0;
bool var = true;  //-> premier rising edge
bool var2 = true; //-> premier rising edge
int g_int_ValButton = 0;

void setup()
{
    InitAngle();
    InitMouvements();
    InitReste();
    InitInterupt1Et3();
    InitTimer1();
    InitTimer3();
    InitLumiere();
}
CConvAN a;
void loop()
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

ISR(INT3_vect) // interruption canal 1 correspond a l'accélération
{
    if (var) // on utilise la variable afin de chercher un front montant puis un descendant
    {
        TCNT1 = 3036;
        EICRA = EICRA & 0xBF; // falling edge
        var = !var;
    }
    else
    {
        EICRA = EICRA | 0x40; // rising edge
        var = !var;
        g_float_ResultACC = (MiseEnFormeAcceleration(TCNT1)); // On traite la valeur afin d'avoir quelque chose en par exemple entre -1 et 1;
    }
}

ISR(INT2_vect) // Meme procéder que pour l'accéleration mais avec le timer 3. Ici on mesure le joystick de direction
{
    if (var2)
    {
        TCNT3 = 3036;
        EICRA = EICRA & 0xEF; // falling edge
        var2 = !var2;
    }
    else
    {
        EICRA = EICRA | 0x10; // rising edge
        var2 = !var2;
        g_float_ResultDirec = (MiseEnFormeDirection(TCNT3)); // On traite la valeur afin d'avoir quelque chose en par exemple entre -1 et 1;
    }
}

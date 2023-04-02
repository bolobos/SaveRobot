#pragma once
#ifndef __MesFonctions_h_
#define __MesFonctions_h_
#include <Arduino.h>
// #include <GEIIutil.h>
#include "Ultrasonic.h" // pour la gestion des capteurs à ultrasons
#include "BMI088.h" // Utilisation du giroscope
#include "Wire.h"
#define MSK_VERIF 0x20

#define ADC_REF 5
#define IR_PROXIMITY_SENSOR A1





#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)



/**
 * @brief class de fonctions pour la can
 * @author David Cartier
 *
 */
class CConvAN
{
public:
    /**
     * @brief Initialise le CAN pour utilisation
     *
     */
    void InitCan8(void);

    /**
     * @brief retourne la valeur de la CAN de 0 à 255
     *
     */
    uint8_t ConvAN8(void);

    uint16_t ConvAN16(void);

    void InitCan16(int x_int_adcport);

private:
};

/**
 * @brief class des différentes fonctions nécessaires pour la liaison série
 *
 */
class LiaisonSerie
{
public:
    /**
     * @brief
     *
     */
    void LiaisonSerie::InitCar();

    /**
     * @brief
     *
     */
    char LiaisonSerie::litCar();

    /**
     * @brief
     *
     */
    void LiaisonSerie::ecritCar(char x_char_c);
};



void InitTimer3(void);
void InitTimer1(void);

void InitInterupt1Et3(void);
void InitMouvements(void);
void InitReste(void);

void avancer(char x_char_vitesseM1, char x_char_vitesseM2);

float MiseEnFormeAcceleration(int16_t x_int16_TCNT);
float MiseEnFormeDirection(int16_t x_int16_TCNT);
void ApplicationMouvement(float x_float_ResultACC, float x_float_ResultDirec,float x_float_Inclinaison,float x_float_DistAv,float x_float_DistAr);

float MiseEnFormeInclinaison(int16_t x_uint16_Valcapteur);
float MiseEnFormeDistance(float x_float_Valcapteur);



float getDistance(uint8_t x_uint8_pin);
float getAngle(void);
void InitAngle(void);
void InitLumiere(void);
void Lumiere(void);



#endif
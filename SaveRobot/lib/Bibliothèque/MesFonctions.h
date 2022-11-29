#ifndef __MesFonctions_h_
#define __MesFonctions_h_
#include <Arduino.h>
//#include <GEIIutil.h>
#include "Ultrasonic.h" // pour la gestion des capteurs à ultrasons
#include "Grove_LED_Bar.h" // led sensor

#define MSK_VERIF 0x20

#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)

/**
 * @brief class de fonctions pour la can
 * @author David Cartier
 * 
 */
class CConvAN{
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

        void InitCan16(void);


    private:
};

/**
 * @brief class des différentes fonctions nécessaires pour la liaison série
 * 
 */
class LiaisonSerie{
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

#endif
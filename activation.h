#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "config.h"
#include "led.h"
#include "maze.h"

namespace activation{
    extern bool isOnGoodSide;
    extern unsigned long timeElapsed;
  
    //State 1 - Activation
    // Se connecter au serveur pour activer la machine (LED rouges vont clignoter lentement)
    extern String json_act_1;
    extern Adafruit_MPU6050* mpu;

    void initAct();
    void loopAct();
    // Mettre le cube "droit" pour allumer les LED vertes
}

#endif

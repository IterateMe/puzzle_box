#ifndef ACTIVATION_CPP
#define ACTIVATION_CPP

#include "activation.h"

bool activation::isOnGoodSide = false;

//State 1 - Activation
// Se connecter au serveur pour activer la machine (LED rouges vont clignoter lentement)

//String activation::json_act_1 = "<p><button id='button' class='button' onclick='activation_turnOn()' >Toggle TEST</button></p>";

unsigned long activation::timeElapsed = 0;

Adafruit_MPU6050* activation::mpu = new Adafruit_MPU6050();

void activation::initAct(){
    if (!activation::mpu->begin()) {
      Serial.println("Failed to find MPU6050 chip");
      while (1) {
        delay(10);
      }
    }
    activation::mpu->setAccelerometerRange(MPU6050_RANGE_2_G);
  }

void activation::loopAct(){
    sensors_event_t a, g, temp;
    mpu->getEvent(&a, &g, &temp);
    if(a.acceleration.x > 9){
      if((millis()-timeElapsed) > 2000){
        isOnGoodSide = true;
        }
     Serial.println("Wait for it!");
    }else{
      timeElapsed = millis();
      isOnGoodSide = false;
    }
    if(isOnGoodSide){
      led::green();
      configu::currentState = 2;
      maze::startMaze();
    }else{
      led::red();
    }
  }

// Mettre le cube "droit" pour allumer les LED vertes
    


#endif

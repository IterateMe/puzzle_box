#include "config.h"
#include "led.h"
#include "activation.h"
#include "network.h"
#include "maze.h"

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(configu::ledPin, OUTPUT);
  pinMode(configu::pinInput_1, INPUT);
  digitalWrite(configu::ledPin, LOW);
  
  //Manage interrupts
  attachInterrupt(digitalPinToInterrupt(configu::pinInput_1), network::updateCLient, CHANGE);
  
  //Initiate SPIFFS
  if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
  }
  
  activation::initAct();
  network::initNetwork();
  led::initLed();
}

void loop() {
  //modules
  switch(configu::currentState){
    case 0:
      Serial.println("STATE 0");
      delay(1000);
      led::off();
      break;
      
    case 1:
      activation::loopAct();
      break;
      
    case 2:
      
      break;
      
    default:
      Serial.println("ERROR");
      delay(1000);
  }

  //Global
  network::loopNetwork();
  led::loopLed();
  digitalWrite(configu::ledPin, configu::ledState);
}

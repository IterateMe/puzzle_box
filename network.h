#ifndef NETWORK_H
#define NETWORK_H

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "config.h"
#include "activation.h"

namespace network{

    extern AsyncWebServer* server; // server(80);
    extern AsyncWebSocket* ws;     //ws("/ws");
  
    void notifyClients();
    
    ICACHE_RAM_ATTR void updateCLient();
    
    void handleWebSocketMessage(AsyncWebSocketClient *client, void *arg, uint8_t *data, size_t len);
    
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                 void *arg, uint8_t *data, size_t len);
    
    void initWebSocket();
    
    String processor(const String& var);

    void initNetwork();

    void loopNetwork();

}

#endif

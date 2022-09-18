#ifndef NETWORK_CPP
#define NETWORK_CPP

#include "network.h"



AsyncWebServer* network::server = new AsyncWebServer(80);    // server(80);
AsyncWebSocket* network::ws = new AsyncWebSocket("/ws");     //ws("/ws");


void network::notifyClients(){
    String a = "{\"one\":\"";
    String c = "\"}";
    ws->textAll(a+activation::json_act_1+c);
}

ICACHE_RAM_ATTR void network::updateCLient(){
      Serial.println("Interrupt");
      configu::ledState = !configu::ledState;
      //notifyClients();
      //ws->textAll("");
    }


void  network::handleWebSocketMessage(AsyncWebSocketClient *client, void *arg, uint8_t *data, size_t len) {
      AwsFrameInfo *info = (AwsFrameInfo*)arg;
      if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        data[len] = 0;

        
        //Serial.println((char*)data);
        
        // FROM THE EXEMPLE
        //if (strcmp((char*)data, "toggle") == 0) {
          //Serial.println((char*)data);
          //configu::ledState = !configu::ledState;
        //}
        
        // ACTIVATION PHASE
        if (strcmp((char*)data, "activation_On") == 0) {
           Serial.println("Activation Starting");
          //configu::ledState = !configu::ledState;
          configu::currentState = 1;
        }
        if (strcmp((char*)data, "maze_on") == 0) {
          //configu::ledState = !configu::ledState;
          Serial.println("Maze Starting");
        }
        
      }
    }
    
void network::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                 void *arg, uint8_t *data, size_t len) {
        switch (type) {
          case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;
          case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
          case WS_EVT_DATA:
            handleWebSocketMessage(client, arg, data, len);
            break;
          case WS_EVT_PONG:
          case WS_EVT_ERROR:
            break;
      }
    }
    
    
void network::initWebSocket() {
  ws->onEvent(onEvent);
  server->addHandler(ws);
}

 String network::processor(const String& var){
    //If need to initiate a variable to any value at loading
      return String();
    }

void network::initNetwork(){
    WiFi.begin(configu::ssid, configu::password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi..");
    }
  
    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());
  
    network::initWebSocket();
  
    // Route for root / web page
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/index.html", String(), false, processor);
    });
  
    // Start server
    server->begin(); 
}

void network::loopNetwork(){
  ws->cleanupClients();
}

#endif

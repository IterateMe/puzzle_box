// Includes
#include <ESP8266WiFi.h>
#include <DNSServer.h> 
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// User configuration
#define SSID_NAME "Puzzle Box"
#define LED D0

// Init System Settings
const byte HTTP_CODE = 200;
const byte DNS_PORT = 53;
const byte TICK_TIMER = 1000;
IPAddress APIP(172, 0, 0, 1); // Gateway

unsigned long lastActivity=0, lastTick=0, tickCtr=0;
DNSServer dnsServer; 
AsyncWebServer  webServer(80);
AsyncWebSocket ws("/ws");

bool ledState = 0;

class CaptiveRequestHandler : public AsyncWebHandler {
  public:
    CaptiveRequestHandler() {
      /* THIS IS WHERE YOU CAN PLACE THE CALLS */
//        webServer.onNotFound([](AsyncWebServerRequest *request){
//        AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/NotFound.html", "text/html");
//        request->send(response);
//       });

        webServer.on("/maxWchix", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/maxWchix.jpg", "image/jpg");
        request->send(response); Serial.println("Send image_1");});

        webServer.on("/lips1", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/lips1.jpg", "image/jpg");
        request->send(response); Serial.println("Send image_2");});
      
    }
    virtual ~CaptiveRequestHandler() {}
    
    static String processor(const String& var){
      Serial.println(var);
      if(var == "STATE"){
        if (ledState){
          return "ON";
        }
        else{
          return "OFF";
        }
      }
      return String();
    }
    
    bool canHandle(AsyncWebServerRequest *request) {
      //request->addInterestingHeader("ANY");
      return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/index.html", String(), false);
      Serial.println("Index sent");
    }
};

void notifyClients() {
  ws.textAll(String(ledState));
  Serial.print("clients notified");
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  Serial.println("Message received");
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "toggle") == 0) {
      ledState = !ledState;
      notifyClients();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        Serial.printf("WebSocket data received from #%u \n", client->id());
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  webServer.addHandler(&ws);
  Serial.println("Web socket intitiated");
}

void setup() {
  Serial.begin(115200);
  Serial.println("");
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID_NAME);
  
  dnsServer.start(DNS_PORT, "*", APIP); // DNS spoofing (Only HTTP)

  webServer.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP

  initWebSocket();
  webServer.begin();
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.println("SETUP COMPLETED");
}


void loop() { 
  ws.cleanupClients();
  dnsServer.processNextRequest();
  digitalWrite(BUILTIN_LED, ledState);
}

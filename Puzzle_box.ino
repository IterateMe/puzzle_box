// ESP8266 WiFi Captive Portal
// By 125K (github.com/125K)

// Includes
#include <ESP8266WiFi.h>
#include <DNSServer.h> 
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// User configuration
#define SSID_NAME "Dr Beaudoin Dermatologue"

// Init System Settings
const byte HTTP_CODE = 200;
const byte DNS_PORT = 53;
const byte TICK_TIMER = 1000;
IPAddress APIP(172, 0, 0, 1); // Gateway

unsigned long lastActivity=0, lastTick=0, tickCtr=0;
DNSServer dnsServer; 
AsyncWebServer  webServer(80);


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
        request->send(response);});

        webServer.on("/lips1", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/lips1.jpg", "image/jpg");
        request->send(response);});
      
    }
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request) {
      //request->addInterestingHeader("ANY");
      return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/index.html", String(), false);
    }
};

void setup() {
  if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
  }
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID_NAME);
  
  dnsServer.start(DNS_PORT, "*", APIP); // DNS spoofing (Only HTTP)

  webServer.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  
  webServer.begin();
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
}


void loop() { 
  dnsServer.processNextRequest();
}

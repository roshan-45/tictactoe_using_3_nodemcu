#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Keypad.h>

// Set your access point network credentials
const char* ssid = "tic-tak-toe";
const char* password = "123456789";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const byte n_rows = 4;
const byte n_cols = 4;

char keys[n_rows][n_cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte colPins[n_rows] = {D3, D2, D1, D0};
byte rowPins[n_cols] = {D7, D6, D5, D4};

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols); 

int matrix[9] = {0,0,0,0,0,0,0,0,0};
 char prev_key='z';
int count=0;

void setup(){
  // Serial port for debugging purposes

  
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Start the server
  server.begin();
}

void loop(){
  char myKey = myKeypad.getKey();

  if (myKey != NO_KEY and myKey!=prev_key){
    Serial.print("Previously pressed: ");
    Serial.println(prev_key);
    prev_key = myKey;
    count+=1;
    Serial.print("Key pressed: ");
    Serial.println(myKey);
    server.on("/board", HTTP_GET, [myKey](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", String(myKey).c_str());
    });
  }

  // Handle incoming client requests
  //server.handleClient();
}

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

#include <Wire.h>

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

 // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

int methane;



void setup(){
  // Serial port for debugging purposes
  Serial.begin(9600);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/methane", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(methane).c_str());
  });


  
  
  // Start server
  server.begin();
}
 
void loop(){
  methane = analogRead(A0);
  
}
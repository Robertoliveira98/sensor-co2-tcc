#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include "MHZ19.h"

//constantes medições e requisições
const long medicaoDelay = 10000;
const String authorizationId = "610102bde69bd84020a30f52";


const char* ssid = "roberto";
const char* password = "87890719";
const int rx_pin = 13; //Serial rx pin no
const int tx_pin = 15; //Serial tx pin no


//url api e ssl
const char* serverName = "https://www.dcc.ufrrj.br/co2-api/inserir";
const char fingerprint[] PROGMEM = "0D 54 90 90 C1 03 A8 9A 43 B0 86 41 91 82 79 4D 49 B7 77 71";


MHZ19 *mhz19_uart = new MHZ19(rx_pin,tx_pin);


void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado à rede WiFi com endereço IP: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Intervalo de medições em ms:");
  Serial.println(medicaoDelay);

  mhz19_uart->begin(rx_pin, tx_pin);
  mhz19_uart->setAutoCalibration(false);
  delay(3000); // Issue #14
  Serial.print("MH-Z19 status:");
  Serial.println(mhz19_uart->getStatus());
  delay(1000);
  
}

void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClientSecure client;
    HTTPClient http;

    client.setFingerprint(fingerprint);
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", authorizationId); 

    //medidor
    measurement_t m = mhz19_uart->getMeasurement();
         
    int httpResponseCode = http.POST("{\"medicao\":\""+(String)m.co2_ppm+"\",\"idSensor\":\""+authorizationId+"\",\"ambiente\":{\"nome\":\"teste-roberto\",\"id\":\"teste1\"}}");

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
      
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  delay(medicaoDelay);
}

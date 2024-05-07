//channel id : 2226105
//channel api key : 5ZZNFKTB60NEJIV9

#include <WiFi.h>
#include "DHTesp.h"
#include "ThingSpeak.h"

unsigned long agora = 0;
float randNumber_temperature = 0;
float randNumber_humidity = 0 ;

//const int DHT_PIN = 3;
const int LED_PIN = 2;

const char* WIFI_NAME = "Winter is Coming";  // SSID WiFi
const char* WIFI_PASSWORD = "1moreove";      // Senha 

const int myChannelNumber =2534697;          // Número canal
const char* myApiKey = "3MCRSZ4RA6KSAIPW";   // Api Key do canal
const char* server = "api.thingspeak.com";

//DHTesp dhtSensor;
WiFiClient client;

void setup() {
  Serial.begin(115200);

//  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
//  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Wifi not connected");
  }
  Serial.println("Wifi connected !");
  Serial.println("Local IP: " + String(WiFi.localIP()));
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop() {
 // TempAndHumidity  data = dhtSensor.getTempAndHumidity();
 //  ThingSpeak.setField(1,data.temperature);
 //  ThingSpeak.setField(2,data.humidity);


 // Gera valores aleatórios entre 10 e 34
 randNumber_temperature = random(10, 35);

// Gera valores aleatórios entre 70 e 89
 randNumber_humidity = random(70, 90);

   ThingSpeak.setField(1,randNumber_temperature);
   ThingSpeak.setField(2,randNumber_humidity);

  if (randNumber_temperature > 0 || randNumber_temperature < 50 && randNumber_humidity > 10 || randNumber_humidity < 100) {  // || OR lógico
    digitalWrite(LED_PIN, HIGH);
  }else{
   digitalWrite(LED_PIN, LOW);
  }
  
  int x = ThingSpeak.writeFields(myChannelNumber,myApiKey);
  
  Serial.println("Temp: " + String(randNumber_temperature, 1) + "°C");
  Serial.println("Humidity: " + String(randNumber_humidity, 2) + "%");
  
  if(x == 200){
    Serial.println("Data pushed successfull");
  }else{
    Serial.println("Push error" + String(x));
  }
  Serial.println("---");

  agora = millis();
  while(millis() < agora + 20000) {
    // Pausa de 20 segundos. Nada a fazer
  }
}
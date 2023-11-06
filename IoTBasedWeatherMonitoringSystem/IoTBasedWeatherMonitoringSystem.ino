#include <DHT.h>  
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

  
#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char * myWriteAPIKey = "NXRMK8FMF0B8GB25";

const char* ssid =  "GlobeAtHome_f63e0_2.4";     // replace with your wifi ssid and wpa2 key
const char* pass =  "UCkm6adj";
unsigned long myChannelNumber = 2254018;

WiFiClient client;

int Temperature;
int Humidity;

void setup() {
Serial.begin(9600);
   dht.begin();
ThingSpeak.begin(client);

       delay(10);
               
       Serial.println("Connecting to ");
       Serial.println(ssid); 
 
       WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 
  

}

void loop() {
      float humidity = dht.readHumidity();
      float  temperature = dht.readTemperature();
       temp();
       Serial.println(Temperature);
       ThingSpeak.writeField(myChannelNumber, 1, temperature , myWriteAPIKey);
       delay(1000);
       Serial.println(Humidity);
       ThingSpeak.writeField(myChannelNumber, 2, humidity , myWriteAPIKey);
       delay(1000);
  }



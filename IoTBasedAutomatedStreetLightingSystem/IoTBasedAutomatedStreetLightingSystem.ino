#include <ESP8266WiFi.h>
#include <ThingSpeak.h>


const int photocell = A0;

const int streetLight = D0;

const char * myWriteAPIKey = "BM9SXYM5W97BW413";

const char *ssid =  "GlobeAtHome_f63e0_2.4";     // replace with your wifi ssid and wpa2 key
const char *pass =  "UCkm6adj";

unsigned long myChannelNumber = 2262737;

WiFiClient client;

int ON = 1;
int OFF = 0;

void setup() {
Serial.begin(9600);
 pinMode(photocell, INPUT);
 pinMode(streetLight, OUTPUT);
 ThingSpeak.begin(client);
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
WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

}

void loop() {
int detect = analogRead(photocell);
Serial.println(detect);

if (detect < 100){
delay(100);
digitalWrite(streetLight, HIGH);
ThingSpeak.writeField(myChannelNumber, 1, ON , myWriteAPIKey);
}

if (detect > 600){
digitalWrite(streetLight, LOW);
ThingSpeak.writeField(myChannelNumber, 1, OFF , myWriteAPIKey);
}

}






#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ThingSpeak.h>

Servo servo1;
const int sensorPin = A0;
const int sensorPower = 5;
float threshold = 1024;
float percentage;
int DRY = 850;

int WET = 500;

const char * myWriteAPIKey = "LELQ5408BOD33C11";

const char *ssid =  "Carlo";     // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";

unsigned long myChannelNumber = 2262737;

WiFiClient client;



void setup() {
Serial.begin(9600);
  pinMode(sensorPower, OUTPUT);
  pinMode(sensorPin, INPUT);
	// Initially keep the sensor OFF
	digitalWrite(sensorPower, LOW);

	servo1.attach(D0);
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
  int getMoisturelvl = analogRead(sensorPin);
  percentage = ((getMoisturelvl / threshold) * 100);
	Serial.print("Analog output: ");
	Serial.println(percentage);
  //get the reading from the function below and print it

 if( getMoisturelvl > DRY){
     servo1.write(0);
    delay(100);
    ThingSpeak.writeField(myChannelNumber, 1, percentage , myWriteAPIKey);
    servo1.write(180);
  
  }
  if( (getMoisturelvl < DRY) && (getMoisturelvl > WET) ){
    delay(100);
    ThingSpeak.writeField(myChannelNumber, 2, percentage, myWriteAPIKey);
  }
  if( getMoisturelvl < WET  ){
    delay(100);
    ThingSpeak.writeField(myChannelNumber, 3, percentage, myWriteAPIKey);
  }

}






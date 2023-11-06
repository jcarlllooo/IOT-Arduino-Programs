#include <ESP8266WiFi.h>
#include <ThingSpeak.h>


const int buzzerPin = D0;
const int waterSensor = A0;

int sensorValue = 0;

int timer = 0;



const char *myWriteAPIKey = "Q5G9QV437A94RETH";

const char *ssid = "Carlo"; // replace with your wifi ssid and wpa2 key
const char *pass = "12345678";

unsigned long myChannelNumber = 2294437;

WiFiClient client;

void setup()
{
    Serial.begin(9600);
    ThingSpeak.begin(client);

  
    pinMode(buzzerPin, OUTPUT);
    pinMode(waterSensor, INPUT);
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

void loop()
{
  

int water = analogRead(waterSensor);

 int level = water*100/1024; 
 Serial.print("Sensor =  " ); 
 Serial.print(level); 
 Serial.println("%");
  int volume = (level/(3.1416*5*6))*100;
  if (water > 0){
    timer = timer + 1;
    delay(1000);
  }
  if (timer >= 15){
    ThingSpeak.writeField(myChannelNumber, 1, volume, myWriteAPIKey);
    buzzer();
  }
  Serial.println(timer); 
}



void buzzer()
{
digitalWrite(buzzerPin, 600);
delay(500);
digitalWrite(buzzerPin, 0);
delay(500);
}

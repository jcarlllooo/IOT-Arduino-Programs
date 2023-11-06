#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const int LED1 = D1;
const int LED2 = D7;
const int LED3 = D3;
const int LED4 = D4;
const int LED5 = D5;
const int LED6 = D6;
const int button = D2;
const int buzzerPin = D0;
const int flameSensor = A0;

int digit = 1;
int floor1 = 1;
int floor2 = 1;
int floor3 = 1;
int floor4 = 1;

const char *myWriteAPIKey = "Y4KG25T76353H5D8";

const char *ssid = "Carlo"; // replace with your wifi ssid and wpa2 key
const char *pass = "12345678";

unsigned long myChannelNumber = 2294308;

WiFiClient client;

void setup()
{
    Serial.begin(9600);
    ThingSpeak.begin(client);

    pinMode(button, INPUT);
    pinMode(flameSensor, INPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    pinMode(LED6, OUTPUT);
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
Floor();
}

void Floor()
{
    int switch1 = digitalRead(button);
    if (switch1 == 1)
    {
        delay(200);
        digit = digit + 1;
        if (digit > 4)
        {
            digit = 1;
        }
    }
    switch (digit)
    {
    case 1:
        fireSensor( 1);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, LOW);

        

        Serial.println(floor1);
        ThingSpeak.writeField(myChannelNumber, 1, floor1, myWriteAPIKey);
        break;

    case 2:
        fireSensor( 2);
        digitalWrite(LED5, HIGH);
        digitalWrite(LED6, LOW);

 

        Serial.println(floor2);
        ThingSpeak.writeField(myChannelNumber, 2, floor2, myWriteAPIKey);
        break;

    case 3:
         fireSensor( 3);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, HIGH);
     

        Serial.println(floor3);
        ThingSpeak.writeField(myChannelNumber, 3, floor3, myWriteAPIKey);
        break;

    case 4:
       fireSensor( 4);
        digitalWrite(LED5, HIGH);
        digitalWrite(LED6, HIGH);
    
        Serial.println(floor4);
        ThingSpeak.writeField(myChannelNumber, 4, floor4, myWriteAPIKey);
        break;
    }
}


void fireSensor( int lednum){
 int flame = analogRead(flameSensor);
    if (flame > 1000){
digitalWrite(buzzerPin, 600);
delay(500);
digitalWrite(buzzerPin, 0);
delay(500);
LED(lednum);
    }
    Serial.println(flame);
}


void LED(int led)
{
 switch (led)
    {
      case 1:
        digitalWrite(LED1, HIGH);
       break;
      
      case 2:
       digitalWrite(LED2, HIGH);
        break;
        
       case 3:
       digitalWrite(LED3,HIGH);
        break;

       case 4:
       digitalWrite(LED4,HIGH);
        break;

    }
}
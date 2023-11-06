#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const int TRIG_PIN = D5; // ESP8266 pin D5 connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN = D6; // ESP8266 pin D6 connected to Ultrasonic Sensor's ECHO pin
const int LED1 = D3;
const int LED2 = D4;
const int LED3 = D7;
const int LED4 = D8;
const int LED5 = D0;
const int LED6 = D1;
const int button = D2;

float duration_us, distance_cm;
int digit = 1;
int floor1 = 0;
int floor2 = 0;
int floor3 = 0;
int floor4 = 0;

const char *myWriteAPIKey = "BM9SXYM5W97BW413";

const char *ssid = "Carlo"; // replace with your wifi ssid and wpa2 key
const char *pass = "12345678";
unsigned long myChannelNumber = 2265981;

WiFiClient client;

int distance;

void setup()
{
    Serial.begin(9600);
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

    pinMode(button, INPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    pinMode(LED6, OUTPUT);
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
        people(floor1);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, LOW);
        Ultrasonic();
        if (distance_cm < 10)
        {
            floor1 = floor1 + 1;
            delay(500);
        }
        Serial.println(floor1);
        ThingSpeak.writeField(myChannelNumber, 1, floor1, myWriteAPIKey);
        break;

    case 2:
        people(floor2);
        digitalWrite(LED5, HIGH);
        digitalWrite(LED6, LOW);
        Ultrasonic();
        if (distance_cm < 10)
        {
            floor2 = floor2 + 1;
            delay(500);
        }
        Serial.println(floor2);
        ThingSpeak.writeField(myChannelNumber, 2, floor2, myWriteAPIKey);
        break;

    case 3:
        people(floor3);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, HIGH);
        Ultrasonic();
        if (distance_cm < 10)
        {
            floor3 = floor3 + 1;
            delay(500);
        }
        Serial.println(floor3);
        ThingSpeak.writeField(myChannelNumber, 3, floor3, myWriteAPIKey);
        break;

    case 4:
        people(floor4);
        digitalWrite(LED5, HIGH);
        digitalWrite(LED6, HIGH);
        Ultrasonic();
        if (distance_cm < 10)
        {
            floor4 = floor4 + 1;
            delay(500);
        }
        Serial.println(floor4);
        ThingSpeak.writeField(myChannelNumber, 4, floor4, myWriteAPIKey);
        break;
    }
}

void Ultrasonic()
{

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // measure duration of pulse from ECHO pin
    duration_us = pulseIn(ECHO_PIN, HIGH);

    // calculate the distance
    distance_cm = 0.017 * duration_us;

    // print the value to Serial Monitor
    Serial.print("distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
}

void people(int numb)
{
    if (numb == 0)
    {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
    }
    if (numb > 0)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
    }
    if (numb > 5)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
    }
    if (numb > 15)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, LOW);
    }
    if (numb > 20)
    {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
    }
}

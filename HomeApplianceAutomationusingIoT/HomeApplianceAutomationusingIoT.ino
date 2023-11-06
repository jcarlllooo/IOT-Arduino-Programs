#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Servo.h>

Servo servo;
const int pSwitch1 = D2;
const int pSwitch2 = D5;

const int powerIndicator1 = D0;
const int powerIndicator2 = D1;

const char * myWriteAPIKey = "VGXIIZAUQ1E583GG";

const char *ssid =  "GlobeAtHome_f63e0_2.4";     // replace with your wifi ssid and wpa2 key
const char *pass =  "UCkm6adj";

unsigned long myChannelNumber = 2262737;

WiFiClient client;

int ON = 1;
int OFF = 0;
bool switch1 = false;
bool switch2 = false;


void setup() {
Serial.begin(9600);
 pinMode(pSwitch1, INPUT);
 pinMode(pSwitch2, INPUT);
  pinMode(powerIndicator1, OUTPUT);
 pinMode(powerIndicator2, OUTPUT);
servo.attach(D4);
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
int ButtonSwitch1 = digitalRead(pSwitch1);
int ButtonSwitch2 = digitalRead(pSwitch2);


Serial.println(ButtonSwitch2);



if (ButtonSwitch1 == 1){
switch1 = !switch1 ;
}
if (switch1 == true){
delay(100);
digitalWrite(powerIndicator1, HIGH);
digitalWrite(powerIndicator2, LOW);
ThingSpeak.writeField(myChannelNumber, 1, ON , myWriteAPIKey);
if(ButtonSwitch2 == 1){
servo.write(180);
ThingSpeak.writeField(myChannelNumber, 2, ON , myWriteAPIKey);
}
delay(100);
servo.write(0);
ThingSpeak.writeField(myChannelNumber, 2, OFF , myWriteAPIKey);
}

if (switch1 == false){
delay(100);
digitalWrite(powerIndicator2, HIGH);
digitalWrite(powerIndicator1, LOW);
ThingSpeak.writeField(myChannelNumber, 1, OFF , myWriteAPIKey);



}
}






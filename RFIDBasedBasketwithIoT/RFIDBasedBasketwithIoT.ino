#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h> 

#define SS_PIN D8
#define RST_PIN D0
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27,20,4); 

const int Button1 = D4;
const int LED = D3;

int scan = 0;
int value1 = 0;
int mode = 1; 

const char *myWriteAPIKey = "O834FMJP0XWB6K6H";

const char *ssid =  "CondoMates.2G";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Condomates.2G";

unsigned long myChannelNumber = 2295332;

WiFiClient client;



void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  ThingSpeak.begin(client);
  SPI.begin();// Initiate  SPI bus
  lcd.init(); 
  lcd.backlight();       
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
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

  pinMode(Button1, INPUT);
  pinMode(LED, OUTPUT);
}
void loop() 
{


 int switch1 = digitalRead(Button1);
    if (switch1 == 0){
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
  mode = !mode;
    }
   Serial.println(mode);
   if(mode == 1){
 addClothing1();
   }
 if(mode == 0){
 subClothing1();
 }
} 





 void subClothing1(){
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
 
 //Tshirt//
 if (content.substring(1) == "E3 63 5E B0") //change here the UID of the card/cards that you want to give access
  {
    value1 = value1 - 450;
    scan = scan + 1;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(0,0);
    lcd.print("Product : T-shirt ");
     lcd.setCursor(0,1);
    lcd.print("Price : 450 ");
    Serial.println();
    delay(200);
    total();
  }


  //short//
 if (content.substring(1) == "73 53 61 AF") //change here the UID of the card/cards that you want to give access
  {
    value1 = value1 - 750;
    scan = scan + 1;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(0,0);
    lcd.print("Product : Shorts ");
     lcd.setCursor(0,1);
    lcd.print("Price : 750 ");
    Serial.println();
    delay(200);
    total();
  }
   
   //shoes//
    if (content.substring(1) == "44 7E A3 3B") //change here the UID of the card/cards that you want to give access
  {
    value1 = value1 - 7500;
    scan = scan + 1;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(0,0);
    lcd.print("Product : Jordan 1 ");
     lcd.setCursor(0,1);
    lcd.print("Price : 7500 ");
    Serial.println();
    delay(200);
    total();
  }

    //hoodie//
   if (content.substring(1) == "60 38 6B 1E") //change here the UID of the card/cards that you want to give access
  {
    value1 = value1 - 950;
    scan = scan + 1;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(0,0);
    lcd.print("Product : Hoodie ");
     lcd.setCursor(0,1);
    lcd.print("Price : 950 ");
    Serial.println();
    delay(200);
    total();
  }
  //pants
   if (content.substring(1) == "4B E2 A9 3B") //change here the UID of the card/cards that you want to give access
  {
    value1 = value1 - 1250;
    scan = scan + 1;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(0,0);
    lcd.print("Product : Pants ");
     lcd.setCursor(0,1);
    lcd.print("Price : 1250 ");
    Serial.println();
    delay(200);
    total();
  }

    //check out//
   if (content.substring(1) == "3A F3 7B 17") //change here the UID of the card/cards that you want to give access
  {
    value1 = 0;
    ThingSpeak.writeField(myChannelNumber, 1, scan, myWriteAPIKey);
    scan = 0;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(5,0);
    lcd.print("Thank you");
     lcd.setCursor(8,1);
    lcd.print("for ");
     lcd.setCursor(6,2);
    lcd.print("buying! ");
    Serial.println();
    delay(200);
  }
 }


void addClothing1(){
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
 
 //Tshirt//
 if (content.substring(1) == "E3 63 5E B0") //change here the UID of the card/cards that you want to give access
  {
    value1 = value1 + 450;
    scan = scan + 1;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(0,0);
    lcd.print("Product : T-shirt ");
     lcd.setCursor(0,1);
    lcd.print("Price : 450 ");
    Serial.println();
    delay(200);
    total();
  }


  //short//
 if (content.substring(1) == "73 53 61 AF") //change here the UID of the card/cards that you want to give access
  {
    value1 = value1 + 750;
    scan = scan + 1;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(0,0);
    lcd.print("Product : Shorts ");
     lcd.setCursor(0,1);
    lcd.print("Price : 750 ");
    Serial.println();
    delay(200);
    total();
  }
   
   //shoes//
    if (content.substring(1) == "44 7E A3 3B") //change here the UID of the card/cards that you want to give access
  {
    value1 = value1 + 7500;
    scan = scan + 1;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(0,0);
    lcd.print("Product : Jordan 1 ");
     lcd.setCursor(0,1);
    lcd.print("Price : 7500 ");
    Serial.println();
    delay(200);
    total();
  }

    //hoodie//
   if (content.substring(1) == "60 38 6B 1E") //change here the UID of the card/cards that you want to give access
  {
    value1 = value1 + 950;
    scan = scan + 1;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(0,0);
    lcd.print("Product : Hoodie ");
     lcd.setCursor(0,1);
    lcd.print("Price : 950 ");
    Serial.println();
    delay(200);
    total();
  }
  //pants
   if (content.substring(1) == "4B E2 A9 3B") //change here the UID of the card/cards that you want to give access
  {
    value1 = value1 + 1250;
    scan = scan + 1;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(0,0);
    lcd.print("Product : Pants ");
     lcd.setCursor(0,1);
    lcd.print("Price : 1250 ");
    Serial.println();
    delay(200);
    total();
  }

    //check out//
   if (content.substring(1) == "3A F3 7B 17") //change here the UID of the card/cards that you want to give access
  {
    value1 = 0;
    ThingSpeak.writeField(myChannelNumber, 1, scan, myWriteAPIKey);
    scan = 0;
    lcd.clear();
    Serial.println(value1);
    lcd.setCursor(5,0);
    lcd.print("Thank you");
     lcd.setCursor(8,1);
    lcd.print("for ");
     lcd.setCursor(6,2);
    lcd.print("buying! ");
    Serial.println();
    delay(200);
  }
 }



void total(){
  if( value1 < 0){
    value1 = 0;
  }
delay(1500);
  lcd.setCursor(9,3);
  lcd.print("total:");
  lcd.setCursor(15,3);
  lcd.print(value1);
  lcd.setCursor(0,3);
  lcd.print(scan);
 }



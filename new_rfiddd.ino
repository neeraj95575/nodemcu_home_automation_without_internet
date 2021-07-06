#include <LiquidCrystal_I2C.h>
#include "MFRC522.h"
#include <Wire.h> 
#include "SPI.h"
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

int ir1 = 2;
int ir2 = 3;
int ir3 = 4;
int ir4 = 5;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Servo myservo;

int mic = 8;

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;


byte Check[] = { // this create check sign in lcd screen 
  B00000,
  B00001,
  B00011,
  B10110,
  B11100,
  B01000,
  B00000,
  B00000
};

byte Right_arrow[] = {
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000,
  B00000
};

byte Left_arrow[] = {
  B00000,
  B00100,
  B01000,
  B11111,
  B01000,
  B00100,
  B00000,
  B00000
};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin(); // start rfid
  lcd.init();  // initialize the lcd 
  rfid.PCD_Init();
  pinMode(2, INPUT); //ir1
  pinMode(3, INPUT); //ir2
  pinMode(4, INPUT); //ir3
  pinMode(5, INPUT); //ir4
  pinMode(8, OUTPUT); //speaker
  myservo.attach(6);
  myservo.write(30);
  Serial.println("waiting for card...");
  lcd.backlight(); // turn on the back light of lcd screen
  lcd.setCursor(2,0);
  lcd.print("CAR PARKING");
  lcd.setCursor(5,1);
  lcd.print("SYSTEM");
  lcd.createChar(0, Check);
  lcd.createChar(1, Right_arrow);
  lcd.createChar(2, Left_arrow);
  
  lcd.setCursor(0, 0);
  lcd.write((byte)1);
  
  lcd.setCursor(14, 0);
  lcd.write((byte)2);

  delay(2000);
  lcd.clear();
}
void loop() {
  
  // put your main code here, to run repeatedly:
  int value1 = digitalRead(2); // for slot1
  int value2 = digitalRead(3); // for slot2
  int value3 = digitalRead(4); // for slot3
  int value4 = digitalRead(5); // for slot4


//////////////////////////////////// for full slots /////////////////
  if (value1==HIGH)
  {
    lcd.setCursor(0,0);
    lcd.print("Slot1 ");
    lcd.setCursor(6, 0);
    lcd.write((byte)0);
  }

  if (value2==HIGH)
  {
    lcd.setCursor(9,0);
    lcd.print("Slot2 ");
    lcd.setCursor(15, 0);
    lcd.write((byte)0);
  }

  if (value3==HIGH)
  {
   lcd.setCursor(0,1);
   lcd.print("Slot3 ");
   lcd.setCursor(6,1);
   lcd.write((byte)0);

  }

  if (value4==HIGH)
  {
   lcd.setCursor(9,1);
   lcd.print("Slot4");
   lcd.setCursor(15,1);
   lcd.write((byte)0);
  }

  if (value1==HIGH && value2==HIGH && value3==HIGH && value4==HIGH)
    { 
       lcd.setCursor(0,0);
       lcd.print("   PARKING IS    "); 
       lcd.setCursor(0,1);
       lcd.print("      FULL        "); 
       delay(2000);
       lcd.clear();

     }
  

//////////////////// for empty slots /////////////////////////////////////
  if (value1==LOW)
  {
    lcd.setCursor(0,0);
    lcd.print("Slot1 ");
    lcd.setCursor(6, 0);
    lcd.print("x");
  }

  if (value2==LOW)
  {
    lcd.setCursor(9,0);
    lcd.print("Slot2 ");
    lcd.setCursor(15, 0);
    lcd.print("x");
  }

  if (value3==LOW)
  {
   lcd.setCursor(0,1);
   lcd.print("Slot3 ");
   lcd.setCursor(6,1);
   lcd.print("x");

  }

  if (value4==LOW)
  {
   lcd.setCursor(9,1);
   lcd.print("Slot4");
   lcd.setCursor(15,1);
   lcd.print("x");
   }
 
/////////////////////////////////////////////////////////////////////////////////
   
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }
  strID.toUpperCase();
  Serial.print("Tap card key: ");
  //Serial.println(strID);
  delay(500);
  
  if (strID.indexOf("6D:C7:64:A9") >= 0) {  //put your own tap card key;   put your own rfid code of the tag 
  
    Serial.println("**Authorised acces**");
   
    digitalWrite(8, LOW);
   
     if (value1==HIGH && value2==HIGH && value3==HIGH && value4==HIGH)
    {
       myservo.write(30);
       Serial.print("full slot");
  
       lcd.setCursor(0,0);
       lcd.print("   PARKING IS    "); 
       lcd.setCursor(0,1);
       lcd.print("      FULL        "); 
       delay(1000);
       lcd.clear();
       
     }

    else
    {
      myservo.write(120); //motor moves 70 degree
      Serial.println("70 degree");
      delay(5000);
      myservo.write(30);
    }
    

  }
  
  else 
  {
   
    Serial.println("**Acces denied**");
    //lcd.setCursor(0,1);
    //lcd.print("Acces denied");
    myservo.write(30);
    digitalWrite(8, HIGH);
    delay(2000);
    digitalWrite(8, LOW);

  }
 }

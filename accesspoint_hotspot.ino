#include <ESP8266WiFi.h>

WiFiServer server(80);
IPAddress IP(192,168,4,2);
IPAddress mask = (255, 255, 255, 0);

const int relay_1 =  D0;
const int relay_2 =  D1; 
const int relay_3 =  D2;  
const int relay_4 =  D3; 

int request1 = 0;
int flag_1=0;

int request2 = 0;
int flag_2=0;

int request3 = 0;
int flag_3=0;

int request4 = 0;
int flag_4=0;


void setup() {
 Serial.begin(9600);
 WiFi.mode(WIFI_AP);
 WiFi.softAP("ESPsoftAP_01", "python@123");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
 
 pinMode(relay_1, OUTPUT);
 pinMode(relay_2, OUTPUT);
 pinMode(relay_3, OUTPUT);
 pinMode(relay_4, OUTPUT);

 Serial.println();
 Serial.println("accesspoint_bare_01.ino");
 Serial.println("Server started.");
 //Serial.print("IP: "); Serial.println(WiFi.softAPIP());
 //Serial.print("MAC:"); Serial.println(WiFi.softAPmacAddress());
}

void loop()
{
   WiFiClient client = server.available();
   if (!client) {return;}
   String request1 = client.readStringUntil('\r');
   String request2 = client.readStringUntil('\r');
   String request3 = client.readStringUntil('\r');
   String request4 = client.readStringUntil('\r');
   Serial.println("********************************");
   Serial.println("From the station: " + request1);
   Serial.println("From the station: " + request2);
   Serial.println("From the station: " + request3);
   Serial.println("From the station: " + request4);
  
   if (request1 == "relay_1_OFF")
   { 
      //ones, turn led on!
      if ( flag_1 == 0)
      {
        digitalWrite(relay_1, HIGH);
        flag_1=1; //change flag variable
      }
      //twice, turn led off!
      else if ( flag_1 == 1)
      {
        digitalWrite(relay_1, LOW);
        flag_1=0; //change flag variable again 
      }    
    } 


    if (request2 == "relay_2_OFF")
   { 
      //press ones, turn led on!
      if ( flag_2 == 0)
      {
        digitalWrite(relay_2, HIGH);
        flag_2=1; //change flag variable
      }
      //press twice, turn led off!
      else if ( flag_2 == 1)
      {
        digitalWrite(relay_2, LOW);
        flag_2=0; //change flag variable again 
      }    
    } 


    if (request3 == "relay_3_OFF")
   { 
      //press ones, turn led on!
      if ( flag_3 == 0)
      {
        digitalWrite(relay_3, HIGH);
        flag_3=1; //change flag variable
      }
      //press twice, turn led off!
      else if ( flag_3 == 1)
      {
        digitalWrite(relay_3, LOW);
        flag_3=0; //change flag variable again 
      }    
    } 


    if (request4 == "relay_4_OFF")
   { 
      //press ones, turn led on!
      if ( flag_4 == 0)
      {
        digitalWrite(relay_4, HIGH);
        flag_4=1; //change flag variable
      }
      //press twice, turn led off!
      else if ( flag_4 == 1)
      {
        digitalWrite(relay_4, LOW);
        flag_4=0; //change flag variable again 
      }    
    } 
   delay(100);
   client.flush();
}

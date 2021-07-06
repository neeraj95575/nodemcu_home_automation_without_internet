#include <ESP8266WiFi.h>

char ssid[] = "ESPsoftAP_01";       // SSID of your AP
char pass[] = "python@123";         // password of your AP
IPAddress server(192,168,4,2);      // IP address of the AP

/////////////////////////////////for push buttons///////////
int button_1 = D1;     
int button_2 = D2; 
int button_3 = D3;  
int button_4 = D4;  
    
int buttonState_1 = 0;  
int buttonState_2 = 0; 
int buttonState_3 = 0;   
int buttonState_4 = 0;


WiFiClient client;
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");

  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  //Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  //Serial.println("MAC:" + WiFi.macAddress());
  //Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  //Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
}

void loop() {
  client.connect(server, 80);
  Serial.println("********************************");
  Serial.print("Byte sent to the AP: ");
  buttonState_1 = digitalRead(button_1);
  buttonState_2 = digitalRead(button_2);
  buttonState_3 = digitalRead(button_3);
  buttonState_4 = digitalRead(button_4);
  
  if (buttonState_1 == HIGH)
  {
   Serial.println(client.print("relay_1_ON\r")); 
  }
  if (buttonState_1 == LOW)
  {
   Serial.println(client.print("relay_1_OFF\r")); 
  }


  if (buttonState_2 == HIGH)
  {
   Serial.println(client.print("relay_2_ON\r"));  
  }
  if (buttonState_2 == LOW)
  {
   Serial.println(client.print("relay_2_OFF\r")); 
  }


  if (buttonState_3 == HIGH)
  {
   Serial.println(client.print("relay_3_ON\r")); 
  }
  if (buttonState_3 == LOW)
  {
   Serial.println(client.print("relay_3_OFF\r")); 
  }
  
  
  if (buttonState_4 == HIGH)
  {
   Serial.println(client.print("relay_4_ON\r")); 
  }
  if (buttonState_4 == LOW)
  {
    
   Serial.println(client.print("relay_4_OFF\r"));  
  }
  client.flush();
  client.stop();
  delay(200);
}

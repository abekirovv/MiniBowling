#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "WiFiEsp.h"
#include "ThingSpeak.h"
#include<NoDelay.h>

char ssid[] = "Bekirov";    //  your network SSID (name) 
char pass[] = "86983488";   // your network password
int keyIndex = 0;
int number = 0; //prom
WiFiEspClient  client;

noDelay timep(15000);
unsigned long start_time;
unsigned long timed_event;
unsigned long current_time;

LiquidCrystal_I2C lcd(0x27,20,4);
int photoR = 0; 
int score = 0; //score
int light0 = 0; // store the current light value
int light1 = 0;
int light2 = 0;
int light3 = 0;
int light4 = 0;
int light5 = 0;
int light6 = 0;
int light7 = 0;
int light8 = 0;
int light9 = 0;
int total = 0;
int pom = 0;



#ifndef HAVE_HWSERIAL3
#define ESP_BAUDRATE  19200
#else
#define ESP_BAUDRATE  115200
#endif

unsigned long myChannelNumber = 1613185;
const char * myWriteAPIKey = "6NBZA71ISNMJ7WUY";

void setup() {

     Serial.begin(9600);
  setEspBaudRate(ESP_BAUDRATE);
  WiFi.init(&Serial3);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
  Serial.println("found it!");
    
  ThingSpeak.begin(client);
  
    lcd.init();
   // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("====================");
    lcd.setCursor(4,1);
    lcd.print("GO BOWLING");
    lcd.setCursor(0,3);
    lcd.print("====================");

    
    
    pinMode(4, OUTPUT); // digital output for led light
    pinMode(5, OUTPUT); // digital output for led light
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    timed_event = 15000;
    current_time = millis();
    start_time = current_time;
    
}

void loop() {
    
    Serial.begin(9600);

    
    light0 = analogRead(A9); // read the value from the photoresistor
    light1 = analogRead(A8); //second photoresistor
    light2 = analogRead(A7);
    light3 = analogRead(A6);
    light4 = analogRead(A5);
    light5 = analogRead(A4);
    light6 = analogRead(A3);
    light7 = analogRead(A2);
    light8 = analogRead(A1);
    light9 = analogRead(A0);
    
    Serial.print("top: ");
    Serial.println(light0); // print light value
    Serial.print("secondright: ");
    Serial.println(light1); //
    Serial.print("secondleft: ");
    Serial.println(light2);

    Serial.print("thirdright: ");
    Serial.println(light3); // print light value
    Serial.print("thirdmiddle: ");
    Serial.println(light4); //
    Serial.print("thirdleft: ");
    Serial.println(light5);

    Serial.print("bottomright: ");
    Serial.println(light6); // print light value
    Serial.print("bottomiddleright: ");
    Serial.println(light7); //
    Serial.print("bottomiddlelfet: ");
    Serial.println(light8);
    Serial.print("bottomleft: ");
    Serial.println(light9);
    delay(1000); // don't spam the computer!
    
   //Serial.println("left: " + light1); // print light value
    digitalWrite(4,HIGH); // set led light ON
    digitalWrite(5,HIGH); // set led light ON
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH); // set led light ON
    digitalWrite(8,HIGH); // set led light ON
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    
    
    
    int photoR1 = 0;
    int photoR2 = 0;
    int photoR3 = 0;
    int photoR4 = 0;
    int photoR5 = 0;
    int photoR6 = 0;
    int photoR7 = 0;
    int photoR8 = 0;
    int photoR9 = 0;
    int photoR10 = 0; 
    
    if(light0 > 35) {
       photoR1 = 1;  
    } else { photoR1 = 0;}
      
    if(light1 > 50) {
       photoR2 = 1;   
    } else { photoR2 = 0;}
     if(light2 > 50) {
       photoR3 = 1;  
    } else { photoR3 = 0;}
   if(light3 > 50) {
     photoR4 = 1;  
    } else { photoR4 = 0;}
      if(light4 > 50) {
     photoR5 = 1;  
    } else { photoR5 = 0;}
      if(light5 > 50) {
       photoR6 = 1;  
    } else { photoR6 = 0;}
      if(light6 > 50) {
       photoR7 = 1;  
    } else { photoR7 = 0;}
      if(light7 > 50) {
      photoR8 = 1;   
    } else { photoR8 = 0;}
      if(light8 > 50) {
     photoR9 = 1;  
    } else { photoR9 = 0;}
      if(light9 > 50) {
     photoR10 = 1;  
    }else { photoR10 = 0;}

    total = photoR1+photoR2+photoR3+photoR4+photoR5+photoR6+photoR7+photoR8+photoR9+photoR10;

    if (total == 0) {
      lcd.setCursor(3,2);
      lcd.print("You can begin: ");
      } else {
          if(total == 10){
             lcd.clear();

          lcd.backlight();
          lcd.setCursor(0,0);
          lcd.print("====================");
          lcd.setCursor(0,1);
          lcd.print("NICE JOB!UP ALL PINS");
          lcd.setCursor(0,2);
          lcd.print("SO YOU CAN TRY AGAIN");
          lcd.setCursor(3,3);
          lcd.print("Your Score: ");
          lcd.print(total);
            } else {
          lcd.clear();

          lcd.backlight();
          lcd.setCursor(0,0);
          lcd.print("====================");
          lcd.setCursor(4,1);
          lcd.print("GO BOWLING");
          lcd.setCursor(0,3);
          lcd.print("REMOVE UNWANTED PINS");

          lcd.setCursor(3,2);
          lcd.print("Your Score: ");
          lcd.print(total);
        }
      }
        
     
      if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    }
    Serial.println("\nConnected.");
      }
     
     int x = ThingSpeak.writeField(myChannelNumber, 1, total, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
delay(15000);
    

 
  
}

void setEspBaudRate(unsigned long baudrate){
  long rates[6] = {115200,74880,57600,38400,19200,9600};

  Serial.print("Setting ESP8266 baudrate to ");
  Serial.print(baudrate);
  Serial.println("...");

  for(int i = 0; i < 6; i++){
    Serial3.begin(rates[i]);
    delay(100);
    Serial3.print("AT+UART_DEF=");
    Serial3.print(baudrate);
    Serial3.print(",8,1,0,0\r\n");
    delay(100);  
  }
    
  Serial3.begin(baudrate);
}

#include "WiFiEsp.h"
#include "ThingSpeak.h"

char ssid[] = "Bekirov";    //  your network SSID (name) 
char pass[] = "86983488";   // your network password
int keyIndex = 0;
int number = 0; //prom
WiFiEspClient  client;

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
}

void loop() {
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

  int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
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

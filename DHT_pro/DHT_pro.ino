#include "ESP8266_AT.h"
#include "DHT.h"

#define DOMAIN        "api.thingspeak.com"
#define PORT        "80"
#define API_WRITE_KEY   "S5YSTJ24LJ64F7Q2"
#define CHANNEL_ID      "749546"
#define DHTPIN 2 
#define DHTTYPE DHT11

#define SSID        "HIPL"
#define PASSWORD    "Hemraj.WiFi"

char _buffer[150], _buffer_2[150];
uint8_t Connect_Status;
//int sample = 0;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  while(!ESP8266_Begin());
  ESP8266_WIFIMode(BOTH_STATION_AND_ACCESPOINT);
  ESP8266_ConnectionMode(SINGLE); 
  ESP8266_ApplicationMode(NORMAL);
  if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)
  ESP8266_JoinAccessPoint(SSID, PASSWORD);
  ESP8266_Start(0, DOMAIN, PORT);	
}

void loop(){
    int h = dht.readHumidity();
    int t = dht.readTemperature();
    Connect_Status = ESP8266_connected();
    if(Connect_Status == ESP8266_NOT_CONNECTED_TO_AP)		/*Again check connection to WIFI*/
    ESP8266_JoinAccessPoint(SSID, PASSWORD);		/*Connect to WIFI*/
    if(Connect_Status == ESP8266_TRANSMISSION_DISCONNECTED)
    ESP8266_Start(0, DOMAIN, PORT);		/*Connect to TCP port*/

    memset(_buffer, 0, 150);
    memset(_buffer_2, 0, 150);
    sprintf(_buffer, "GET /update?api_key=%s&field1=%d", API_WRITE_KEY, h);
    sprintf(_buffer_2, "GET /update?api_key=%s&field2=%d", API_WRITE_KEY, t);
    ESP8266_Send(_buffer_2);
    ESP8266_Send(_buffer);
   
    delay(10000);
 }
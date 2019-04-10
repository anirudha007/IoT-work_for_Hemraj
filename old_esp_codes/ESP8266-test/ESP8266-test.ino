/*
 * ESP8266 AT
 * http://www.electronicwings.com
 */ 
 #include "ESP8266_AT.h"

 /* Select Demo */
//#define RECEIVE_DEMO        /* Define RECEIVE demo */
#define SEND_DEMO         /* Define SEND demo */

/* Define Required fields shown below */
#define DOMAIN        "api.thingspeak.com"
#define PORT        "80"
#define API_WRITE_KEY   "S5YSTJ24LJ64F7Q2"
#define CHANNEL_ID      "749546"

#define SSID        "HIPL"
#define PASSWORD      "Hemraj.WiFi"

char _buffer[300];
uint8_t Connect_Status;
#ifdef SEND_DEMO
uint8_t Sample = 0;
#endif

void setup() {
  Serial.begin(115200);
 
  while(!ESP8266_Begin());
  ESP8266_WIFIMode(BOTH_STATION_AND_ACCESPOINT);/* 3 = Both (AP and STA) */
  ESP8266_ConnectionMode(SINGLE);     /* 0 = Single; 1 = Multi */
  ESP8266_ApplicationMode(NORMAL);    /* 0 = Normal Mode; 1 = Transperant Mode */
  if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)	/*Check WIFI connection*/
  ESP8266_JoinAccessPoint(SSID, PASSWORD);		/*Connect to WIFI*/
  ESP8266_Start(0, DOMAIN, PORT);	
}

void loop() {
    Connect_Status = ESP8266_connected();
    if(Connect_Status == ESP8266_NOT_CONNECTED_TO_AP)		/*Again check connection to WIFI*/
    ESP8266_JoinAccessPoint(SSID, PASSWORD);		/*Connect to WIFI*/
    if(Connect_Status == ESP8266_TRANSMISSION_DISCONNECTED)
    ESP8266_Start(0, DOMAIN, PORT);		/*Connect to TCP port*/

    #ifdef SEND_DEMO
    memset(_buffer, 0, 300);
    sprintf(_buffer, "GET /update?api_key=%s&field1=%d", API_WRITE_KEY, Sample++); 	/*connect to thingspeak server to post data using your API_WRITE_KEY*/
    ESP8266_Send(_buffer);
    //delay(10);
    
    memset(_buffer, 0, 300);
    sprintf(_buffer, "GET /update?api_key=%s&field2=%d", API_WRITE_KEY, Sample++);
    ESP8266_Send(_buffer);
    delay(15000); /* Thingspeak server delay */
    #endif
    
    #ifdef RECEIVE_DEMO
    memset(_buffer, 0, 150);
    sprintf(_buffer, "GET /channels/%s/feeds/last.txt", CHANNEL_ID); /*Connect to thingspeak server to get data using your channel ID*/
    ESP8266_Send(_buffer);
    Read_Data(_buffer);
    delay(600);
    #endif
  }

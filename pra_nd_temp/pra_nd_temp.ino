
 #include "ESP8266_AT.h"


#define DOMAIN          "api.thingspeak.com"
#define PORT            "80"
#define API_WRITE_KEY   "P86SW4TZNFV8IZ3W"
#define CHANNEL_ID      "774855"

#define SSID            "HIPL"
#define PASSWORD        "Hemraj.WiFi"

char _buffer[400];
uint8_t Connect_Status;

//uint8_t Sample = 0;
int ThermistorPin = A0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


void setup() {
  Serial.begin(115200);
 
  while(!ESP8266_Begin());
  ESP8266_WIFIMode(BOTH_STATION_AND_ACCESPOINT);/* 3 = Both (AP and STA) */
  ESP8266_ConnectionMode(SINGLE);     /* 0 = Single; 1 = Multi */
  ESP8266_ApplicationMode(NORMAL);    /* 0 = Normal Mode; 1 = Transperant Mode */
  if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)  /*Check WIFI connection*/
  ESP8266_JoinAccessPoint(SSID, PASSWORD);    /*Connect to WIFI*/
  ESP8266_Start(0, DOMAIN, PORT); 
}

void loop() {
    Vo = analogRead(ThermistorPin);
    int sensorVal=analogRead(A1);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    Tc = T - 273.15;
    int temp = Tc;
    float voltage = (sensorVal*5.0)/1024.0;
    float pressure_pascal = (3.0*((float)voltage-0.47))*1000000.0;
    float pressure_bar = pressure_pascal/10e5;
    int preasure1 = (pressure_bar-0.15);
    
    Connect_Status = ESP8266_connected();
    if(Connect_Status == ESP8266_NOT_CONNECTED_TO_AP)   /*Again check connection to WIFI*/
    ESP8266_JoinAccessPoint(SSID, PASSWORD);    /*Connect to WIFI*/
    if(Connect_Status == ESP8266_TRANSMISSION_DISCONNECTED)
    ESP8266_Start(0, DOMAIN, PORT);   /*Connect to TCP port*/

    memset(_buffer, 0, 400);
    sprintf(_buffer, "GET /update?api_key=%s&field1=%d&field2=%d", API_WRITE_KEY, temp, preasure1);  /*connect to thingspeak server to post data using your API_WRITE_KEY*/
    ESP8266_Send(_buffer);
    delay(15000); /* Thingspeak server delay */
}

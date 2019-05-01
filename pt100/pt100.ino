
const int AnalogInput = A0;  


int   sensorValue = 0;        
int   temperature = 0;

float f1 = 0;
float t1 = 0;



void setup() {

  Serial.begin(9600); 
}

void loop() {
  
    
     sensorValue = analogRead(AnalogInput);
                
     
    
     temperature=map(sensorValue,205,1023,-500,1500);

     f1 = temperature;  // 
     t1 = f1/10.0;      //
                        // 

     Serial.print(t1);
     Serial.print("\n"); 
 
     delay(1000);     
  
  
  
  
}

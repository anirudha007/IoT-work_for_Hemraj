int relay_pin = 10;
int val=0;
int result = 0;
int sensor_pin = A0;
int kill_switch = 12;
int switch_state = 0;

#define UPPERLIMIT  630 
#define LOWERLIMIT  500

#define UPPERCOEFF 0.064
#define LOWERCOEFF 0.054

void setup() {
  pinMode(kill_switch, INPUT);
  pinMode(relay_pin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(relay_pin, LOW);   // relay off         
  for(int i=0;i<10;i++){
    result = result + analogRead(sensor_pin);
    val = result/10; 
  }
  switch_state = digitalRead(kill_switch);
  if(switch_state==LOW){
    if(val >= UPPERLIMIT){
      Serial.print(val*UPPERCOEFF);
      Serial.println("kgf");
      digitalWrite(relay_pin, HIGH); // relay on
      }
    else if(val <= LOWERLIMIT){
      Serial.print(val*LOWERCOEFF);
      Serial.println("kgf");
      digitalWrite(relay_pin, HIGH); // relay on 
      }
    else{
      Serial.println("No horn");
      digitalWrite(relay_pin, LOW); // relay off 
    }
  }
  else if(switch_state==LOW){
      Serial.println("Killed!");
      digitalWrite(relay_pin, LOW);
      delay(10000);
  }
  delay(10);
}

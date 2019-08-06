void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println(read_internal_temp());
  delay(100);
}

double read_internal_temp(void){
  unsigned int wADC;
  double t;
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // ADC en
  delay(20);            
  ADCSRA |= _BV(ADSC);  // Begin covsersion
  while (bit_is_set(ADCSRA,ADSC));
  wADC = ADCW;
  t = (wADC - 324.31 ) / 1.22;
  return (t);
}

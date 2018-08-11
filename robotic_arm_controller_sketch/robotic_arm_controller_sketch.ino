const int analog0 = 0;

void setup() {
  Serial.begin( 9600 );
}

void loop() {
  int i = analogRead( PIN_ANALOG_INPUT );
  float f = i * 5.0 / 1023.0;
  Serial.println( f );
  delay( 1000 ); 
}

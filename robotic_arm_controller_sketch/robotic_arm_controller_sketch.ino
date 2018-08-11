const int controller_axis0 = 0;
const int controller_axis1 = 1;
const int controller_axis2 = 2;
const int controller_axis3 = 3;
const int controller_axis4 = 4;
const int controller_axis5 = 5;

const int arm_axis0_up = 2;
const int arm_axis0_down = 3;
const int arm_axis1_up = 4;
const int arm_axis1_down = 5;
const int arm_axis2_up = 6;
const int arm_axis2_down = 7;
const int arm_axis3_up = 8;
const int arm_axis3_down = 9;
const int arm_axis4_up = 10;
const int arm_axis4_down = 11;
const int arm_axis5_up = 12;
const int arm_axis5_down = 13;


void setup() {
  Serial.begin( 9600 );
}

void loop() {
  int i = analogRead( PIN_ANALOG_INPUT );
  float f = i * 5.0 / 1023.0;
  Serial.println( f );
  delay( 1000 ); 
}

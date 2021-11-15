// #include <analogWrite.h> DO not include - made for esp32

// pins DC motors connected to
const int motorPin = A0;
//const int motorPin2 = SCL;

// emit a number between 0 and 255
//void emit_motor(int number) {
//  analogWrite(motorPin1, number);
//}

void setup() {
 // initialize the motors as outputs
 pinMode(motorPin, OUTPUT);
 // Set up serial communication
 Serial.begin(9600);
}

void loop() {
  analogWrite(motorPin, 40); // there is some minimum we are not aware of
//  for(int x = 20; x < 255; x+=20) {
//    analogWrite(motorPin, x);
//    delay(2000);
//  }
//  analogWrite(motorPin, 50);
//  analogWrite(motorPin, 50);
//  delay(5000);
//  analogWrite(motorPin, 0);
//  delay(5000);
}

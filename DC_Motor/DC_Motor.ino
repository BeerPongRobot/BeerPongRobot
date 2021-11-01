#include <analogWrite.h>

// pins DC motors connected to
const int motorPin1 = SDA;
const int motorPin2 = SCL;

// emit a number between 0 and 255
void emit_motor(int number) {
  analogWrite(motorPin1, number);
  analogWrite(motorPin2, number);
}

void setup() {
 // initialize the motors as outputs
 pinMode(motorPin1, OUTPUT);
 pinMode(motorPin2, OUTPUT);
 // Set up serial communication
 Serial.begin(9600);
}

void loop() {
  emit_motor(100);
}

#include <ESP32_Servo.h>
// Controlling a servo position using a potentiometer (variable resistor)
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>
// create servo object to control a servo
Servo myservo;
// Pin to control the servo
const int servo_pin = 27;
int val;

void setup()
{
  myservo.attach(servo_pin, 600, 2400);
}
void loop()
{
  myservo.write(0);
  delay(1000);
  myservo.write(90);
  delay(1000);
  myservo.write(180);
  delay(1000);
} 

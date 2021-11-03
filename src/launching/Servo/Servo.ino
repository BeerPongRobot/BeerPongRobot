#include <ESP32_Servo.h>
// Controlling a servo position using a potentiometer (variable resistor)
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>
// create servo object to control a servo
Servo myservo;
// Pin to control the servo
const int servo_pin = 12;
int val;

void setup()
{
  myservo.attach(servo_pin);
}
void loop()
{
  val = (val + 180) % 360;
  myservo.write(val);
  delay(1000);
} 

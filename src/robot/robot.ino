#include <Servo.h> // installed from here: https://www.arduino.cc/reference/en/libraries/servo/

// pins DC motors connected to
const int motorPin = A0; // note pin A2 does not work, does not have PWM

const int step_pin = A4;
const int direction_pin = A3;

const int horiz_step_pin = A2;
const int horiz_direction_pin = A1;

const int servo_pin = A5;

// create servo object to control a servo
Servo myservo;
// Pin to control the servo

void setup() {
  // put your setup code here, to run once:
 // Set up serial communication
 Serial.begin(9600);
 pinMode(motorPin, OUTPUT);
 pinMode(step_pin, OUTPUT);
 pinMode(direction_pin, OUTPUT);
 pinMode(horiz_step_pin, OUTPUT);
 pinMode(horiz_direction_pin, OUTPUT);

 myservo.attach(servo_pin, 600, 2400);
}

// 200 steps for 360 degree
const int STEPS_PER_TURN = 200;

// Adjust the delay for control speed
const int delay_between_step_microsec = 5000;

void step(bool forward, int step_pin, int direction_pin)
{
 // setting the direction
 if (forward == true)
 {
 digitalWrite(direction_pin, HIGH);
 }
 else
 {
 digitalWrite(direction_pin, LOW);
 }
 // creating a step
 digitalWrite(step_pin, HIGH);
 delayMicroseconds(4);// minimum 1.9us
 digitalWrite(step_pin, LOW);
}

void steps(int number_of_steps, int step_pin, int direction_pin)
{
 bool move_forward = true;
 // Establishing the direction
 if (number_of_steps >= 0)
 {
 move_forward = true;
 }
 else
 {
 move_forward = false;
 number_of_steps = -number_of_steps;
 }
 // Generating the steps
 for (int i = 0; i < number_of_steps; i++)
 {
 step(move_forward, step_pin, direction_pin);
 // Delay for proper speed
 delayMicroseconds(delay_between_step_microsec);
 }
}

void test_wheels() {
  analogWrite(motorPin, 40);
  delay(10000);
  analogWrite(motorPin, 0);
}

void test_horizontal() {
  steps(50, horiz_step_pin, horiz_direction_pin);
  delay(2000);
  steps(-50, horiz_step_pin, horiz_direction_pin);
}

void test_vertical() {
  steps(25, step_pin, direction_pin);
  delay(2000);
  steps(-25, step_pin, direction_pin);
}

void test_servo() {
  for(int i = 180; i >= 0; i--) {
    myservo.write(i);
    delay(15);
  }

  delay(3000);
  myservo.write(180);
}

void loop() {
  test_wheels();
  delay(2000);
  test_horizontal();
  delay(2000);
  test_vertical();
  delay(2000);
  test_servo();
  delay(2000);
}

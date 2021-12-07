//#include <Servo.h> // installed from here: https://www.arduino.cc/reference/en/libraries/servo/
#include <analogWrite.h>

// pins DC motors connected to
const int motorPin = 15; // TODO check PWM

const int horiz_step_pin = SCL;
const int horiz_direction_pin = SDA;

const int vert_step_pin = 32;
const int vert_direction_pin = 14;

const int pusher_step_pin = TX;
const int pusher_direction_pin = 21;

const int limitPin = SDA;

int state = 0;

// create servo object to control a servo
//Servo myservo;

// Pin to control the servo
//const int servo_pin = A5;

void setup() {
  // put your setup code here, to run once:
 // Set up serial communication
 Serial.begin(9600);
 pinMode(motorPin, OUTPUT);
 pinMode(vert_step_pin, OUTPUT);
 pinMode(vert_direction_pin, OUTPUT);
 pinMode(horiz_step_pin, OUTPUT);
 pinMode(horiz_direction_pin, OUTPUT);
 pinMode(pusher_step_pin, OUTPUT);
 pinMode(pusher_direction_pin, OUTPUT);

// myservo.attach(servo_pin, 600, 2400);

// limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
}

// 200 steps for 360 degree
const int STEPS_PER_TURN = 200;

void step(bool forward, int step_pin, int direction_pin) {
  // setting the direction
  if (forward == true) {
    digitalWrite(direction_pin, HIGH);
  } else {
    digitalWrite(direction_pin, LOW);
  }
  // creating a step
  digitalWrite(step_pin, HIGH);
  delayMicroseconds(4);// minimum 1.9us
  digitalWrite(step_pin, LOW);
}

void steps(int number_of_steps, int step_pin, int direction_pin, int delay_between_step_microsec) {
  bool move_forward = true;
  // Establishing the direction
  if (number_of_steps >= 0) {
    move_forward = true;
  } else {
    move_forward = false;
    number_of_steps = -number_of_steps;
  }
  
  // Generating the steps
  for (int i = 0; i < number_of_steps; i++) {
    step(move_forward, step_pin, direction_pin);
    // Delay for proper speed
    delayMicroseconds(delay_between_step_microsec);
  }
}

void test_wheels() {
  analogWrite(motorPin, 60);
  delay(10000);
  analogWrite(motorPin, 0);
  delay(2000);
}

void test_horizontal() {
  steps(50, horiz_step_pin, horiz_direction_pin, 20000);
  delay(2000);
  steps(-50, horiz_step_pin, horiz_direction_pin, 20000);
  delay(2000);
}

void test_pusher() {
  steps(STEPS_PER_TURN / 2, pusher_step_pin, pusher_direction_pin, 5000);
  delay(2000);
}

void test_vertical() {
  steps(25, vert_step_pin, vert_direction_pin, 20000);
  delay(2000);
  steps(-25, vert_step_pin, vert_direction_pin, 20000);
  delay(2000);
}

//void test_servo() {
//  analogWrite(motorPin, 0);
//  for(int i = 180; i >= 0; i--) {
//    myservo.write(i);
//    delay(15);
//  }
//
//  delay(3000);
//  myservo.write(180);
//}

void test_limit_switch() {
  if(digitalRead(limitPin) == HIGH) {
    Serial.println("PRESS");
  }

  delay(5);
}

void loop() {
    test_wheels();
    test_horizontal();
    test_vertical();
    test_pusher();
}

//void wait(int ms) {
//  int curr = millis();
//  while (millis() - curr < ms) {
//    if(digitalRead(buttonPin) == HIGH) {
//      state = (state + 1) % 5;
//      return;
//    }
//    delay(1);
//  }
//}

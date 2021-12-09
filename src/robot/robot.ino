//#include <Servo.h> // installed from here: https://www.arduino.cc/reference/en/libraries/servo/
#include <analogWrite.h>

// pins DC motors connected to
const int motorPin = 15;
float motorSpeed = 40.0;

// stepper pins
const int horiz_step_pin = SCL;
const int horiz_direction_pin = SDA;
const int vert_step_pin = 32;
const int vert_direction_pin = 14;
const int pusher_step_pin = TX;
const int pusher_direction_pin = 21;

// Define pins that read in X/Y values of joystick and the push button
const int xPin = A0;
const int yPin = A1;
const int pushPin = 13;

// Define limit switch pin(s)
const int clockwiseLimitPin = 27;
const int counterclockwiseLimitPin = 12;

// Set the x/y values of the joystick when it is not moved
const int xCalibrate = 1950;
const int yCalibrate = 1950;

// The range from the default x/y values at which a move is registered
const int range = 800;

// bool representing if robot is aiming or not. Determines what happens on button press
bool isAiming = false;

void setup() {
  // Set up serial communication

  // Set up motor and stepper pins
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(vert_step_pin, OUTPUT);
  pinMode(vert_direction_pin, OUTPUT);
  pinMode(horiz_step_pin, OUTPUT);
  pinMode(horiz_direction_pin, OUTPUT);
  pinMode(pusher_step_pin, OUTPUT);
  pinMode(pusher_direction_pin, OUTPUT);

  // joystick button pin
  pinMode(pushPin, INPUT_PULLUP);

  // limit switch pins
  pinMode(clockwiseLimitPin, INPUT_PULLUP);
  pinMode(counterclockwiseLimitPin, INPUT_PULLUP);
}

// 200 steps for 360 degree
const int STEPS_PER_TURN = 200;

// step a stepper by one step in direction forward dependent on given pins
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

// step a stepper with given pins by number_of_steps with a given delay after each step
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

// Set the wheel speed of the motor
void set_wheel_speed(float wheelSpeed) {
  int intSpeed = (int) wheelSpeed;
  analogWrite(motorPin, intSpeed);
}

// Runs the pusher stepper to push ball into wheels
void push_ball() {
  steps(STEPS_PER_TURN / 2, pusher_step_pin, pusher_direction_pin, 5000);
}

void launch_ball() {
  push_ball();
  delay(2000);
  analogWrite(motorPin, 0);
}

// turn the robot left and right if joystick is moved left/right
void horizontal_aim(int yPos) {
  if (yPos > yCalibrate + range) {
    // only allow movement if limit switch is not hit
    if(digitalRead(clockwiseLimitPin) != LOW) {
      steps(1, horiz_step_pin, horiz_direction_pin, 0);
    }
  } else if (yPos < yCalibrate - range) {
    if(digitalRead(counterclockwiseLimitPin) != LOW) {
      steps(-1, horiz_step_pin, horiz_direction_pin, 0);
    }
  }
}

// change DC motor speed if xPos is left/right of joystick initial position
void update_wheel_speed(int xPos) {
  // dc motor speed changing
  if (xPos < xCalibrate - range) {
    // cap motor speed
    if(motorSpeed < 85) {
      motorSpeed += .3;
    }
  } else if (xPos > xCalibrate + range) {
    // stop motor from going to slow
    if(motorSpeed > 40) {
       motorSpeed -=.3;
    }
  }
}

// handle button press by launching ball if robot is aiming, and switching between aiming and off states
void handle_button_press() {
  Serial.println("HI");
  if(digitalRead(pushPin) == LOW) {
    Serial.println("BUTTON PRESS");
    if(isAiming) {
      launch_ball();
      isAiming = false;
    } else {
      isAiming = true;
    }

    delay(300);
  }
}

// aim robot by reading joystick position, and update horizontal location and wheel speed
void aim_robot() {
  int xPos = analogRead(xPin);
  int yPos = analogRead(yPin);
  set_wheel_speed(motorSpeed);
 
  horizontal_aim(yPos);
  update_wheel_speed(xPos);

  delay(30);
}

void loop() {
  // if robot is in aiming mode, allow it to be controlled
  if(isAiming) {
    aim_robot();
  }

  // either way, check for a button press
  handle_button_press();
}



// EVERYTHING BELOW IS DEPRECATED

// Custom delay to check for button press and switch state in the middle of a delay
// void wait(int ms) {
//  int curr = millis();
//  while (millis() - curr < ms) {
//    if(digitalRead(buttonPin) == HIGH) {
//      state = (state + 1) % 5;
//      return;
//    }
//    delay(1);
//  }
//}

// Control the pusher with a servo
// DEPRECATED (using a stepper instead of servo)

// void test_servo() {
//  analogWrite(motorPin, 0);
//  for(int i = 180; i >= 0; i--) {
//    myservo.write(i);
//    delay(15);
//  }
//
//  delay(3000);
//  myservo.write(180);
//}

// vertical aim the launcher by running steps when joystick moved up/down
// DEPRECATED (vertical aiming does not work)
// void vertical_aim() {
//  if (xPos > xCalibrate + range) {
//    steps(3, vert_step_pin, vert_direction_pin, 20000);
//  } else if (xPos < xCalibrate - range) {
//    steps(-3, vert_step_pin, vert_direction_pin, 20000);
//  }
// }

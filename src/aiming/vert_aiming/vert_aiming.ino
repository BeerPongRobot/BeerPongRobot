const int step_pin_1 = 13;
const int direction_pin_1 = 12;
const int step_pin_2 = 15;
const int direction_pin_2 = 32;

// 200 steps for 360 degree
const int STEPS_PER_TURN = 200;

// Adjust the delay for control speed
const int delay_between_step_microsec = 5000;
void setup()
{
 Serial.begin(9600);
 pinMode(step_pin_1, OUTPUT);
 pinMode(direction_pin_1, OUTPUT);
 pinMode(step_pin_2, OUTPUT);
 pinMode(direction_pin_2, OUTPUT);
}

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
void loop()
{
 // Vertical Aiming
 for(int i=0; i<50; i++){
  steps(1, step_pin_1, direction_pin_1);
  steps(1, step_pin_2, direction_pin_2);
  Serial.print(i);
 }
}

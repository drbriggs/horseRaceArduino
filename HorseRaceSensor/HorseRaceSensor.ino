#include <Stepper.h>

#define FROM_CONTROLLER   7 //7 
#define TO_CONTROLLER     8  //8
#define SENSOR1           4
#define SENSOR2           5
#define SENSOR3           6

#define STEPS_PER_REV  2048
#define MOT_SPEED         14
#define TOTAL_STEPS 40UL*2048

int stepsToTurn;
int newSensor1val;
int newSensor2val;
int newSensor3val;
int oldSensor1val = 1;
int oldSensor2val = 1;
int oldSensor3val = 1;
int stepsTaken = 0;
int old_controller = LOW;

Stepper myStepper(STEPS_PER_REV, 10,12,11,13);

void setup() {
  // put your setup code here, to run once:
  myStepper.setSpeed(MOT_SPEED);
  // TODO: set sensors 1-3 as input
  pinMode(SENSOR1, INPUT_PULLUP);
  pinMode(SENSOR2, INPUT_PULLUP);
  pinMode(SENSOR3, INPUT_PULLUP);
  pinMode(FROM_CONTROLLER, INPUT);
  pinMode(TO_CONTROLLER, OUTPUT);
  digitalWrite(TO_CONTROLLER, LOW);
}

void loop() {
  // if game is running
  if(FROM_CONTROLLER == HIGH){
    // readSensors
    newSensor1val = digitalRead(SENSOR1);
    newSensor2val = digitalRead(SENSOR2);
    newSensor3val = digitalRead(SENSOR3);
    
    // if the sensors have recently changed, add turns to step counter
    if (oldSensor1val == 1 && newSensor1val == 0) {
      stepsToTurn += STEPS_PER_REV;
    }
    if (oldSensor2val == 1 && newSensor2val == 0) {
      stepsToTurn += STEPS_PER_REV;
    }
    if (oldSensor3val == 1 && newSensor3val == 0) {
      stepsToTurn += STEPS_PER_REV;
    }

    // if there is still a value on step counter, turn the motor
    if (stepsToTurn > 0) {
      myStepper.step(1);
      stepsTaken++;
      stepsToTurn--;
    }
    // if horse has reached the end of the track, notify the controller
    if (stepsTaken >= TOTAL_STEPS) {
      // This Horse Has Won the Race!!!
      digitalWrite(TO_CONTROLLER, HIGH);
    }

    // set old sensor value to current value for next cycle
    oldSensor1val = newSensor1val;
    oldSensor2val = newSensor2val;
    oldSensor3val = newSensor3val;
  }
  // check if game has recently ended
  // This is interesting to know, but what do we do with it?
  if (old_controller == LOW && digitalRead(FROM_CONTROLLER) == HIGH){
    //digitalWrite(TO_CONTROLLER, HIGH);
  }
  //if game not running
  if(digitalRead(FROM_CONTROLLER) == LOW){
    //and horse not in starting possition 
    if(stepsTaken > 0){
      //move horse back to start
      myStepper.step(-1);
      stepsTaken--;
    }
  }
  //keep track of controller value for next cycle
  old_controller = digitalRead(FROM_CONTROLLER);
}

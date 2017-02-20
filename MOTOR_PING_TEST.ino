#include <AFMotor.h>

#define trigPin 15
#define echoPin 14
//turn
AF_DCMotor motor(1, MOTOR12_64KHZ);
//run
AF_DCMotor motor2(2, MOTOR12_64KHZ);

int maxSpeed = 230;
int turnSpeed = 100;
boolean runningForward = false;
int runSpeed = 200;
int turnDistance = 40;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // turn on motor
  motor.setSpeed(turnSpeed);
  motor2.setSpeed(maxSpeed);
  
  motor.run(RELEASE);
  motor2.run(RELEASE);
  
  randomSeed(millis());
}

void loop() {
  int distance = getDistance();
  if (distance > 0 && distance < turnDistance) {
    byte turnDirection = random(1,3);
    Serial.println(turnDirection);
    while (distance > 0 && distance < turnDistance) {
      turn(turnDirection);
      distance = getDistance();
    }
  } else if (!runningForward) {
    forward(motor2);
  }
  delay(20);
}

int getDistance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  //Serial.println(distance);
  return distance;
}

void forward(AF_DCMotor forwardMotor) {
  forwardMotor.run(FORWARD);
  runningForward = true;
  forwardMotor.setSpeed(maxSpeed);
  Serial.print("Speed: ");
  Serial.println(maxSpeed);
  delay(1000);
  forwardMotor.setSpeed(runSpeed);
  Serial.print("Speed: ");
  Serial.println(runSpeed);
}

//if turnDirection = 1, turn right
//else turn left
void turn(byte turnDirection){
  motor2.run(RELEASE);
  runningForward = false;
  if (turnDirection == 1) {
    motor.run(FORWARD);
    Serial.println("Turn right");
  } else {
    motor.run(BACKWARD);
    Serial.println("Turn left");
  }
  delay(1200);
  motor.run(RELEASE);
}

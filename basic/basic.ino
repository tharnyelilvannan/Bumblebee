#include <Arduino.h>
#include <SparkFun_TB6612.h>

// US initializations
#define ECHO 12
#define TRIG 13
int duration;
int distance;

// IR initializations
#define IR_INPUT 14
int IR_isObstacle = HIGH;

// motor initializations
#define AIN1 2
#define BIN1 4
#define AIN2 3
#define BIN2 5
#define PWMA 10
#define PWMB 11
#define STBY 6
const int offsetA = 1;
const int offsetB = -1;
Motor left_motor = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor right_motor = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {

  Serial.begin(9600);

  // initialize IR
  pinMode(IR_INPUT, INPUT);

  // initialize US
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // ensure trigger is set to low at first
  digitalWrite(TRIG, LOW);

}

void loop() {

  // IR
  IR_isObstacle = digitalRead(IR_INPUT);

  if (IR_isObstacle == LOW)
  {
    Serial.println("White surface 2.");
  }
  else
  {
    Serial.println("Black surface 2.");
  }

  delay(200);

  // US1
  digitalWrite(TRIG, HIGH); // pulse trigger
  delayMicroseconds(10); 
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH); // read echo

  if (duration >= 38000) {

    Serial.print("Out of range"); 

  }
  else
  {
    // calculate distance to object
    distance = duration / 58; 
    Serial.print(distance); 
    Serial.println(" cm");

  }

  delay(1000); 

  
  left_motor.drive(100, 1000);
  right_motor.drive(100, 1000);
  

  delay(1000);

}

#include <Arduino.h>
#include <SparkFun_TB6612.h>

// US1 initializations
#define ECHO1 8 // echo value back 
#define TRIG1 9 // triggers sound output
int duration1; // duration it takes for pulse echo off object and come back
float distance1; // distance to object

// IR1 initializations
#define IR_INPUT1 7 // input pin for IR sensor
int IR_isObstacle1 = HIGH; // for IR sensor, high means yes

// US2 initializations
#define ECHO2 12
#define TRIG2 13
int duration2;
int distance2;

// IR2 initializations
#define IR_INPUT2 14
int IR_isObstacle2 = HIGH;

// motor initializations
#define AIN1 2
#define BIN1 4
#define AIN2 3
#define BIN2 5
#define PWMA 10
#define PWMB 11
#define STBY 6
const int offsetA = 1;
const int offsetB = 1;
Motor left_motor = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor right_motor = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {

  Serial.begin(9600);

  // initialize IR
  pinMode(IR_INPUT1, INPUT);
  pinMode(IR_INPUT2, INPUT);

  // initialize US
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  // ensure trigger is set to low at first
  digitalWrite(TRIG1, LOW);
  digitalWrite(TRIG2, LOW);

}

void loop() {

  // IR1
  IR_isObstacle1 = digitalRead(IR_INPUT1);

  if (IR_isObstacle1 == LOW)
  {
    Serial.println("White surface 1.");
  }
  else
  {
    Serial.println("Black surface 1.");
  }

  delay(200);

  // IR2
  IR_isObstacle2 = digitalRead(IR_INPUT2);

  if (IR_isObstacle2 == LOW)
  {
    Serial.println("White surface 2.");
  }
  else
  {
    Serial.println("Black surface 2.");
  }

  delay(200);

  // US1
  digitalWrite(TRIG1, HIGH); // pulse trigger
  delayMicroseconds(10); 
  digitalWrite(TRIG1, LOW);
  duration1 = pulseIn(ECHO1, HIGH); // read echo

  if (duration1 >= 38000) {

    Serial.print("Out of range"); 

  }
  else
  {
    // calculate distance to object
    distance1 = duration1 / 58; 
    Serial.print(distance1); 
    Serial.println(" cm");

  }

  delay(1000); 


  // US2
  digitalWrite(TRIG2, HIGH); // pulse trigger
  delayMicroseconds(10); 
  digitalWrite(TRIG2, LOW);
  duration2 = pulseIn(ECHO2, HIGH); // read echo

  if (duration2 >= 38000) {

    Serial.print("Out of range"); 

  }
  else
  {
    // calculate distance to object
    distance2 = duration2 / 58; 
    Serial.print(distance2); 
    Serial.println(" cm");

  }

  delay(1000); 

  
  left_motor.drive(100, 1000);
  right_motor.drive(100, 1000);
  

  delay(1000);


}

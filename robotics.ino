#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include <Wire.h>
#include "drive.h"

#define IR_PIN1 A0
#define IR_PIN2 A1
#define motorPIN1 2
#define motorPIN2 3
#define motorPIN3 4 
#define motorPIN4 5
#define motorPIN5 6
#define motorPIN6 7
#define motorPIN7 8
#define motorPIN8 9

#define POS_M 800
#define LOW_THRESHOLD 400
#define HIGH_THRESHOLD 700
int IR_VAL1;
int IR_VAL2;

AccelStepper right(4, motorPIN1, motorPIN3, motorPIN2, motorPIN4);
AccelStepper left(4,motorPIN5,motorPIN7,motorPIN6,motorPIN8);

void foward() {
  right.moveTo(right.currentPosition()+50);
  left.moveTo(left.currentPosition()+50);
  }

void reverse() {
  right.moveTo(right.currentPosition()-50);
  left.moveTo(left.currentPosition()-50);
  }

 void stopcar() {
  right.stop();
  left.stop();
  Serial.println("STOPPED");
  }

void rotate_right() {
  right.moveTo(right.currentPosition()-50);
  left.moveTo(left.currentPosition()+50);
  Serial.println("ROTATE TO RIGHT");
  }

 void rotate_left() {
  right.moveTo(right.currentPosition()+50);
  left.moveTo(left.currentPosition()-50);
  Serial.println("ROTATE TO LEFT"); 
  }

 void wallCheck() {
  foward();
  if (IR_VAL1 < HIGH_THRESHOLD && IR_VAL1 > LOW_THRESHOLD && IR_VAL2 < HIGH_THRESHOLD && IR_VAL2 > LOW_THRESHOLD) {
    
    }
   else {
    wallCheck();
    }
  }
void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN1, INPUT);
  pinMode(IR_PIN2,INPUT);

  right.setMaxSpeed(1200.0);
  right.setAcceleration(110.0);
  right.setSpeed(100.0);
  right.moveTo(POS_M);

  left.setMaxSpeed(1200);
  left.setAcceleration(110.0);
  left.setSpeed(100.0);
  left.moveTo(POS_M);
  Serial.println(dummy());
}

void loop() {
 
  IR_VAL1 = analogRead(IR_PIN1);
  IR_VAL2 = analogRead(IR_PIN2);

    
  right.run();
  left.run();

  DEBUG_CHECK(IR_VAL1,IR_VAL2,left,distanceToGo(),right.distanceToGo());
  delay(15);
}

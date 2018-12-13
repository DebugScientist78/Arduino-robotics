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
#define HIGH_THRESHOLD 900
int IR_VAL1;
int IR_VAL2;
bool wall_level;

AccelStepper right(4, motorPIN1, motorPIN3, motorPIN2, motorPIN4);
AccelStepper left(4,motorPIN5,motorPIN7,motorPIN6,motorPIN8);

bool Wall_seen(int val1, int val2) {
  if (val1 < HIGH_THRESHOLD && val1 > LOW_THRESHOLD && val2 < HIGH_THRESHOLD && val2 > LOW_THRESHOLD) {
    return true;
    }
   else {
    return false;
    }
  }


void foward(int n) {
  right.move(right.currentPosition()+200*n);
  left.move(left.currentPosition()+200);
  }

void reverse(int n) {
  right.move(right.currentPosition()-200*n);
  left.move(left.currentPosition()-200*n);
  }

 void stopcar() {
  right.stop();
  left.stop();
  Serial.println("STOPPED");
  }

void rotate_right() {
  right.move(right.currentPosition()-200);
  left.move(left.currentPosition()+200);
  Serial.println("ROTATE TO RIGHT");
  }

 void rotate_left() {
  right.move(right.currentPosition()+200);
  left.move(left.currentPosition()-200);
  Serial.println("ROTATE TO LEFT"); 
  }

 void wallCheck(bool left_preformed) {
  foward(1);
  IR_VAL1 = analogRead(IR_PIN1);
  IR_VAL2 = analogRead(IR_PIN2);
  if (Wall_seen(IR_VAL1,IR_VAL2)) {
    /*
     * check left, then check right 
     */
     reverse(3);
     Serial.println("CONDITION #1");
     if (!left_preformed) {
      rotate_left();
      Serial.println("CONDITION #2");
      foward(1);
      wall_level = true;
      wallCheck(wall_level);
      }
      else {
        rotate_right();
        Serial.println("CONDITION #3");
        wall_level = false;
        return;
        }
    }
   else {
    return;
    }
    Serial.println("-------------------------------");
  }
void setup() {
  wall_level = false;
  Serial.begin(9600);
  pinMode(IR_PIN1, INPUT);
  pinMode(IR_PIN2,INPUT);

  right.setMaxSpeed(120000.0);
  right.setAcceleration(1000.0);
  right.setSpeed(1000.0);
  right.moveTo(POS_M);

  left.setMaxSpeed(120000);
  left.setAcceleration(1000.0);
  left.setSpeed(1000.0);
  left.moveTo(POS_M);
  Serial.println(dummy());
}

void loop() {
 
  IR_VAL1 = analogRead(IR_PIN1);
  IR_VAL2 = analogRead(IR_PIN2);

  right.run();
  left.run();

  wallCheck(wall_level);

  //DEBUG_CHECK(IR_VAL1,IR_VAL2,left.distanceToGo(),right.distanceToGo());
  delay(30);
}

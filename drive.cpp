#include <AccelStepper.h>
#include <Wire.h>
#include "drive.h"
#include "Arduino.h"

char* dummy() {
  return "Hello World!";
 }

 void drive_foward(int position,AccelStepper mot) {
  Serial.println("BEGIN");
  mot.moveTo(mot.currentPosition()+position);
  mot.run();
  Serial.println("END");
 }

void DEBUG_CHECK(int IR1, int IR2, int posTogo) {
  if (Serial) {
    Serial.print("IR1: ");
    Serial.println(IR1);
    Serial.print("IR2: ");
    Serial.println(IR2);

    
    }
  }

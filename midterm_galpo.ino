/*=====================================================
             IR SENSOR OBJECT COUNTER
======================================================
Description:
  Counts objects detected by an IR sensor and displays
  the count on two seven-segment displays and Serial Monitor.

Programmer:
  De Asis, Felicity M.
  Dela Torre, Shanna Dale R.
  Galpo, Rhile L.

Date:
  15 October 2026
------------------------------------------------------*/
#include "decoder.h"

// GPIOS
const uint8_t IR = 36;
const uint8_t SW1 = 15;
const uint8_t SW2 = 2;

// VARIABLES
int counter = 0;
int input = HIGH;
int previousInput = HIGH;

int SW1_state = 0;
int SW2_state = 0;
int change = 1;

void setup() {

  // IR SENSOR
  pinMode(IR, INPUT);

  // SWITCHES
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);

  // SEVEN-SEGMENT DISPLAYS
  decoderSetup();

  Serial.begin(9600);

  // INITIAL DISPLAY
  decoder(counter);

  // READ INITIAL SENSOR STATE
  previousInput = digitalRead(IR);
}

void loop() {

  // READ SWITCHES
  SW1_state = digitalRead(SW1);
  SW2_state = digitalRead(SW2);

 
 
  // SELECT COUNTING MODE
  if (SW1_state == 0 && SW2_state == 0) {
    change = 1;
  }
  else if (SW1_state == 0 && SW2_state == 1) {
    change = -1;

  }
  else if (SW1_state == 1 && SW2_state == 0) {
    change = 2;
  }
  else {
    change = -2;
  }


  // READ IR SENSOR
  input = digitalRead(IR);

  // COUNT ONLY ON A NEW DETECTION
  if (previousInput == HIGH && input == LOW) {

    counter = counter + change;

    // LIMIT COUNTER FROM 00 TO 99
    if (counter < 0) {
      counter = 0;
    }
    else if (counter > 99) {
      counter = 99;
    }

    // UPDATE DISPLAYS
    decoder(counter);

    // SERIAL MONITOR
    Serial.printf("Object Count: %02d\n", counter);
  }

  // SAVE CURRENT SENSOR STATE
  previousInput = input;

  delay(20);
}

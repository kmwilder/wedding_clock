#include <Servo.h>
#include "pitches.h"

Servo myServo;

//==================================
// Pin Assignments
//==================================
const int servoPin = 9;
const int soundPin = 10;
const int triggerPin = 2;
const int resetPin = 3;

//==================================
// Song Definition
//==================================
int numNotes = 8;

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


//==================================
// Arduino core functions
//==================================
void setup() {
  pinMode(triggerPin, INPUT); 
  pinMode(resetPin, INPUT);
}

bool triggered = true;

void loop() {
  
  int triggerState = digitalRead(triggerPin);
  int resetState = digitalRead(resetPin); // pushbutton, normally open

  if(!triggered && triggerState) {
    triggered = true;
    quietServo(0);
    //playSong();
    delay(1000);
    
  } else if(triggered && resetState == LOW) {
    triggered = false;
    quietServo(90);
    delay(1000);
  }

}

//==================================
// Helper Functions
//==================================

// Our servo buzzes indefinitely after giving it a position.
// Workaround: only drive servo input while it's moving.
void quietServo(int pos) {
  myServo.attach(servoPin);
  myServo.write(pos);
  delay(500);
  myServo.detach();
}

// Taken from toneMelody
// http://www.arduino.cc/en/Tutorial/Tone
void playSong() {
  
   // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(soundPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(soundPin);
  }
}


/* PUMPKIN DROID | HALLOWEEN HACK CODE!!
 *
 * This program sets up a servo to move BB-8's head, 
 * hooks up LEDs and a buzzer to a photoresistor to
 * trigger BB-8 when the lights are off. 
 * 
 * Have fun =)
 *
 * This file is part of the Estefannie Explains It All repo.
 *
 * (c) Estefannie Explains It All <estefannieexplainsitall@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include <Servo.h>
#include "pitches.h"

// I am defining the note for the buzzer
// check out the header filed included to 
// make your own sounds! Pitch.h is from
// "toneMelody" in the examples in Arduino.cc
#define NOTE_B0  31

// create a servo object to control BB-8's head
Servo myservo; 
int servoPostiton;

//photoresistor - controls when BB-8's sounds and lights go off
int photoresistorPin;    
int photoresistorValue;

//LEDs and BUZZER pin
int ledBuzzerPin;

void setup() {

    //initializing.. 
    servoPostiton = 0;
    //input pin for the photoresistor
    photoresistorPin = A0;
    ledBuzzerPin = 13;
    photoresistorValue = 0;

    //initialize serial communications at 9600 bps
    Serial.begin(9600);  
    
    //attaches the servo on pin 9 to the servo object
    myservo.attach(9);  
}

void loop() {
  
  //reading value from the photoresistor
  photoresistorValue = analogRead(photoresistorPin);

  //50 is a threshold I set for a normal semi-dimmed light
  //you can change to a higher threshold if the pumpkin 
  //will be in a bright place
  if (photoresistorValue < 50)
  {
    //quarter note = 1000 / 4
    int noteDuration = 1000 / 4;
    tone(3, NOTE_B0, noteDuration);
    
    //servo!!!
    myservo.write(90);
    delay(8 * 90);
    myservo.write(270);
    delay(8 * 180);
    myservo.write(180);
  }
}


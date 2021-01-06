/* SMART GINGERBREAD HOUSE
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

//Wiring
const int doorServoPin = 9
const int gingerbreadMenServosPin = 3

int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
int tempo = 200;
int song = 0;
int lightsBlink = 0;
int dance = 0;
int doorOpen = 0;

int spin = 1;

int incomingByte = 0;   // for incoming serial data

// create a servo object to control servos
Servo doorServo; 
Servo gingerbreadMenServos;
int servoPosition;
int pos = 0;    // variable to store the servo position

int musicPlaying = 0;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(13, HIGH);
    digitalWrite(6, HIGH);
    delayMicroseconds(tone);
    digitalWrite(13, LOW);
    digitalWrite(6, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        pinMode(13, OUTPUT);
        pinMode(11, OUTPUT);
        pinMode(6, OUTPUT);

        servoPosition = 0;
        doorServo.attach(doorServoPin);
        gingerbreadMenServos.attach(gingerbreadMenServosPin);
}

int doorState = 0;
int danceState = 0;
int lightState = 0;

long prev_door = 0;
long prev_dance = 0;
long prev_light = 0;

long door_dt = 0;
long dance_dt = 0;
long light_dt = 0;

void loop() {
  
  unsigned long dt = millis();
  
        if (musicPlaying == 1)
        {
          if (notes[song] == ' ') 
          {
              delay(beats[song] * tempo); // rest
          }
          else 
          {
              playNote(notes[song], beats[song] * tempo);
          }
          // pause between notes
          delay(tempo / 2);

          song++;

          if (song >= length)
            song = 0;
        }

        if (lightsBlink == 1 && musicPlaying == 0) {
          if (lightState == 0) {
           digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
            if ((dt - light_dt) - prev_light > 1000)
            {
              prev_light = (dt - light_dt);
              lightState = 1;
            }
          }
          if (lightState == 1) {
           digitalWrite(6, LOW);   // turn the LED on (HIGH is the voltage level)
           if ((dt - light_dt) - prev_light > 1000)
           {
            prev_light = (dt - light_dt);
            lightState = 0;
           }
          }
        }

        if (dance == 1) {
          //Serial.print("Dance!");
          gingerbreadMenServos.write(pos);              // tell servo to go to position in variable 'pos'
          if ((dt - dance_dt) - prev_dance > 1) {
            pos++;
            prev_dance = (dt - dance_dt);
          }
          //delay(3);                       // waits 15ms for the servo to reach the position
          pos++;
          if (pos >= 360)
            pos = 0;
        }
        else if (dance == 0) {
          gingerbreadMenServos.write(pos);
        }

        if (doorOpen == 1) {
          if (doorState == 0)
          {
              doorServo.write(90);
              if ((dt - door_dt) - prev_door > 8 * 90)
              {
                prev_door = (dt - door_dt);
                doorState = 1;
                Serial.print(doorState);
              }
          }
          if (doorState == 1)
          {
              doorServo.write(270);
              if ((dt - door_dt) - prev_door > 8 * 180)
              {
                prev_door = (dt - door_dt);
                doorState = 2;
                Serial.print(doorState);
              }
          }
          if (doorState == 2)
          {
              doorServo.write(180);
              doorState = 3;//done
              Serial.print(doorState);
          }
        }
        else if (doorOpen == 0) {
          if (doorState == 0)
          {
              doorServo.write(180);
              if ((dt - door_dt) - prev_door > 8 * 90)
              {
                prev_door = (dt - door_dt);
                doorState = 1;
                Serial.print(doorState);
              }
          }
          if (doorState == 1)
          {
              doorServo.write(270);
              if ((dt - door_dt) - prev_door > 8 * 180)
              {
                prev_door = (dt - door_dt);
                doorState = 2;
                Serial.print(doorState);
              }
          }
          if (doorState == 2)
          {
              doorServo.write(90);
              doorState = 3;//done
              Serial.print(doorState);
          }
        }

        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);

                if (incomingByte == 'E')
                {
                  // everything on
                  digitalWrite(13, HIGH);
                  
                  musicPlaying = 1;
                  
                  digitalWrite(11, HIGH);
                  
                  lightsBlink = 1;
                  light_dt = dt;
                  prev_light = 0;
                  
                  dance = 1;
                  dance_dt = dt;
                  prev_dance = 0;
                  
                  doorOpen = 1;
                  door_dt = dt;
                  prev_door = 0;
                  doorState = 0;
                }
                else if (incomingByte == 'N')
                {
                  // everything off
                  digitalWrite(13, LOW);
                  
                  musicPlaying = 0;
                  
                  digitalWrite(11, LOW);
                  
                  lightsBlink = 0;
                  light_dt = dt;
                  prev_light = 0;
                  
                  dance = 0;
                  dance_dt = dt;
                  prev_dance = 0;
                  
                  doorOpen = 0;
                  door_dt = dt;
                  prev_door = 0;
                  doorState = 0;
                }

                //lights that turn on with the music's beats!
                if(incomingByte == 'H')
                {
                    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                }
                else if(incomingByte == 'L')
                {
                    digitalWrite(13, LOW);   // turn the LED off
                }
                
                //Turning the music on
                else if(incomingByte == 'J')
                {
                    musicPlaying = 1;
                }
                
                else if(incomingByte == 'B')
                {
                    musicPlaying = 0; 
                }
                
                //Opening the front door
                else if(incomingByte == 'D')
                {
                  doorOpen = 1;
                  door_dt = dt;
                  prev_door = 0;
                  doorState = 0;
                }
                //Closing the front door
                else if(incomingByte == 'F')
                {
            
                  Serial.println("Close Door");
                  doorOpen = 0;
                  door_dt = dt;
                  prev_door = 0;
                  doorState = 0;
                }
                
                //Lights inside the gingerbread house
                if(incomingByte == 'I')
                {
                    digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
                }
                else if(incomingByte == 'P')
                {
                    digitalWrite(11, LOW);   // turn the LED off
                }
                
                //Christmas Lights
                if(incomingByte == 'C')
                {
                  lightsBlink = 1;
                  light_dt = dt;
                  prev_light = 0;
                }
                else if(incomingByte == 'O')
                {
                  lightsBlink = 0;
                  light_dt = dt;
                  prev_light = 0;
                  if (musicPlaying == 0) {
                    digitalWrite(6, LOW);
                  }
                }
                
                //moving Trees and Gingerbread Men
                if(incomingByte == 'M')
                {
                  dance = 1;
                  dance_dt = dt;
                  prev_dance = 0;
                }
                
                //stop moving
                else if(incomingByte == 'G')
                {
                  dance = 0;
                  dance_dt = dt;
                  prev_dance = 0;
                }
        }
}
 

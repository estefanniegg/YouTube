/* 
Pokeball 

This is a simple program that 
moved the servo's head from 0 to 180
without delays to create the desired motion.

Have fun =)

This file is part of the Estefannie Explains It All repo.

*/

#include <Servo.h>

Servo myservo;

int pos = 0;

void setup() 
{
  myservo.attach(9);
}

void loop() 
{
  myservo.write(180);
  myservo.write(0);
}



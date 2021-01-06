
/* SCR4P-E THE ROBOT
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
/**************************************** DATE STUFF**********************/
#include <TM1637Display.h>
#include "RTClib.h"
// Define the connections pins for display:
#define CLK A3
#define DIO 11
TM1637Display display = TM1637Display(CLK, DIO);
RTC_DS3231 rtc;

//doom date
int armageddonMonth = 12;
int armageddonDay = 31;
int armageddonYear = 2020;
int armageddon = 0;

///**************************************** MOTORs STUFF**********************/
#include <Servo.h>
Servo servo1;
Servo servo2; 
int pos = 0; 

// Motor A connections
int enA = 6;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4; 
//// Mini motor to move eyes 
int mini_A1A = 12;
int mini_A1B = 13;

long randomSpeedA;
long randomSpeedB;
long randomDir;
//
void setup() {

  Serial.begin(9600);

/**************************************** DATE STUFF**********************/
  display.setBrightness(7);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

 /**************************************** MOTOR STUFF**********************/ 


  servo2.attach(A1); 

  //DC MOTORS
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(mini_A1A,OUTPUT);
  pinMode(mini_A1B,OUTPUT);   

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(mini_A1A, LOW);
  digitalWrite(mini_A1B, LOW);

  randomSeed(analogRead(0));
}

/****************************************DC MOTOR STUFF**********************/
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  digitalWrite(mini_A1A,HIGH);
  digitalWrite(mini_A1B,LOW); 
  delay(2000);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);

  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);

  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  digitalWrite(mini_A1A,LOW);
  digitalWrite(mini_A1B,LOW); 

}

// This function lets you control speed of the motors
void speedControl() {
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  
  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }

  
  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}


void randomMove()
{
    randomDir = random(1, 3);

    randomSpeedA = random(100, 255);
    randomSpeedB = random(100, 255);

    if (randomDir == 1)
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    }
    else if (randomDir == 2)
    {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
    }
    else if (randomDir == 3)
    {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
    }

    analogWrite(enA, randomSpeedA);
    analogWrite(enB, randomSpeedB);

    delay(4000);

    // Now turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    analogWrite(enA, 0);
    analogWrite(enB, 0);
}

void moveArm()
{
     servo2.write(180); 
    delay (100);// tell servo to go to position in variable 'pos'
    servo2.write(0); 
    delay(  100);// tell servo to go to position in variable 'pos'
}

/**************************************** DATE STUFF**********************/
//magic code i copied from the internet
int dateDifference(int year1, int month1, int day1, int year2, int month2, int day2)
{
    int ref,dd1,dd2;
    ref = year1;
    if(year2 < year1)
    {
      ref = year2;
    }  
    dd1 = 0;
    dd1 = dater(month1);    
    for(int i=ref;i<year1;i++)
    {
        if(i%4==0)
        dd1+=1;
    }   
    dd1 = dd1+day1+(year1-ref)*365;
    dd2 = 0;   
    for(int i=ref;i<year2;i++)
    {
        if(i%4==0)
        dd2+=1;
    }   
    dd2=dater(month2)+dd2+day2+((year2-ref)*365);   
    return dd2-dd1;
}
int dater(int x)
{ const int dr[]= { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  return dr[x-1];
}

void displayCounter(){
//get today's date
  DateTime now = rtc.now();
  
  //calculate the number of days left until armageddon
  armageddon = dateDifference(now.year(),now.month(),now.day(), armageddonYear,armageddonMonth,armageddonDay);

  //clear to strt over
  display.clear();
//  // Show doom counter:
  int i;
  for (i = 0; i < armageddon + 1; i++) {
    display.showNumberDec(i);
    delay(50);
  }

  //make sure everyone sees how many days are left
  display.showNumberDec(armageddon);
  delay(1500);

}


///****************************************************************************/

void loop() {

  //delay(3000);

  displayCounter();
  digitalWrite(mini_A1A,HIGH);
  digitalWrite(mini_A1B,LOW); 
  moveArm();

  randomMove();

}

/* INTERNET BUTTON CONTROLLED AUTOMATED FRENCH PRESS
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
#include <InternetButton.h>

InternetButton b = InternetButton();

int buttonPress = 0;
int green(String something);
int none(String something);
int song(String song);
int blue(String blue);

void setup() {
    b.begin();
    Particle.variable("buttonPress",&buttonPress, INT);
    Particle.function("green", green);
    Particle.function("none", none);
    Particle.function("song", song);
    Particle.function("blue", blue);

    b.playSong("C4,8,E4,8,G4,8,C5,8,G5,4"); fjfle rij 
}

void loop() {
    //if any of the buttons is pressed, turn all LEDs to rainbow 
    if(b.buttonOn(1) || b.buttonOn(2) || b.buttonOn(3) || b.buttonOn(4))
    {
        b.advanceRainbow(10, 10);
        b.allLedsOn(255, 0, 255);
        buttonPress = 1;
    }
    else
    {
        buttonPress = 0; 
    }
}

//turn all the lights green 
int green(String something)
{
    b.allLedsOn(0, 255, 0);
    return 0;
}

//turn all the lights blue
int blue(String something)
{
    b.allLedsOn(0, 0, 255);
    return 0;
}

//turn all LEDs off
int none(String noColor)
{
    b.allLedsOff();
}

//play song
int song(String song)
{
    b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8");
    b.rainbow(10);
    b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8");
}
/* DAFT PUNK HELMET
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

#include <FastLED.h>

#define DATA_LEFTEAR_PIN 1
#define DATA_RIGTHEAR_PIN 2
#define DATA_RIGHT_PIN 3
#define DATA_LEFT_PIN 7
#define BUTTON 4
#define POT A0

// Params for width and height
const uint8_t kMatrixWidth = 4;
const uint8_t kMatrixHeight = 8;
const bool    kMatrixSerpentineLayout = true;

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
#define NUM_LEDONE 1

// Calculates position on string based on coordinates
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
  
  return i;
}

// Define the array of leds
CRGB led_array[NUM_LEDS];
CRGB led_ears[NUM_LEDONE];
int boardLed = 13;

void setup()
{
    Serial.begin(9600);
    pinMode(boardLed, OUTPUT);
    pinMode(BUTTON, INPUT);
    pinMode(POT, INPUT);
    FastLED.addLeds<WS2812B, DATA_LEFT_PIN, GRB>(led_array, NUM_LEDS);
    FastLED.addLeds<WS2812B, DATA_RIGHT_PIN, GRB>(led_array, NUM_LEDS);
}

char readIn;

void clear()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        led_array[i] = CRGB::Black;
    }
    FastLED.show();
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { led_array[i].nscale8(250); } }

void cylon()
{
	static uint8_t hue = 0;

	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS; i++)
    {
		led_array[i] = CHSV(hue++, 255, 255);

		FastLED.show(); 

		fadeall();

		delay(10);
	}

	// Now go in the other direction.  
	for(int i = (NUM_LEDS)-1; i >= 0; i--)
    {
		led_array[i] = CHSV(hue++, 255, 255);
		FastLED.show();

		fadeall();

		delay(10);
	}
}

void lightRow(int row, CRGB color)
{
    for (int i = 0; i < kMatrixWidth; i++)
    {
        led_array[XY(i, row)] = color;                
    }
    FastLED.show();
}

CRGB rainbow[8] = {CRGB::Purple, CRGB::Blue, CRGB::PowderBlue,
                   CRGB::Green, CRGB::LightGreen, CRGB::Yellow,
                   CRGB::Orange, CRGB::Red};

void lightRows(int rows, CRGB color)
{
    for (int i = 0; i < rows; i++)
    {
        lightRow(i, color);
    }
}

void fullColor(CRGB color) // this works
{
    lightRows(kMatrixHeight, color);
}

void fullonRainbow() // this works
{
    for (int i = 0; i < kMatrixHeight; i++)
    {
        lightRow(i, rainbow[i]);
    }
}

void rainbowDrop()
{
    // drop in
    for (int i = 0; i < kMatrixHeight; i++)
    {
        CRGB currentColor = rainbow[kMatrixHeight - i];
        
        int currentPosition = kMatrixHeight;
        int previousPosition = currentPosition + 1;

        while(currentPosition > i)
        {
            currentPosition = currentPosition - 1;
            previousPosition = currentPosition + 1;

            lightRow(currentPosition, currentColor);
            if (previousPosition <= (kMatrixHeight - 1))
            {
                lightRow(previousPosition, CRGB::Black);
            }
            FastLED.show();
            delay(100);          
        }
    }

    // clear out
    for (int i = 0; i < kMatrixHeight; i++)
    {
        CRGB currentColor = rainbow[kMatrixHeight - i];
        
        int currentPosition = i;
        int previousPosition = currentPosition - 1;

        while(currentPosition >= -1)
        {
            currentPosition = currentPosition - 1;
            previousPosition = currentPosition + 1;

            if (currentPosition != -1)
            {
                lightRow(currentPosition, currentColor);
            }
            lightRow(previousPosition, CRGB::Black);

            FastLED.show();
            delay(100);          
        }
    }
}

int cycleColor = 0;
void rainbowCycle()
{
    CRGB currentColor = rainbow[cycleColor];
    cycleColor++;

    if (cycleColor > 7)
    {
        cycleColor = 0;
    }

    int currentPosition = kMatrixHeight;
    int previousPosition = currentPosition + 1;

    while(currentPosition > -1)
    {
        currentPosition = currentPosition - 1;
        previousPosition = currentPosition + 1;

        if (currentPosition > -1)
        {
            lightRow(currentPosition, currentColor);            
        }
        if (previousPosition <= (kMatrixHeight - 1))
        {
            lightRow(previousPosition, CRGB::Black);
        }
        FastLED.show();
        delay(100);          
    }
}

void bounce()
{
    CRGB currentColor = rainbow[cycleColor];
    cycleColor++;

    if (cycleColor > 7)
    {
        cycleColor = 0;
    }

    int bounceDistance = 3;
    int bottomArray[] = {0, 1, 2};
    int topArray[] = {kMatrixHeight - 1,  kMatrixHeight - 2, kMatrixHeight -3};

    for (int i = 0; i < bounceDistance; i++)
    {
        lightRow(topArray[i], currentColor);    
        lightRow(bottomArray[i], currentColor);
        FastLED.show();
        delay(100);       
    }

    for (int i = bounceDistance; i >= 0; i--)
    {
        lightRow(topArray[i], CRGB::Black);    
        lightRow(bottomArray[i], CRGB::Black);
        FastLED.show();
        delay(100);       
    }
}

enum Mode
{
    Solid,
    Animation1,
    Animation2,
    Animation3,
    Animation4,
    Audio1,
    Audio2,
    Audio3
};

Mode mode = Animation2;
int low, mid, high;
int bassCount = 0;
void loop() {
    while (Serial.available() > 0)
    {
        readIn = Serial.read();
        if (readIn == 's')
        {
            low = Serial.parseInt();
            mid = Serial.parseInt();
            high = Serial.parseInt();
            break;
        }    
    }

    // use pot to select mode
    int potVal = analogRead(POT);
    Mode previousMode = mode;
    if (potVal < 128)
    {
        mode = Solid;
    }
    else if (potVal >= 128 && potVal < 256)
    {
        mode = Animation1;
    }
    else if (potVal >= 256 && potVal < 384)
    {
        mode = Animation2;
    }
    else if (potVal >= 384 && potVal < 512)
    {
        mode = Animation3;
    }
    else if (potVal >= 512 && potVal < 640)
    {
        mode = Animation4;
    }
    else if (potVal >= 640 && potVal < 768)
    {
        mode = Audio1;
    }
    else if (potVal >= 768 && potVal < 896)
    {
        mode = Audio2;
    }
    else if (potVal >= 896)
    {
        mode = Audio3;
    }

    if (mode != previousMode)
    {
        bassCount++;
    }

    // lighting mode
    switch(mode)
    {
    case Solid:
    {
        fullonRainbow();
        break;
    }
    case Animation1:
    {
        cylon();
        break;
    }
    case Animation2:
    {
        clear();
        bounce();
        clear();
        delay(1000);
        break;
    }
    case Animation3:
    {
        clear();
        rainbowDrop();
        clear();
        break;
    }
    case Animation4:
    {
        clear();
        rainbowCycle();
        clear();
        delay(1000);
        break;
    }
    case Audio1:
    {
        clear();

        if (low > 20)
        {
            bassCount++;
        }

        int colorChoice = bassCount % mode;
        CRGB bassColor = rainbow[colorChoice];

	if (mid > 800)
	{
        	lightRows(8, bassColor);
	}
        else if (mid > 700)
	{
        	lightRows(7, bassColor);
	}
	else if (mid > 600)
        {
        	lightRows(6, bassColor);
        }
        else if (mid > 500)
        {
        	lightRows(5, bassColor);
        }
        else if (mid > 400)
        {
        	lightRows(4, bassColor);
        }
        else if (mid > 300)
        {
        	lightRows(3, bassColor);
        }
        else if (mid > 200)
        {
        	lightRows(2, bassColor);
        }
        else if (mid > 100)
        {
        	lightRows(1, bassColor);
        }
        break;
    }
    case Audio2:
    {
        clear();

        if (mid > 20)
        {
            bassCount++;
        }

        int colorChoice = bassCount % mode;
        CRGB bassColor = rainbow[colorChoice];

        if (low > 20)
	{
        	lightRows(8, bassColor);
	}
        else if (low > 15)
        {
        	lightRows(6, bassColor);
        }
        else if (low > 10)
        {
        	lightRows(4, bassColor);
        }
        else
        {
        	lightRows(2, bassColor);
        }
        break;
    }
    case Audio3:
    {
        clear();

        if (mid > 30)
        {
            bassCount++;
        }

        int colorChoice = bassCount % mode;
        CRGB bassColor = rainbow[colorChoice];

        fullColor(bassColor);
    }
    }

    if (bassCount > 8000)
    {
        bassCount = 0;
    }

}

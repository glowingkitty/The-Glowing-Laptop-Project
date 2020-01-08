#include <Arduino.h>
#include <FastLED.h>

//#define STRIPTYPE NEOPIXEL

const int stripSize = 21;
const int hueStep = 8;
const int segmentSize = 3;
const int showFrom = 0;
constexpr uint8_t stripPin = 3;

const int LEDstripLEFT[] = {2,3,4,5,6,7,8,9,10,11,12,13};
const int LEDstripRIGHT[] = {0,1,2,21,20,19,18,17,16,15,14};

CRGB LEDs[stripSize];
int initialHue = 0;
void setup()
{
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, stripPin>(LEDs, int(stripSize));
}

// for color shift moving
void hueShift()
{
  initialHue -= 1;
}

int segmentStart = segmentSize - 1;
void segmentShift()
{
  segmentStart--;
  if (segmentStart < 0)
  {
    segmentStart = segmentSize - 1;
  }
}

// show right and left a glowing ball moving up
void right_and_left_transition()
{
  for (int i = 0; i < 12; i++)
  {
    int left = LEDstripLEFT[i];
    int right = LEDstripRIGHT[i];
    for (int inner_i = 0; inner_i < 30; inner_i++)
    {
      LEDs[inner_i] = CRGB::Black;
      FastLED.show(255);
    }
    LEDs[left] = CRGB::Red;
    LEDs[right] = CRGB::Blue;
    FastLED.show(255);
  }
}

void color_shift_segments_right_and_left()
{
  for (int k = 0; k < 5; k++)
  {
    int hue = initialHue;
    for (int i = 0; i < 12; i++, hue += hueStep)
    {
      int left = LEDstripLEFT[i];
      int right = LEDstripRIGHT[i];
      LEDs[left] = CHSV(hue % 256, 255, 255);
      LEDs[right] = CHSV(hue % 256, 255, 255);
    }
    hueShift();
    FastLED.show(255);
    delay(20);
  }
  segmentShift();
}

void color_shift_circle()
{
  for (int k = 0; k < 5; k++)
  {
    int hue = initialHue;
    for (int i = 0; i < stripSize; i++, hue += hueStep)
    {
      if ((i + segmentStart) % segmentSize < showFrom)
      {
        LEDs[i] = CRGB::Black;
      }
      else
      {
        LEDs[i] = CHSV(hue % 256, 255, 255);
      }
    }
    FastLED.show(100);
    delay(50);
    hueShift();
  }
  segmentShift();
}


void testleds()
{
  for (int i = 0; i < stripSize; i++)
    {
        LEDs[i] = CHSV(255, 255, 255);
        FastLED.show(100);
        delay(100);
    }

  
}

void loop()
{
  // right_and_left_transition();
  color_shift_segments_right_and_left();
  // testleds();
  // color_shift_circle();
}
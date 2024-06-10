
#include <Adafruit_NeoPixel.h>

// Which DATA_PIN on the Arduino is connected to the NeoPixels?
#define DATA_PIN D4  // On Trinket or Gemma, suggest changing this to 1
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 26  // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, DATA_PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 10  // Time (in milliseconds) to pause between pixels

unsigned long previousMillis = 0;
const long interval = DELAYVAL;

void timeLED(int hour, int min);
int *getColor(String color);
void glowColor(String colour);
int *getColor(String colour);
void resetLed(bool dir);
void ledLoop(String colour, bool dir);
void chase(String colour);
void ledSetup();

int *getColor(String colour) {
  static int color[3];

  if (colour == "red") {
    color[0] = 255;
    color[1] = 50;
    color[2] = 10;
  } else if (colour == "green") {
    color[0] = 10;
    color[1] = 255;
    color[2] = 50;
  } else if (colour == "blue") {
    color[0] = 20;
    color[1] = 20;
    color[2] = 200;
  } else if (colour == "yellow") {
    color[0] = 155;
    color[1] = 50;
    color[2] = 155;
  } else if (colour == "white") {
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
  } else if (colour == "black") {
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
  }
  return color;
}
void resetLed(bool dir) {
  if (dir) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      delay(DELAYVAL);
    }
  } else {
    for (int i = NUMPIXELS - 1; i > 0; i--) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      delay(DELAYVAL);
    }
  }
}

void ledLoop(String colour, bool dir) {
  pixels.clear();  // Set all pixel colors to 'off'

  int *color = getColor(colour);

  if (dir) {
    for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(color[0], color[1], color[2]));
      pixels.show();    // Send the updated pixel colors to the hardware.
      delay(DELAYVAL);  // Pause before next pass through loop
    }
    resetLed(1);
  } else {

    for (int i = NUMPIXELS - 1; i > 0; i--) {  // For each pixel...
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(color[0], color[1], color[2]));
      pixels.show();    // Send the updated pixel colors to the hardware.
      delay(DELAYVAL);  // Pause before next pass through loop
    }
    resetLed(0);
  }
}
void chase(String colour) {  // Sets off chase effect with four leds. Led brightness drops by a certain percentage along the chasing leds
  int *color = getColor(colour);
  for (int i = 0; i < NUMPIXELS; i++) {
    // Set the color for the first LED
    pixels.setPixelColor(i, pixels.Color(color[0], color[1], color[2]));

    // Set the color for the second LED
    if (i > 0) {
      pixels.setPixelColor(i - 1, pixels.Color(color[0] * 0.5, color[1] * 0.5, color[2] * 0.5));
    }
    // Set the color for the third LED
    if (i > 1) {
      pixels.setPixelColor(i - 2, pixels.Color(color[0] * 0.75, color[1] * 0.75, color[2] * 0.75));
    }

    pixels.show();
    delay(100);

    // Turn off the LEDs
    if (i > 2) {
      pixels.setPixelColor(i - 3, pixels.Color(0, 0, 0));
    }
    if (i > 1) {
      pixels.setPixelColor(i - 2, pixels.Color(0, 0, 0));
    }
    if (i > 0) {
      pixels.setPixelColor(i - 1, pixels.Color(0, 0, 0));
    }
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }

  pixels.clear();
}
void timeLED(int hour, int min) {
  hour = map(hour, 0, 12, 0, NUMPIXELS);  // Map the first value to the range of the LED strip
  min = map(min, 0, 60, 0, NUMPIXELS);    // Map the second value to the range of the LED strip

  pixels.clear();  // Clear the strip

  pixels.setPixelColor(hour, pixels.Color(50, 20, 255));  // Set the first LED to blue
  pixels.setPixelColor(hour - 1, pixels.Color(25, 10, 155));
  pixels.setPixelColor(hour + 1, pixels.Color(25, 10, 155));
  pixels.show();
  pixels.setPixelColor(min, pixels.Color(50, 255, 20));  // Set the second LED to green
  pixels.setPixelColor(min - 1, pixels.Color(25, 10, 155));
  pixels.setPixelColor(min + 1, pixels.Color(25, 10, 155));
  pixels.show();  // Update the strip
}

void ledSetup() {
  pixels.begin();  // INITIALIZE NeoPixel pixel object (REQUIRED)
  pixels.setBrightness(100);
  chase("green");
  pixels.clear();
}

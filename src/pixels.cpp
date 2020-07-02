#include "pixels.h"

#define PIXEL_PIN D3
#define NUMPIXELS 12
Adafruit_NeoPixel pixels(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setupPixels() {
    pixels.begin();
}

void clearPixels() {
    pixels.clear();
}

void setAllPixels(int r, int g, int b) {
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
  }
}

void setPixel(int index, int r, int g, int b) {
  pixels.clear();
  pixels.setPixelColor(index, pixels.Color(r, g, b));
  pixels.show();
}


// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void chasePixels(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      pixels.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<pixels.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / pixels.numPixels();
        uint32_t color = pixels.gamma32(pixels.ColorHSV(hue)); // hue -> RGB
        pixels.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      pixels.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void blinkPixels(int r, int g, int b, int times) {
  for(int i=0; i<times; i++) {
    setAllPixels(r, g, b);
    delay(500);
    setAllPixels(0, 0, 0);
    delay(500);
  }
}

/*  0: red    (255, 0, 0)
    5: yellow (255, 255, 0)
    10: green  (0, 255, 0)
 */
void fadePixels(int score){
  int r, g, b;
  r = 510 - score*51;
  g = score*51;
  b = 0;

  if(r > 255) {
    r = 255;
  }
  if(g > 255) {
    g = 255;
  }

  setAllPixels(r, g, b);
}
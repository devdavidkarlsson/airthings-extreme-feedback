#ifndef pixels_h
#define pixels_h

#include <Adafruit_NeoPixel.h>

void setupPixels();
void clearPixels();
void setAllPixels(int r, int g, int b);
void setPixel(int index, int r, int g, int b);
void chasePixels(int wait);
void blinkPixels(int r, int g, int b, int times);
void fadePixels(int score);

#endif
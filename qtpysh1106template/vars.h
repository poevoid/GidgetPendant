#pragma once
#include "arrays.h"
#define MAX_FPS 15

#define WHITE 0xFFFF
#define BLACK 0X0000
#define MIC_PIN A0
#define TEXT_HEIGHT 14
#define TEXT_WIDTH 60
#define TWINKLE_WIDTH 7
#define TWINKLE_HEIGHT 7

#define NUMFLAKES 24
#define XPOS 0
#define YPOS 1
#define DELTAY 2
int           pixelInterval = 50;       // Pixel Interval (ms)
uint16_t      pixelNumber = 1;  // Total Number of Pixels
uint16_t      pixelCurrent = 0;         // Pattern Current Pixel Number
int           pixelCycle = 0;           // Pattern Pixel Cycle
int lastsample;
bool textboxleft = true;
bool textboxup = false;
uint32_t prevTime = 0;  // Used for frames-per-second throttle
uint8_t cursorx = 16;
uint8_t cursory = 28;
int threshold = 15000;
int lefttouchvalue;
int righttouchvalue;
bool sensorsPlugged = false;
//int angle=0;

enum class ScreenMode : uint8_t {
  Waveform,
  Watch,
  Probe,
  Twinkles
};
int crudedebounce = 10;
const int bouncedefault = 10;


struct Tape {
  uint8_t firstframe;
  uint8_t framecount;
  uint8_t lastframe;
  uint8_t currentframe;
};
struct Wave {
  int x;
  int y;
};
Tape tape = { 0, 8, 7, 0 };
ScreenMode screen = { ScreenMode::Waveform };
Wave wave = { 0, 0 };
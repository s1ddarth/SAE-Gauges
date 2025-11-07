#ifndef GAUGE_H
#define GAUGE_H

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

// Define colors
#define GAUGE_BG_COLOR TFT_BLACK
#define GAUGE_TICK_COLOR TFT_WHITE
#define GAUGE_NEEDLE_COLOR TFT_RED
#define GAUGE_HIGHLIGHT_COLOR 0x051D // Dark blue for the gauge background
#define GAUGE_TEXT_COLOR TFT_WHITE

#include <TFT_eSPI.h>

extern TFT_eSPI tft;

// Constants for gauge geometry and colors
extern const int gaugeCenterX;
extern const int gaugeCenterY;
extern const int gaugeArcOuter;
extern const int gaugeArcInner;
extern const int tickOuter;
extern const int tickInner;
extern const int needleLength;
extern const int needlePivotRadius;
extern const int textRadius;

extern const int maxSpeed;
extern const int startAngle;
extern const int endAngle;

// Function prototypes
float mapSpeedToAngle(int speed);
void drawGauge();
void drawNeedle(int speed, uint16_t color);
void drawSpeedText(int speed);

#endif

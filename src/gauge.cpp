#include <gauge.h>

// ==========

int gaugeCenterX = SCREEN_WIDTH / 2;
int gaugeCenterY = SCREEN_HEIGHT / 2;

int gaugeArcOuter = 110; // Outer radius of the blue arc
int gaugeArcInner = 95;  // Inner radius of the blue arc

int tickOuter = 93; // Ticks are drawn inside the arc
int tickInner = 88;

int needleLength = 85;     // Needle is short, does NOT overlap ticks or arc
int needlePivotRadius = 8; // Center pivot

int textRadius = 70; // Radius for numbers
// ==========

// Speed settings
int maxSpeed = 240; // Max speed for the gauge
int currentSpeed = 0;
int oldSpeed = 0;

// Gauge angle settings (in degrees)
int startAngle = 135;
int endAngle = 45;
int totalAngle = 360 - startAngle + endAngle;

float mapSpeedToAngle(int speed)
{
  // Map the speed (0-maxSpeed) to the angle range (startAngle to endAngle)
  float angle = map(speed, 0, maxSpeed, startAngle, 360 + endAngle);
  if (angle > 360)
  {
    angle = angle - 360;
  }
  return angle;
}

// =========================================================================
// FUNCTION to draw the static gauge elements
// =========================================================================
void drawGauge()
{
  // Draw the main gauge arc (as a series of thick lines)
  // This gives a nice shaded effect
  for (int i = gaugeArcInner; i <= gaugeArcOuter; i++)
  {
    // Fade from dark blue to black
    uint16_t color = tft.color565(0, 0, map(i, gaugeArcInner, gaugeArcOuter, 60, 0));
    tft.drawArc(gaugeCenterX, gaugeCenterY, i, i - 1, startAngle, endAngle, color, GAUGE_BG_COLOR);
  }

  // Draw tick marks and numbers
  int numTicks = 13; // 0, 20, 40 ... 240
  for (int i = 0; i < numTicks; i++)
  {
    int speed = i * (maxSpeed / (numTicks - 1));
    float angle = mapSpeedToAngle(speed);
    float angleRad = angle * DEG_TO_RAD; // Convert to radians for trig

    // Calculate tick positions (using new geometry)
    float x1 = gaugeCenterX + tickOuter * cos(angleRad);
    float y1 = gaugeCenterY + tickOuter * sin(angleRad);
    float x2 = gaugeCenterX + tickInner * cos(angleRad);
    float y2 = gaugeCenterY + tickInner * sin(angleRad);

    // Calculate text position (using new geometry)
    float xText = gaugeCenterX + textRadius * cos(angleRad);
    float yText = gaugeCenterY + textRadius * sin(angleRad);

    // Draw tick line
    tft.drawLine(x1, y1, x2, y2, GAUGE_TICK_COLOR);

    // Draw text
    tft.setTextColor(GAUGE_TEXT_COLOR, GAUGE_BG_COLOR);
    tft.setTextSize(1);
    // Use drawString with MC_DATUM for perfect centering
    tft.drawString(String(speed), xText, yText);
  }

  // Draw "KM/H" text
  tft.setTextColor(TFT_LIGHTGREY, GAUGE_BG_COLOR);
  tft.setTextSize(2);
  tft.drawString("KM/H", gaugeCenterX, gaugeCenterY + 40);
}

// =========================================================================
// FUNCTION to draw the needle
// =========================================================================
void drawNeedle(int speed, uint16_t color)
{
  float angle = mapSpeedToAngle(speed);
  float angleRad = angle * DEG_TO_RAD;

  // Calculate needle tip (using new geometry)
  float x1 = gaugeCenterX + needleLength * cos(angleRad);
  float y1 = gaugeCenterY + needleLength * sin(angleRad);

  // Calculate needle base (a small triangle)
  float baseRadius = needlePivotRadius;
  float angleRadL = (angle - 90) * DEG_TO_RAD; // 90 deg left
  float angleRadR = (angle + 90) * DEG_TO_RAD; // 90 deg right

  float x2 = gaugeCenterX + baseRadius * cos(angleRadL);
  float y2 = gaugeCenterY + baseRadius * sin(angleRadL);
  float x3 = gaugeCenterX + baseRadius * cos(angleRadR);
  float y3 = gaugeCenterY + baseRadius * sin(angleRadR);

  // Draw the needle (as a filled triangle)
  tft.fillTriangle(x1, y1, x2, y2, x3, y3, color);

  // Draw a center pivot point
  tft.fillCircle(gaugeCenterX, gaugeCenterY, baseRadius - 2, color);

  // This logic is now correct:
  // When drawing, add a border
  // When erasing, the fillCircle above erases the border
  if (color != GAUGE_BG_COLOR)
  {
    tft.drawCircle(gaugeCenterX, gaugeCenterY, baseRadius - 2, TFT_DARKGREY);
  }
}

// =========================================================================
// FUNCTION to draw the speed as text
// =========================================================================
void drawSpeedText(int speed)
{
  // Set text font and size
  tft.setTextColor(GAUGE_TEXT_COLOR, GAUGE_BG_COLOR);

  // Use a sprite for flicker-free text update
  // Create a 100x25 sprite
  TFT_eSprite spr = TFT_eSprite(&tft);
  spr.createSprite(100, 25);
  spr.setTextDatum(MC_DATUM);
  spr.setColorDepth(8); // 8-bit color is fine

  // Fill with background color
  spr.fillSprite(GAUGE_BG_COLOR);

  // Draw the speed string into the sprite
  spr.setTextSize(3);
  spr.drawString(String(speed), 50, 12); // Centered in 100x25 sprite

  // Push the sprite to the screen
  spr.pushSprite(gaugeCenterX - 50, gaugeCenterY + 5);

  // Delete the sprite to free memory
  spr.deleteSprite();
}

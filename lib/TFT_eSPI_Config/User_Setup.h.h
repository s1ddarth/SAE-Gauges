// ************ TFT_eSPI User Setup ************

// Select the driver
#define GC9A01_DRIVER

// Display resolution
#define TFT_WIDTH  240
#define TFT_HEIGHT 240

// SPI pins
#define TFT_MOSI 11
#define TFT_MISO -1   // Not used by GC9A01
#define TFT_SCLK 9
#define TFT_CS   15
#define TFT_DC   14
#define TFT_RST  16
#define TFT_BL   -1   // Backlight pin not connected

// Optional settings
#define SPI_FREQUENCY  40000000  // 40 MHz SPI
#define TFT_RGB_ORDER TFT_RGB

// Touch is not used
#define TOUCH_CS -1

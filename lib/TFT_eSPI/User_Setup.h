// ************ TFT_eSPI User Setup ************

// Select the driver
#define GC9A01_DRIVER

// Display resolution
#define TFT_WIDTH  240
#define TFT_HEIGHT 240

// SPI pins
#define TFT_SCLK 36
#define TFT_MOSI 35
#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8

// Optional settings
#define SPI_FREQUENCY  40000000  // 40 MHz SPI
#define TFT_RGB_ORDER TFT_RGB

// Touch is not used
#define TOUCH_CS -1

# SPARKLEIOT XH-S3E Speedometer

A speedometer application for the SPARKLEIOT XH-S3E microcontroller with serial output monitoring via PlatformIO.

## Hardware Setup

### Board
- **Microcontroller:** SPARKLEIOT XH-S3E (ESP32-S3 based)
- **Carrier Board:** ESP32-S3 WROOM Core Board (WiFi/Bluetooth, 4MB Flash, USB-C)
- **Development Environment:** VSCode + PlatformIO

### USB Connection
**Important:** The SPARKLEIOT XH-S3E has two USB ports labeled **COM** and **USB**. Despite the labeling convention, you must connect to the **USB port** for programming and serial communication. The COM port does not work for uploads or serial monitoring.

- **Programming:** Connect USB-C cable to the **USB port** (not COM) on the dev board
- **Serial Monitor:** Use the same **USB port** connection
- **Baud Rate:** 115200

## Software Requirements

- VSCode
- PlatformIO CLI or PlatformIO Extension for VSCode
- Espressif32 platform (v6.5.0+)
- Arduino framework

## Installation & Build

1. **Clone the repository:**
   ```bash
   git clone https://github.com/s1ddarth/SAE-Gauges.git
   ```

2. **Install dependencies:**
   ```bash
   pio lib install
   ```

3. **Build the project:**
   ```bash
   pio run -e esp32-s3
   ```

4. **Upload firmware:**
   ```bash
   pio run -e esp32-s3 -t upload
   ```

5. **Open Serial Monitor:**
   ```bash
   pio device monitor -b 115200
   ```

## Configuration

See `platformio.ini` for platform-specific settings:
- **Platform:** espressif32@6.5.0
- **Board:** esp32-s3-devkitc-1
- **Monitor Speed:** 115200 baud
- **Upload Speed:** 460800 baud

### USB Serial Configuration

The firmware includes the following build flags to enable USB serial communication (CDC - Communications Device Class):

```ini
build_flags =
    -DARDUINO_USB_MODE=1
    -DARDUINO_USB_CDC_ON_BOOT=1
```

## Code Structure

- **`src/speedometer.ino`** - Main application code with Hall effect sensor reading and serial output
- **`platformio.ini`** - Project configuration and dependencies
- **`lib/`** - Local libraries (TFT_eSPI user configuration, etc.)

## Features (Planned)

- Hall effect sensor input for speed measurement
- TFT display output (SPI-based, currently commented out)
- Real-time serial monitoring
- Speedometer gauge visualization
- RGB LED control via addressable Neopixel LED

## Hardware: LED Control

The ESP32-S3 WROOM board includes two types of LEDs:

### Power Indicator LED (Red)
- **Status:** Always on when board is powered
- **Controllable:** No (hardwired to power supply)
- Indicates board is receiving USB power

### Addressable RGB LED (Neopixel WS2812B)
- **GPIO Pin:** 48
- **Controllable:** Yes
- **Library:** Requires Adafruit NeoPixel library

### Using the RGB LED

Add the Adafruit NeoPixel library to `platformio.ini`:

```ini
lib_deps =
    bodmer/TFT_eSPI@^2.5.43
    adafruit/Adafruit NeoPixel@^1.12.0
```

**Important:** Do not use `digitalWrite()` for the RGB LED—it requires the NeoPixel library for proper PWM control.

## Troubleshooting

### Serial Monitor Shows No Output

1. **Verify USB connection:** Ensure the USB-C cable is connected to the **USB port**, not the COM port
2. **Check baud rate:** Monitor must be set to 115200
3. **Rebuild with flags:** Ensure `build_flags` are present in `platformio.ini` for USB CDC support
4. **Reset board:** Press the RESET button on the board after opening the serial monitor

### Upload Fails with "Operation timed out"

1. Try a different USB-C cable (cable quality issues are common)
2. Use a different USB-C port
3. Reduce upload speed in `platformio.ini`:
   ```ini
   upload_speed = 115200
   ```
4. Manually reset the board during upload:
   - Click Upload in PlatformIO
   - When "Connecting..." appears, press the RESET button
   - Release when upload begins

## Development Notes

- The TFT display configuration requires SPI pins to be correctly mapped; see User_Setup.h
- Sensor pin configuration for the Hall effect sensor is currently commented out (pin 4)
- The application initializes at 115200 baud with a 1-second startup delay
- The RGB LED on GPIO 48 is addressable (WS2812B) and requires the Adafruit NeoPixel library

## Resources

- [ESP32-S3 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/)
- [PlatformIO Documentation](https://docs.platformio.org/)
- [Arduino Framework](https://www.arduino.cc/)
- [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)

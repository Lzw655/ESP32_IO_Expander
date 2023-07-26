# ESP32_IO_Expander

ESP32_IO_Expander is a versatile library designed to drive IO expander chips with ESP32. It is based on [Arduino-ESP32](https://github.com/espressif/arduino-esp32) (or [ESP-IDF](https://github.com/espressif/esp-idf)) and utilizes [Espressif Components Registry](https://components.espressif.com/), with various components encapsulated using C++.

## Features

* Supports both Arduino-ESP32 and ESP-IDF SDKs.
* Compatible with various IO expander chips.
* Provides support to control individual IO pins in the same way as Arduino (using pinMode(), digitalRead(), and digitalWrite() functions).
* Allows simultaneous control of multiple IO pins.

## How to Use

```cpp
#include <ESP_IOExpander_Library.h>

// Create an ESP_IOExpander object according to the chip type
ESP_IOExpander *expander = new ESP_IOExpander_TCA95xx_8bit(I2C_NUM_0, ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000, I2C_SCL_PIN, I2C_SDA_PIN);

// Control a single pin (0-31)
expander->pinMode(0, OUTPUT);
expander->digitalWrite(0, HIGH);
expander->digitalWrite(0, LOW);
expander->pinMode(0, INPUT);
int level = expander->digitalRead(0);

// Control multiple pins (IO_EXPANDER_PIN_NUM_0 - IO_EXPANDER_PIN_NUM_31)
expander->multiPinMode(IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1, OUTPUT);
expander->multiDigitalWrite(IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1, HIGH);
expander->multiDigitalWrite(IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1, LOW);
expander->multiPinMode(IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1, INPUT);
uint32_t level = expander->multiDigitalRead(IO_EXPANDER_PIN_NUM_2 | IO_EXPANDER_PIN_NUM_3);
```

## Arduino Example

* [test](examples/test): Demonstrates how to use ESP32_IO_Expander and test all functions.

## SDK Versions

The following tables show the supported SDK versions for ESP32_IO_Expander at different versions.

| **ESP32_IO_Expander** | **Arduino-ESP32** | **ESP-IDF** |
| :-------------------: | :---------------: | :---------: |
|        v1.0.0         | v2.0.9 and later  |   v4.4.5    |

## Supported Drivers

|   **Driver**    |                                         **Version**                                          |
| --------------- | -------------------------------------------------------------------------------------------- |
| Base Component  | [1.0.1](https://components.espressif.com/components/espressif/esp_io_expander)               |
| TCA95xx (8bit)  | [1.0.1](https://components.espressif.com/components/espressif/esp_io_expander_tca9554)       |
| TCA95xx (16bit) | [1.0.0](https://components.espressif.com/components/espressif/esp_io_expander_tca95xx_16bit) |
| HT8574          | [1.0.0](https://components.espressif.com/components/espressif/esp_io_expander_ht8574)        |
/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ESP_IOEXPANDER_H
#define ESP_IOEXPANDER_H

#include <stdint.h>

#include "driver/i2c.h"

#include "base/esp_io_expander.h"

// Refer to `esp32-hal-gpio.h`
#define INPUT             0x01
#define OUTPUT            0x03
#define LOW               0x0
#define HIGH              0x1

class ESP_IOExpander
{
public:
    ESP_IOExpander(i2c_port_t id, uint8_t address, const i2c_config_t *config);
    ESP_IOExpander(i2c_port_t id, uint8_t address, int scl, int sda);
    ESP_IOExpander(i2c_port_t id, uint8_t address);

    void init(void);
    void reset(void);
    void del(void);
    esp_io_expander_handle_t getHandle(void);

    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t val);
    int digitalRead(uint8_t pin);

    void multiPinMode(uint32_t pin_mask, uint8_t mode);
    void multiDigitalWrite(uint32_t pin_mask, uint8_t value);
    uint32_t multiDigitalRead(uint32_t pin_mask);

    void printStatus(void);

    virtual ~ESP_IOExpander() = default;
    virtual void begin(void) = 0;

protected:
    esp_io_expander_handle_t handle;

    // I2C
    i2c_port_t i2c_id;
    i2c_config_t i2c_config;
    uint8_t i2c_address;
    bool i2c_need_init;

};

#endif

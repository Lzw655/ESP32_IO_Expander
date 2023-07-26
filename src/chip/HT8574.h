/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>

#include "driver/i2c.h"
#include "esp_err.h"

#include "../ESP_IOExpander.h"

class ESP_IOExpander_HT8574: public ESP_IOExpander {
public:
    ESP_IOExpander_HT8574(i2c_port_t id, uint8_t address, const i2c_config_t *config): ESP_IOExpander(id, address, config) { };
    ESP_IOExpander_HT8574(i2c_port_t id, uint8_t address, int scl, int sda): ESP_IOExpander(id, address, scl, sda) { };
    ESP_IOExpander_HT8574(i2c_port_t id, uint8_t address): ESP_IOExpander(id, address) { };
    ~ESP_IOExpander_HT8574() override;

    void begin(void) override;
};

/**
 * @brief I2C address of the ht8574
 *
 * The 8-bit address format is as follows:
 *
 *                (Slave Address)
 *     ┌─────────────────┷─────────────────┐
 *  ┌─────┐─────┐─────┐─────┐─────┐─────┐─────┐─────┐
 *  |  0  |  1  |  1  |  1  | A2  | A1  | A0  | R/W |
 *  └─────┘─────┘─────┘─────┘─────┘─────┘─────┘─────┘
 *     └────────┯────────┘     └─────┯──────┘
 *           (Fixed)        (Hareware Selectable)
 *
 * And the 7-bit slave address is the most important data for users.
 * For example, if a chip's A0,A1,A2 are connected to GND, it's 7-bit slave address is 0111000b(0x38).
 * Then users can use `ESP_IO_EXPANDER_I2C_HT8574_ADDRESS_000` to init it.
 */
#define ESP_IO_EXPANDER_I2C_HT8574_ADDRESS_000    (0x38)
#define ESP_IO_EXPANDER_I2C_HT8574_ADDRESS_001    (0x29)
#define ESP_IO_EXPANDER_I2C_HT8574_ADDRESS_010    (0x2A)
#define ESP_IO_EXPANDER_I2C_HT8574_ADDRESS_011    (0x2B)
#define ESP_IO_EXPANDER_I2C_HT8574_ADDRESS_100    (0x2C)

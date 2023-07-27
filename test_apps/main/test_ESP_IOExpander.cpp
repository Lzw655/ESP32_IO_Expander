/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <inttypes.h>

#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "unity.h"
#include "unity_test_runner.h"

#include "ESP_IOExpander_Library.h"

// Refer to `esp32-hal-gpio.h`
#define INPUT             0x01
#define OUTPUT            0x03
#define LOW               0x0
#define HIGH              0x1

static const char *TAG = "ESP_IOxpander_test";

#define I2C_SDA_PIN     (8)
#define I2C_SCL_PIN     (18)

TEST_CASE("test ESP IO expander for TCA9554", "[tca9554]")
{
    ESP_IOExpander *expander = new ESP_IOExpander_TCA95xx_8bit(I2C_NUM_0, ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000, I2C_SCL_PIN, I2C_SDA_PIN);

    expander->init();
    expander->begin();

    ESP_LOGI(TAG, "Original status:");
    expander->printStatus();

    expander->pinMode(0, OUTPUT);
    expander->pinMode(1, OUTPUT);
    expander->multiPinMode(IO_EXPANDER_PIN_NUM_2 | IO_EXPANDER_PIN_NUM_3, OUTPUT);

    ESP_LOGI(TAG, "Set pint 0-3 to output mode:");
    expander->printStatus();

    expander->digitalWrite(0, LOW);
    expander->digitalWrite(1, LOW);
    expander->multiDigitalWrite(IO_EXPANDER_PIN_NUM_2 | IO_EXPANDER_PIN_NUM_3, LOW);

    ESP_LOGI(TAG, "Set pint 0-3 to low level:");
    expander->printStatus();

    expander->pinMode(0, INPUT);
    expander->pinMode(1, INPUT);
    expander->multiPinMode(IO_EXPANDER_PIN_NUM_2 | IO_EXPANDER_PIN_NUM_3, INPUT);

    ESP_LOGI(TAG, "Set pint 0-3 to input mode:");
    expander->printStatus();

    int level[4] = {0, 0, 0, 0};
    uint32_t level_temp;

    // Read pin 0-3 level
    level[0] = expander->digitalRead(0);
    level[1] = expander->digitalRead(1);
    level_temp = expander->multiDigitalRead(IO_EXPANDER_PIN_NUM_2 | IO_EXPANDER_PIN_NUM_3);
    level[2] = level_temp & IO_EXPANDER_PIN_NUM_2 ? HIGH : LOW;
    level[3] = level_temp & IO_EXPANDER_PIN_NUM_3 ? HIGH : LOW;
    ESP_LOGI(TAG, "Pin 0-3 level: %d %d %d %d", level[0], level[1], level[2], level[3]);

    delete expander;
}

// Some resources are lazy allocated in the LCD driver, the threadhold is left for that case
#define TEST_MEMORY_LEAK_THRESHOLD (-300)

static size_t before_free_8bit;
static size_t before_free_32bit;

static void check_leak(size_t before_free, size_t after_free, const char *type)
{
    ssize_t delta = after_free - before_free;
    printf("MALLOC_CAP_%s: Before %u bytes free, After %u bytes free (delta %d)\n", type, before_free, after_free, delta);
    TEST_ASSERT_MESSAGE(delta >= TEST_MEMORY_LEAK_THRESHOLD, "memory leak");
}

void setUp(void)
{
    before_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    before_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
}

void tearDown(void)
{
    size_t after_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    size_t after_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
    check_leak(before_free_8bit, after_free_8bit, "8BIT");
    check_leak(before_free_32bit, after_free_32bit, "32BIT");
}

extern "C" void app_main(void)
{
    //   _____  ___     __                            _
    //   \_   \/___\   /__\_  ___ __   __ _ _ __   __| | ___ _ __
    //    / /\//  //  /_\ \ \/ / '_ \ / _` | '_ \ / _` |/ _ \ '__|
    // /\/ /_/ \_//  //__  >  <| |_) | (_| | | | | (_| |  __/ |
    // \____/\___/   \__/ /_/\_\ .__/ \__,_|_| |_|\__,_|\___|_|
    //                         |_|
    printf("  _____  ___     __                            _\r\n");
    printf("  \\_   \\/___\\   /__\\_  ___ __   __ _ _ __   __| | ___ _ __\r\n");
    printf("   / /\\//  //  /_\\ \\ \\/ / '_ \\ / _` | '_ \\ / _` |/ _ \\ '__|\r\n");
    printf("/\\/ /_/ \\_//  //__  >  <| |_) | (_| | | | | (_| |  __/ |\r\n");
    printf("\\____/\\___/   \\__/ /_/\\_\\ .__/ \\__,_|_| |_|\\__,_|\\___|_|\r\n");
    printf("                        |_|\r\n");
    unity_run_menu();
}

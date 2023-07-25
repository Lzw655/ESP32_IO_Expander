#include <Arduino.h>
#include <ESP_IOExpander_Library.h>

ESP_IOExpander *io_expander;

void setup()
{
    sleep(5);
    Serial.begin(115200);
    Serial.println("Hello world");

    io_expander = new ESP_IOExpander_TCA9554(I2C_NUM_0, ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000, 18, 8);
    io_expander->init();
    io_expander->begin();
}

void loop()
{
    sleep(1);
    Serial.println( "loop" );
}

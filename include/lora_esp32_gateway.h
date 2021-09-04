#ifndef LORA_ESP32_H_
#define LORA_ESP32_H_

#include <Arduino.h>
extern "C" {
    #include <freertos/FreeRTOS.h>
    #include <freertos/task.h>
    #include "esp_system.h"
    #include "driver/uart.h"
    #include "driver/gpio.h"
    #include "freertos/queue.h"
}

enum class STATUS_ESP32 {
    OK,
    ERROR,
    VALID,
    INVALID
};

#endif 
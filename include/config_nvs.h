#ifndef NVS_CPP_H_
#define NVS_CPP_H_
#include <lora_esp32_gateway.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <esp_system.h>
#include <string>

class CONFIG_NVS {
public:
    // init nvs storage
    STATUS_ESP32 begin();

    STATUS_ESP32 write_int(std::string &key, int value);
    STATUS_ESP32 write_string(std::string key, std::string value);

    STATUS_ESP32 read_int(std::string &key, int *read_value);
    STATUS_ESP32 read_string(std::string key, std::string &value);
    STATUS_ESP32 commit();
    void stop();
private:
    char buffer_holder[200]; // to hold data from NVS
    size_t _length = 200;
    nvs_handle _handle;
};

#endif
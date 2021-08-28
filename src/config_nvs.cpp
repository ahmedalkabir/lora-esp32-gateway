#include <Arduino.h>
#include <config_nvs.h>


STATUS_ESP32 CONFIG_NVS::begin(){
    esp_err_t err = nvs_flash_init();

    if(err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND){
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    // i'll use storage namespace this
    // time
    err = nvs_open("storage", NVS_READWRITE, &_handle);
    if(err != ESP_OK){
        return STATUS_ESP32::OK;
    } else {
        return STATUS_ESP32::ERROR;
    }
}

STATUS_ESP32 CONFIG_NVS::write_string(std::string key, std::string value){
    esp_err_t err = nvs_set_str(_handle, key.c_str(), value.c_str());
    if(err == ESP_OK){
        return STATUS_ESP32::OK;
    } else {
        return STATUS_ESP32::ERROR;
    }
}

STATUS_ESP32 CONFIG_NVS::read_string(std::string key, std::string &value){
    esp_err_t err = nvs_get_str(_handle, key.c_str(), buffer_holder, &_length);
    if(err == ESP_OK){
        value = buffer_holder;
        return STATUS_ESP32::OK;
    } else {
        return STATUS_ESP32::ERROR;
    }
}

STATUS_ESP32 CONFIG_NVS::commit(){
    esp_err_t err = nvs_commit(_handle);

    if(err == ESP_OK){
        return STATUS_ESP32::OK;
    } else {
        return STATUS_ESP32::ERROR;
    }
}

void CONFIG_NVS::stop(){
    nvs_close(_handle);
}
#ifndef LORA_H_
#define LORA_H_
#include <lora_esp32_gateway.h>

// C prototypes

// it will setup uart driver
// UART 2 is used and connected to GPIO17 and GPIO16
void setup_lora_medium();

// Receiver Task
void lora_rx_task(void *parameters);

// C++ Class 
class LORA {

public:
    void begin();
    bool is_connected();
    size_t send();
    
};

#endif
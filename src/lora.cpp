#include <lora.h>

static QueueHandle_t uart2_queue;

void LORA::begin(){
    setup_lora_medium();
}

void setup_lora_medium(){
    const uart_config_t uart_lora_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_param_config(UART_NUM_2, &uart_lora_config);

    uart_driver_install(UART_NUM_2, 1024 * 2, 0, 20, &uart2_queue, 0);

    uart_set_pin(UART_NUM_2, GPIO_NUM_0, GPIO_NUM_4, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    xTaskCreate(lora_rx_task, "lora_rx_task", 2048, NULL, configMAX_PRIORITIES, NULL);
}

void send_data(const char *data){
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(UART_NUM_2, data, len);
    Serial.printf("[Wrote %d]\n", txBytes);
}

void lora_rx_task(void *parameters){
    Serial.printf("[lora task]\n");
    uart_event_t event;
    uint8_t recv_buf[100];
    send_data("[lora task started]\n");
    size_t length = 0;
    esp_err_t err;
    while (1)
    {
        // const int rxBytes = uart_read_bytes(UART_NUM_2, recv_buf, 100, 1000 / portTICK_RATE_MS);

        // if(rxBytes > 0){
        //     recv_buf[rxBytes] = 0;
        //     Serial.printf("Read %d bytes: '%s'\n", rxBytes, recv_buf);
        // }

        if(xQueueReceive(uart2_queue, (void *)&event, (portTickType)portMAX_DELAY)){
            switch (event.type)
            {
            case UART_DATA:
                uart_read_bytes(UART_NUM_2, recv_buf, event.size, portMAX_DELAY);

                Serial.print("[ received: ");
                Serial.write(recv_buf, event.size);
                Serial.println("]");
                uart_write_bytes(UART_NUM_2, (const char *)recv_buf, event.size);
                break;
            
            default:
                break;
            }
        }
    }       
}


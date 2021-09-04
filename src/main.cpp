#include <Arduino.h>
#include <lora.h>

LORA lora;

void setup(){
  Serial.begin(115200);
  // setup_lora_medium();
  lora.begin();

}

void loop(){

}
#include "buzzer.h"
#include "pico/stdlib.h"

#define BUZZER_PIN 21
#define VOLUMN_LIMIT 100 //limite de volume para a emissão do alerta

void buzzer_init(){
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

void buzzer_check_alert(int volume){
    if (volume > VOLUMN_LIMIT){
        gpio_put(BUZZER_PIN, 1);
        sleep_ms(500);
        gpio_put(BUZZER_PIN, 0);
    }
}

void buzzer_stop(){
    gpio_put(BUZZER_PIN, 0);
}
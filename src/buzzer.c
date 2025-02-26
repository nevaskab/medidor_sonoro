#include "buzzer.h"
#include "pico/stdlib.h"

#define BUZZER_PIN 21
#define VOLUMN_LIMIT 100 //limite de volume para a emissão do alerta

void buzzer_init(){
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

//função que compara o nível do volume e se for maior que o limite é emitido um alerta
void buzzer_check_alert(int volume){
    if (volume > VOLUMN_LIMIT){
        int duracao_ms = 500;
        while (duracao_ms > 0) {
            gpio_put(BUZZER_PIN, 1);
            sleep_ms(2);
            duracao_ms --;
            gpio_put(BUZZER_PIN, 0);
            sleep_ms(3);
            duracao_ms -=3;
        }
    }
}

void buzzer_stop(){
    gpio_put(BUZZER_PIN, 0);
}
#include "buttons.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "audio.h"
#include "buzzer.h"
#include "display.h"

#define A_BUTTON_PIN   5 //botão A conectado ao GPIO5
#define B_BUTTON_PIN   6 //botão B conectado ao GPIO6
#define DEBOUNCE_DELAY 200
#define NUM_BUTTONS 2

void buttons_init(void) {
    gpio_init(A_BUTTON_PIN);
    gpio_init(B_BUTTON_PIN);
    gpio_set_dir(A_BUTTON_PIN, GPIO_IN);
    gpio_set_dir(B_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(A_BUTTON_PIN);
    gpio_pull_up(B_BUTTON_PIN);

    //função de interrupção sendo chamada para cada botão
    gpio_set_irq_enabled_with_callback(A_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &irq_button);
    gpio_set_irq_enabled_with_callback(B_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &irq_button);
}

//declarei os botões e uma variável com o último tempo para poder criar a função de debounce
const uint32_t gpio_button[NUM_BUTTONS] = {A_BUTTON_PIN, B_BUTTON_PIN};
uint32_t last_time[NUM_BUTTONS] = {0};

//a função de debounce vai analisar CADA UM dos botões e evitar que o botão tenha "trepidação" para não gerar erros de execução
bool debounce(uint gpio) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    int index_button = -1;

    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (gpio_button[i] == gpio) {
            index_button = i;
            break;
        }
    }

    if (index_button == -1) {
        return false;
    }

    if (current_time - last_time[index_button] < DEBOUNCE_DELAY) {
        return false;
    }

    last_time[index_button] = current_time;
    return true;
}

//verifica se o botão A foi pressionado
bool input_is_button_a_pressed(void) {
    return !gpio_get(A_BUTTON_PIN);  //retorna true se o botão estiver pressionado
}

//verifica se o botão B foi pressionado
bool input_is_button_b_pressed(void) {
    return !gpio_get(B_BUTTON_PIN);  //retorna true se o botão estiver pressionado
}

void irq_button(uint gpio, uint32_t events) {

    if(debounce(gpio)){

        //botão A pressionado chama as funções audio_pause e buzzer_stop
        if(gpio == A_BUTTON_PIN){
            audio_pause();
            buzzer_stop();
        }
        //botão B chama as funções audio_reset e display clear
        else if(gpio == B_BUTTON_PIN){
            audio_reset();
            display_clear();
        }
    }
}
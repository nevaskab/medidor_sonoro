#include <stdlib.h>
#include "pico/stdlib.h"
#include "audio.h"
#include "hardware/adc.h"
#include "display.h"
#include "leds.h"
#include "buzzer.h"

#define MIC_PIN 28
#define ADC_CHANNEL 2
#define MID_VALUE 2048
#define MAX_VALUE 4095 
#define SENSE 40

static bool paused = false;
static int current_volumn = 0;
static bool reset = false;
static absolute_time_t reset_start_time;

void audio_init(){
    adc_init();
    adc_gpio_init(MIC_PIN);
    adc_select_input(ADC_CHANNEL);
}

void audio_pause(){
    paused = !paused;
}

void audio_reset(){
    reset = true;
    reset_start_time = get_absolute_time();

    display_show_message("Reiniciando...");

    leds_clear();
    buzzer_stop();
}

bool audio_update(){
    if(reset){
        int64_t elapsed_time = absolute_time_diff_us(reset_start_time,get_absolute_time()) / 1000;
        if(elapsed_time >= 2000){
            reset = false;
            current_volumn = 0;
            paused = false;
            display_show_volumn(current_volumn);
        }
        return true;
    }
    return  false;
}

int audio_get_volumn(){
    if(paused || reset){
        return current_volumn;
    }

    uint16_t raw_value = adc_read();

    int volume = abs(raw_value - MID_VALUE);

    current_volumn = (volume * SENSE) / 100;

    return current_volumn;
}
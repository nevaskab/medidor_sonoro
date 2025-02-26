#include <stdio.h>
#include "pico/stdlib.h"
#include "audio.h"
#include "buzzer.h"
#include "display.h"
#include "buttons.h"
#include "leds.h"

int main() {
    stdio_init_all(); 
    audio_init();     
    buzzer_init();    
    display_init();   
    buttons_init();
    leds_init();

    while (true) {
        if(audio_update()){
            sleep_ms(100);
            continue;
        }

        //pega o som através do microfone
        int volume = audio_get_volumn();

        //atualiza a matriz de LEDs de acordo com a intensidade do som
        leds_graphic_volumn(volume);

        //faz a verificação do volume, caso ultrapasse o limite um alerta é emitido pelo buzzer
        buzzer_check_alert(volume);

        //exibe o volume no display
        display_show_volumn(volume);
    }
}
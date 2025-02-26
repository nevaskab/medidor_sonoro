#include <stdlib.h>
#include "pico/stdlib.h"
#include "leds.h"
#include "hardware/pio.h"
#include "medidor_sonoro.pio.h"

#define MATRIZ_PIN 7
#define MATRIZ_LEDS 25

static PIO pio = pio0;
static uint sm;

//inicializa a PIO da matriz de LEDs 5x5
void leds_init(void) {
    sm = pio_claim_unused_sm(pio, true);
    uint offset = pio_add_program(pio, &medidor_sonoro_program);
    medidor_sonoro_program_init(pio, sm, offset, MATRIZ_PIN);
}

//mapa de LEDs da matriz
static const uint8_t led_matriz[5][5] = {
    {4,  3,  2,  1,  0},
    {5,  6,  7,  8,  9},
    {14, 13, 12, 11, 10},
    {15, 16, 17, 18, 19},
    {24, 23, 22, 21, 20}
};

//função para apagar a matriz de LEDs
void leds_clear(void) {
    uint32_t leds_off = 0x000000 << 8;
    uint32_t matriz_led_buffer[MATRIZ_LEDS];

    for (int i = 0; i < MATRIZ_LEDS; i++) {
        matriz_led_buffer[i] = leds_off;
    }

    for (int i = 0; i < MATRIZ_LEDS; i++) {
        pio_sm_put_blocking(pio, sm, matriz_led_buffer[i]);
    }
}

//exibe o nível de volume na matriz de LEDs
void leds_graphic_volumn(int volume) {
    //cor Tyrian Purple
    uint32_t color = 0x400326;
    //leds desligados
    uint32_t leds_off = 0x000000 << 8;

    //buffer para armazenar o estado dos LEDs
    uint32_t matriz_led_buffer[MATRIZ_LEDS];
    for (int i = 0; i < MATRIZ_LEDS; i++) {
        matriz_led_buffer[i] = leds_off;
    }

    //acende os LEDs correspondentes ao volume
    //esses valores simulam bandas de frequência para que os leds da matriz movimentem diferentemente devido a intensidade do som
    static const float cols_height[5] = {0.8, 1.0, 1.2, 0.9, 1.1};

    for (int num_cols = 0; num_cols < 5; num_cols++) {
        int height = (volume * cols_height[num_cols]) / 100 * 5;

        if(height > 5) {
            height = 5;
        }

        for(int num_rows = 0; num_rows < height; num_rows++){
            int led_index_placa = led_matriz[num_rows][num_cols];
            matriz_led_buffer[led_index_placa] = color;
        }
    }

    //envia os dados para a matriz de LEDs
    for (int i = 0; i < MATRIZ_LEDS; i++) {
        pio_sm_put_blocking(pio, sm, matriz_led_buffer[i]);
    }
}

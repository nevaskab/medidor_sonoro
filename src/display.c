#include <stdio.h>
#include "display.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_ADDRESS 0x3C
#define I2C_PORT i2c1 //a placa bitdoglab utiliza o canal I2C1 por padrão
#define SDA_PIN 14
#define SCL_PIN 15

//declaração da estrutura ssd1306_t
ssd1306_t ssd;

//função que inicializa o display
void display_init() {
    //configura o I2C (display)
    i2c_init(I2C_PORT, 100 * 1000);  // 100 kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    //inicializa o display ssd
    ssd1306_init(&ssd, DISPLAY_WIDTH, DISPLAY_HEIGHT, false, DISPLAY_ADDRESS, I2C_PORT);
    ssd1306_fill(&ssd, false);
    ssd1306_config(&ssd);
}

//função que limpa o display
void display_clear(){
    ssd1306_fill(&ssd, 0);
    ssd1306_send_data(&ssd);
}

//função para escrever outras mensagens desejadas
void display_show_message(const char *message){
    
    ssd1306_fill(&ssd, 0);

    ssd1306_draw_string(&ssd, message, 0, 10);

    ssd1306_send_data(&ssd);

    display_clear();
}

//função que escreve constantemente o valor do volume no display
void display_show_volumn(int volume){
    ssd1306_fill(&ssd, 0);

    char buffer[16];
    buffer[0] = 'V';
    buffer[1] = 'o';
    buffer[2] = 'l';
    buffer[3] = 'u';
    buffer[4] = 'm';
    buffer[5] = 'e';
    buffer[6] = ':';
    buffer[7] = ' ';
    buffer[8] = (volume / 100) + '0';
    buffer[9] = ((volume / 10) % 10) + '0';
    buffer[10] = (volume % 10) + '0';
    buffer[11] = '%';
    buffer[12] = '\0';

    ssd1306_fill(&ssd, 0);

    ssd1306_draw_string(&ssd, buffer, 0, 25);

    ssd1306_send_data(&ssd);

    sleep_ms(500);
}
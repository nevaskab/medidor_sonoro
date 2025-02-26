#ifndef AUDIO_H
#define AUDIO_H
#include <stdbool.h>

void audio_init();
void audio_pause();
void audio_reset();
bool audio_update();
int audio_get_volumn();

#endif
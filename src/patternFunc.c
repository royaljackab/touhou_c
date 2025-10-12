#include "globals.h"
#include "patternFunc.h"

void Pattern_Straight(Bullet* bullet, void* userData) {
    bullet->pos.x += bullet->direction.x * bullet->speed;
    bullet->pos.y += bullet->direction.y * bullet->speed;
}

void Pattern_SineWave(Bullet* bullet, void* userData) {
    float amplitude = 50.0f; // Amplitude of the sine wave
    float frequency = 0.1f;  // Frequency of the sine wave

    bullet->pos.x = sin(2 * 1.f * bullet->timer/60 ) + 3 * sin(1.f * bullet->timer/60);
    bullet->pos.y = 2 * sin(3 * 1.f * bullet->timer/60 );
}
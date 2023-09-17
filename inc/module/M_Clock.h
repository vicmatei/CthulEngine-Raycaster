#pragma once

#include <SDL2/SDL.h>

#include "app/G_defs.h"

struct M_FpsClock {
    double delta;
    double loopStart;
};

void M_FpsClock_Prep(struct M_FpsClock* clock) {
    clock->loopStart = SDL_GetTicks64();
}
void M_FpsClock_Tick(struct M_FpsClock* clock) {
    clock->delta = SDL_GetTicks64() - clock->loopStart;
    if (clock->delta < TARGET_DELTA) { SDL_Delay(TARGET_DELTA - clock->delta); }
}
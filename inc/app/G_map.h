#pragma once

#include <SDL2/SDL.h>

#include "module/M_Renderer.h"

#include "app/G_defs.h"

void G_Map_DrawMap(SDL_Renderer** renderer, int map[], float stroke) {
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            int index = y * MAP_SIZE + x;
            if (map[index] == 1) {
                M_Renderer_DrawRect(renderer,x * TILE_W,y * TILE_H,TILE_W - stroke,TILE_H - stroke,100,100,100);
            } else {
                M_Renderer_DrawRect(renderer,x * TILE_W,y * TILE_H,TILE_W - stroke,TILE_H - stroke,50,50,50);
            }
        }
    }
}
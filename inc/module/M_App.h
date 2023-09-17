#pragma once

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "module/M_Console.h"

#include "app/G_defs.h"

struct M_App {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
};

void M_App_Init(struct M_App* app) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        M_SetStyle(255,0,0);
        printf("SDL failed to initialize: %s\n",SDL_GetError());
        M_ResetStyle();
    }
    if (TTF_Init() < 0) {
        M_SetStyle(255,0,0);
        printf("SDL_ttf failed to initialize: %s\n",TTF_GetError());
        M_ResetStyle();
    }
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN,&app->window,&app->renderer) < 0) {
        M_SetStyle(255,0,0);
        printf("SDL failed to create window and renderer: %s\n",SDL_GetError());
        M_ResetStyle();
    }
    SDL_SetWindowTitle(app->window,WINDOW_TITLE);

    if (TILE_W > TILE_H) {
        #undef MAX_DEPTH
        #define MAX_DEPTH ((int)(TILE_W * MAP_SIZE))
    }
}
void M_App_Close(struct M_App* app) {
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}

void M_App_FillBg(SDL_Renderer** renderer, int r, int g, int b) {
    SDL_SetRenderDrawColor(*renderer,r,g,b,255);
    SDL_RenderClear(*renderer);
}
void M_App_UpdateScreen(SDL_Renderer** renderer) {
    SDL_RenderPresent(*renderer);
}
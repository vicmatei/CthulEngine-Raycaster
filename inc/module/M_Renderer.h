#pragma once

#include <SDL2/SDL.h>

void M_Renderer_DrawRect(SDL_Renderer** renderer, float x, float y, float w, float h, int r, int g, int b) {
    SDL_SetRenderDrawColor(*renderer,r,g,b,255);
    SDL_RenderFillRect(*renderer,&(SDL_Rect){x,y,w,h});
}
void M_Renderer_DrawLine(SDL_Renderer** renderer, float x1, float y1, float x2, float y2, int r, int g, int b) {
    SDL_SetRenderDrawColor(*renderer,r,g,b,255);
    SDL_RenderDrawLine(*renderer,x1,y1,x2,y2);
}
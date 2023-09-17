#pragma once

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

struct M_TextObject {
    SDL_Texture* texture;
    SDL_Rect rect;
    
    int r;
    int g;
    int b;
};

void M_TextObject_Init(SDL_Renderer** renderer, struct M_TextObject* obj, TTF_Font** font, char text[], float x, float y, float w, float h, int r, int g, int b) {
    SDL_Surface* surface = TTF_RenderText_Solid(*font,text,(SDL_Color){r,g,b,255});
    obj->texture = SDL_CreateTextureFromSurface(*renderer,surface);
    SDL_FreeSurface(surface);

    obj->rect = (SDL_Rect){x,y,w,h};
    
    obj->r = r;
    obj->g = g;
    obj->b = b;
}
void M_TextObject_RefreshText(SDL_Renderer** renderer, struct M_TextObject* obj, TTF_Font** font, char new_text[]) {
    SDL_Surface* surface = TTF_RenderText_Solid(*font,new_text,(SDL_Color){obj->r,obj->g,obj->b,255});
    obj->texture = SDL_CreateTextureFromSurface(*renderer,surface);
    SDL_FreeSurface(surface);
}
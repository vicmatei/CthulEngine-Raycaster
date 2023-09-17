// ! include
// ! std
#include <stdio.h>
#include <stdbool.h>
// ! SDL2
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
// ! sdl app module
#include "module/M_Console.h"
#include "module/M_App.h"
#include "module/M_Clock.h"
#include "module/M_Math.h"
#include "module/M_Renderer.h"
#include "module/M_TextRenderer.h"
// ! game specific header files
#include "app/G_defs.h"
#include "app/G_player.h"
#include "app/G_map.h"

int main(int argc, char* argv[]) {
    // ! GENERAL SDL APP COMPONENTS
    // * prepare SDL app components
    struct M_App app; M_App_Init(&app);
    struct M_FpsClock clock;

    // ! GAME COMPONENTS
    // * prepare game components
    struct G_Player player; G_Player_Init(&player);
    int gameMap[] = {
        2,2,1,2,1,2,1,2,2,
        2,0,0,0,0,0,0,0,2,
        1,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,2,
        1,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,2,
        1,0,0,0,0,0,0,0,1,
        2,0,0,0,0,0,0,0,2,
        2,2,1,2,1,2,1,2,2,
    };
    // * load fonts from the ('$ROOT/font/directory')
    TTF_Font* title_font = TTF_OpenFont("./../font/font.ttf",64);
    TTF_Font* big_font = TTF_OpenFont("./../font/font.ttf",32);
    TTF_Font* game_font = TTF_OpenFont("./../font/font.ttf",16);

    struct M_TextObject text_obj;
    M_TextObject_Init(&app.renderer,&text_obj,&title_font,"some text",0,SCREEN_HEIGHT,(SCREEN_WIDTH / 2),(WINDOW_HEIGHT-SCREEN_HEIGHT),255,255,255);

    // ! game loop
    bool run = true; while (run) {
        M_FpsClock_Prep(&clock);

        // ! events
        // * check for events
        while (SDL_PollEvent(&app.event)) {
            // * check if the user wants to quit
            if (app.event.type == SDL_QUIT) {
                run = false;
            }
        }
        // ! screen
        // * fill / draw background
        M_App_FillBg(&app.renderer,0,0,0);
        M_Renderer_DrawRect(&app.renderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,25,25,25);

        // ! draw
        // * player
        G_Player_RenderFOV(&app.renderer,&player,gameMap);
        G_Player_DrawCrosshair(&app.renderer);

        // * update text content
        char angle_text[4+7];
        snprintf(angle_text,4+7,"Angle: %f",M_Math_ConvRadsToDegs(player.angle));
        // * render text and refresh its content
        M_TextObject_RefreshText(&app.renderer,&text_obj,&title_font,angle_text);
        SDL_RenderCopy(app.renderer,text_obj.texture,NULL,&text_obj.rect);

        // ! update
        // * player
        G_Player_Move(&player,gameMap);
        G_Player_UpdateStats(&player,false);
        
        // ! screen
        // * update and fps clock tick
        M_App_UpdateScreen(&app.renderer);
        M_FpsClock_Tick(&clock);
    }

    return 0;
}
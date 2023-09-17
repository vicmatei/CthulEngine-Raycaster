#pragma once

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "module/M_Math.h"
#include "module/M_Renderer.h"

#include "app/G_defs.h"

struct G_Player {
    SDL_Rect rect;
    
    float speed;
    float turn_speed;
    
    double angle;

    bool moving_forward;
};
void G_Player_Init(struct G_Player* p) {
    p->rect = (SDL_Rect){SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,16,16};

    p->speed = 5;
    p->turn_speed = 0.1;

    p->angle = M_Math_ConvDegsToRads(180);
}

void G_Player_Draw(SDL_Renderer** renderer, struct G_Player *p) {
    M_Renderer_DrawRect(renderer,p->rect.x,p->rect.y,p->rect.w,p->rect.h,255,255,0);
}
void G_Player_DrawCrosshair(SDL_Renderer** renderer) {
    M_Renderer_DrawRect(renderer,SCREEN_WIDTH / 2 - 12,SCREEN_HEIGHT / 2 - 12,24,24,200,200,200);
    M_Renderer_DrawRect(renderer,SCREEN_WIDTH / 2 - 8,SCREEN_HEIGHT / 2 - 8,16,16,50,50,50);
}
void G_Player_RenderFOV(SDL_Renderer** renderer, struct G_Player* p, int map[]) {
    double startAngle = p->angle - HALF_FOV;
    for (int ray = 0; ray < CASTED_RAYS; ray++) {
        for (int depth = 0; depth < MAX_DEPTH; depth++) {
            double targetX = M_Math_CalcTargetX(p->rect.x,startAngle,depth);
            double targetY = M_Math_CalcTargetY(p->rect.y,startAngle,depth);

            int col = ((int)(targetX / TILE_W));
            int row = ((int)(targetY / TILE_H));
            int index = row * MAP_SIZE + col;

            int selected = map[index];
            if (selected == 1) {
                float new_depth = depth * cos(p->angle - startAngle);
                float wall_height = ((SCREEN_HEIGHT) * (21000/SCREEN_HEIGHT)) / new_depth;
                int color = 255 - (255 / depth);
                M_Renderer_DrawRect(renderer,ray * SCALE,SCREEN_HEIGHT / 2 - (wall_height / 2),SCALE,wall_height,color,0,0);
                break;
            } else if (selected == 2) {
                float new_depth = depth * cos(p->angle - startAngle);
                float wall_height = ((SCREEN_HEIGHT) * (21000/SCREEN_HEIGHT)) / new_depth;
                int color = 255 - (255 / depth);
                M_Renderer_DrawRect(renderer,ray * SCALE,SCREEN_HEIGHT / 2 - (wall_height / 2),SCALE,wall_height,color,color,color);
                break;
            }
        }
        startAngle += STEP_ANGLE;
    }
}

void G_Player_Move(struct G_Player* p, int map[]) {
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W]) {
        p->moving_forward = true;
        p->rect.x += M_Math_CalcTargetX(0,p->angle,p->speed);
        p->rect.y += M_Math_CalcTargetY(0,p->angle,p->speed);
    } else if (keys[SDL_SCANCODE_S]) {
        p->moving_forward = false;
        p->rect.x -= M_Math_CalcTargetX(0,p->angle,p->speed);
        p->rect.y -= M_Math_CalcTargetY(0,p->angle,p->speed);
    }
    if (keys[SDL_SCANCODE_A]) {
        p->angle -= p->turn_speed;
    } else if (keys[SDL_SCANCODE_D]) {
        p->angle += p->turn_speed;
    }

    int row = (int)(p->rect.x / TILE_W);
    int col = (int)(p->rect.y / TILE_H);

    int index = row * MAP_SIZE + col;
    int selected = map[index];
    if (selected != 0) {
        if (p->moving_forward) {
            p->rect.x -= M_Math_CalcTargetX(0,p->angle,p->speed);
            p->rect.y -= M_Math_CalcTargetY(0,p->angle,p->speed);
        } else {
            p->rect.x += M_Math_CalcTargetX(0,p->angle,p->speed);
            p->rect.y += M_Math_CalcTargetY(0,p->angle,p->speed);
        }
    }
}
void G_Player_UpdateStats(struct G_Player* p, bool monitor) {
    if ((M_Math_ConvRadsToDegs(p->angle) > 360)) {
        p->angle = M_Math_ConvDegsToRads(0);
    } else if ((M_Math_ConvRadsToDegs(p->angle) < 0)) {
        p->angle = M_Math_ConvDegsToRads(360);
    }

    if (monitor) {
        printf("Deg: %f| Rad: %f\n",M_Math_ConvRadsToDegs(p->angle),p->angle);
        printf("\x01b[2J");
        printf("\x01b[H");
    }
}
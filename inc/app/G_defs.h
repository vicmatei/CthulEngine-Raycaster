#pragma once

#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 650
#define WINDOW_TITLE "SDL2 Window - RaycasterProject"
#define FPS 60
#define TARGET_DELTA (1000 / FPS)

#define MAP_SIZE 9
#define TILE_W (SCREEN_WIDTH / MAP_SIZE)
#define TILE_H (SCREEN_HEIGHT / MAP_SIZE)
#define FOV (M_PI / 3)
#define HALF_FOV (FOV / 2)
#define CASTED_RAYS 240
#define STEP_ANGLE (FOV / CASTED_RAYS)
#define SCALE (SCREEN_WIDTH / CASTED_RAYS + 1)

#define MAX_DEPTH ((int)(MAP_SIZE * TILE_H))
#pragma once

#include <stdio.h>

void M_SetStyle(int r, int g, int b) {
    printf("\x01b[38;2;%d;%d;%dm",r,g,b);
}
void M_ResetStyle(void) {
    printf("\x01b[0;0m");
}
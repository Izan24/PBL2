#include <stdio.h>
#include "general.h"
#include "maps.h"
#include "sdlDefine.h"
#include "graphics.h"


void draw_line_to(LINE line)
{
    SDL_SetRenderDrawColor(rend, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(rend, line.x1, line.y1, line.x2, line.y2);
}


SDL_Texture* bg_init(char* img) {

    SDL_Surface* surface;
    SDL_Texture* bg;

    bg = (SDL_Texture*)malloc(sizeof(SDL_Texture*));

    surface = IMG_Load(img);

    bg = SDL_CreateTextureFromSurface(rend, surface);

    return bg;
}
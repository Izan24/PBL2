#include <stdio.h>
#include "general.h"
#include "maps.h"
#include "sdlDefine.h"
#include "graphics.h"


void draw_line_to(LINE line)
{
    SDL_SetRenderDrawColor(rend, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(rend, line.x0, line.y0, line.x1, line.y1);
}


SDL_Texture* bg_init(const char* img) {

    SDL_Surface* surface;
    SDL_Texture* bg;

    bg = (SDL_Texture*)malloc(sizeof(SDL_Texture*));

    surface = IMG_Load(img);

    bg = SDL_CreateTextureFromSurface(rend, surface);

    return bg;
}



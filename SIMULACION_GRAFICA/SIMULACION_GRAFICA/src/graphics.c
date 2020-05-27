#include <stdio.h>
#include "general.h"
#include "maps.h"
#include "sdlDefine.h"
#include "graphics.h"


void drawLineTo(LINE line, int red, int green, int blue)
{
    SDL_SetRenderDrawColor(rend, red, green, blue, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(rend, line.x0, line.y0, line.x1, line.y1);
}


SDL_Texture* bgInit(const char* img)
{
    SDL_Surface* surface;
    SDL_Texture* bg;

    bg = (SDL_Texture*)malloc(sizeof(SDL_Texture*));

    surface = IMG_Load(img);

    bg = SDL_CreateTextureFromSurface(rend, surface);

    return bg;
}

void drawThiccLine(LINE line){
    SDL_SetRenderDrawColor(rend, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(rend, line.x0+1, line.y0+1, line.x1+1, line.y1+1);
    SDL_RenderDrawLine(rend, line.x0, line.y0, line.x1, line.y1);
    SDL_RenderDrawLine(rend, line.x0-1, line.y0-1, line.x1-1, line.y1-1);
}


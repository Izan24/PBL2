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


SDL_Texture* bgInit(char* img)
{
    surface = IMG_Load(img);
    SDL_Texture* bg = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    //free(surface);
    //bg = (SDL_Texture*)malloc(sizeof(SDL_Texture*));
    return bg;
}

void drawThiccLine(LINE line){
    SDL_SetRenderDrawColor(rend, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(rend, line.x0+1, line.y0+1, line.x1+1, line.y1+1);
    SDL_RenderDrawLine(rend, line.x0, line.y0, line.x1, line.y1);
    SDL_RenderDrawLine(rend, line.x0-1, line.y0-1, line.x1-1, line.y1-1);
}


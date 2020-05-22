#include <stdio.h>
#include "sdlDefine.h"
#include "general.h"

int sdl_init()
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("No se ha podido iniciar.");
        return 1;
    }

    Uint32 render_flags;

    window = SDL_CreateWindow("Nombre del programa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!window)
    {
        printf("Error de ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    rend = SDL_CreateRenderer(window, -1, render_flags);

    if (!rend)
    {
        printf("Error creating the renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    return 0;
}

int sdl_destroy()
{
    
    if (rend)// It enters here only if rend is defined and same with the other variables
    {
        SDL_DestroyRenderer(rend);
    }

    if (window)
    {
        SDL_DestroyWindow(window);
    }

    return 1;
}
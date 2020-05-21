#include <stdio.h>
#include "general.h"
#include "maps.h"
#include "sdlDefine.h"
#include "graphics.h"

int main() {


    /*printf("%s", mapFileName());*/

    sdl_init();


    SDL_Event event;
    BOOL closeRequested = FALSE;
    SDL_Texture* bg = bg_init("resources/images/backgrounds/MutrikuIMGwith_NODES.png");

    while (closeRequested == FALSE)
    {

        SDL_RenderClear(rend);

        SDL_RenderCopy(rend, bg, NULL, NULL);
        SDL_RenderDrawLine(rend, 0, 0, 680, 384);

        SDL_RenderPresent(rend);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                closeRequested = TRUE;
                sdl_destroy();
            }
        }
    }


    getchar();
    return 0;
}


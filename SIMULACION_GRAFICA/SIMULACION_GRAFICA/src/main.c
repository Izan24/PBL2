#include <stdio.h>
#include "general.h"

int main() {


    /*printf("%s", mapFileName());*/

    MAP* map = loadMap();
    LINE lineas[2000];

    sdl_init();


    SDL_Event event;
    BOOL closeRequested = FALSE;
    //SDL_Texture* bg = bg_init("/resources/images/backgrounds/MutrikuIMG.png");
    SDL_Texture* bg = bg_init("Arre.jpg");

    /*while (closeRequested == FALSE)
    {*/

        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, bg, NULL, NULL);
        SDL_RenderPresent(rend);
        for (int i = 0; i < getLines(lineas, map); i++) {
            draw_line_to(lineas[i]);
            SDL_RenderPresent(rend);
        }


        /*while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                closeRequested = TRUE;
                sdl_destroy();
            }
        }*/
    //}


    getchar();
    return 0;
}


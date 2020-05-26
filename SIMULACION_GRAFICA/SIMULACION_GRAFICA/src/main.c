#include <stdio.h>
#include "general.h"

int main() {

<<<<<<< HEAD


=======
    /*printf("%s", mapFileName());*/

    MAP* map = loadMap();
    LINE lines[2000];
>>>>>>> master

	

<<<<<<< HEAD
	
=======
    // RANDOM TU


    SDL_Event event;
    BOOL closeRequested = FALSE;
    //SDL_Texture* bg = bg_init("/resources/images/backgrounds/MutrikuIMG.png")/*;*/
    SDL_Texture* bg = bgInit("MutrikuIMG.png");

    /*while (closeRequested == FALSE)
    {*/

    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);
    SDL_RenderPresent(rend);
    for (int i = 0; i < getLines(lines, map); i++) {
        drawLineTo(lines[i], 0, 0, 255);
        SDL_RenderPresent(rend);
    }

    NODEPOINT* startPrueba;
    NODEPOINT* endPrueba;

    startPrueba = &map->points[15];
    endPrueba = &map->points[80];

    execAlgorithm(map, lines, startPrueba, endPrueba);

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
>>>>>>> master
}


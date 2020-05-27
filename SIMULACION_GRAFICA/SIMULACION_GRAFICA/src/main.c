#include <stdio.h>
#include "general.h"

int main() {




    MAP* map = loadMap();
    LINE lines[2000];
    SDL_Event event;
    BOOL closeRequested = FALSE;

    sdl_init();

    SDL_Texture* bg = bgInit(map->IMGPath);
    BUTTON ALL_Buttons[10];
    INTERESTPOINT* interestPoints;

    STARTEND* twoPoints = (STARTEND*)malloc(sizeof(STARTEND));
    twoPoints->startP = NULL;
    twoPoints->endP = NULL;






    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);
    SDL_RenderPresent(rend);

    init_buttons(ALL_Buttons);
    button_set_dim(ALL_Buttons);

    interestPoints = initInterestpoints(map);




    for (int i = 0; i < getLines(lines, map); i++) {
        drawLineTo(lines[i], 0, 0, 255);
        SDL_RenderPresent(rend);
    }

    do
    {
        SDL_RenderCopy(rend, bg, NULL, NULL);
        closeRequested = init_menu(twoPoints, map, ALL_Buttons, lines);
        SDL_RenderPresent(rend);
    } while (closeRequested == FALSE);


    return 0;
}


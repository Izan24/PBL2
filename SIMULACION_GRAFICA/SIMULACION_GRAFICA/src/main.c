#include <stdio.h>
#include "general.h"

int main(){

    LINE lines[2000];
    BOOL closeRequested = FALSE;
    sdl_init();
    struct Cursors cursor = initCursor();

    intro();

    MAP* map = loadMap();
    SDL_Texture* bg = bgInit(map->IMGPath);
    BUTTON ALL_Buttons[MAX_BUTTON_N];
    INTERLIST* interestPoints;

    STARTEND* twoPoints = (STARTEND*)malloc(sizeof(STARTEND));
    twoPoints->startP = NULL;
    twoPoints->endP = NULL;



    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);

    initButtons(ALL_Buttons);
    buttonSetDim(ALL_Buttons);


    interestPoints = initInterestpoints(map); // Get all the interest poits

    getLines(lines, map);

    //for (int i = 0; i < getLines(lines, map); i++) {
    //    drawLineTo(lines[i], 0, 0, 255);
    //    SDL_RenderPresent(rend);
    //}

    drawAllInterestPoints(interestPoints,RED);

    //redrawAll(&map, lines, &interestPoints, &bg, twoPoints, ALL_Buttons);
        
    do
    {
        //SDL_RenderCopy(rend, bg, NULL, NULL);

        closeRequested = initMenu(twoPoints, &map, ALL_Buttons, lines, &interestPoints, &bg, cursor);

        SDL_RenderPresent(rend);
    } while (closeRequested == FALSE);


    return 0;
}


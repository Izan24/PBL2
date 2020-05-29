#include <stdio.h>
#include "general.h"

int main(){
    //MAP* map = loadMap();
    //LINE lines[2000];
    //BOOL closeRequested = FALSE;

    //sdl_init();

    //SDL_Texture* bg = bgInit(map->IMGPath);
    //BUTTON ALL_Buttons[10];
    //INTERLIST* interestPoints;

    //STARTEND* twoPoints = (STARTEND*)malloc(sizeof(STARTEND));
    //twoPoints->startP = NULL;
    //twoPoints->endP = NULL;


    //SDL_RenderClear(rend);
    //SDL_RenderCopy(rend, bg, NULL, NULL);
    //SDL_RenderPresent(rend);

    //initButtons(ALL_Buttons);
    //buttonSetDim(ALL_Buttons);

    //interestPoints = initInterestpoints(map); // Get all the interest poits

    //getLines(lines, map);

    ////for (int i = 0; i < getLines(lines, map); i++) {
    ////    drawLineTo(lines[i], 0, 0, 255);
    ////    SDL_RenderPresent(rend);
    ////}

    //drawAllInterestPoints(interestPoints,twoPoints,RED);

    //do
    //{
    //    //SDL_RenderCopy(rend, bg, NULL, NULL);
    //    closeRequested = initMenu(twoPoints, map, ALL_Buttons, lines,interestPoints);
    //    SDL_RenderPresent(rend);
    //} while (closeRequested == FALSE);



    sdl_init();
    mapBuilderMain();



    return 0;
}


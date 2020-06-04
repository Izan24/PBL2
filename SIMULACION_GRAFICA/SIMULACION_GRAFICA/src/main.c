#include <stdio.h>
#include "general.h"

int main(int argv, char* argc)
{
    MAP* map;
    BUTTON ALL_Buttons[MAX_BUTTON_N];
    INTERLIST* interestPoints = NULL;
    ANODE* printList = NULL;
    STARTEND* twoPoints = NULL;
    struct Cursors cursor;
    cursor.arrow = NULL;
    cursor.hand= NULL;
    SDL_Texture* bg = NULL;
    MOUSE_POS* position = NULL;

    int writePointId = -1;
    int thId = -1;
    double angle = 0;

    WHEELCHAIR* wheelChair = NULL;
    BOOMER* boomer = NULL;

    sdl_init();

    map = loadMap();

    intro();

    initButtons(ALL_Buttons);

    initApp(map, &interestPoints, &bg, &twoPoints, &printList, &position, &wheelChair, &boomer, cursor, &angle, &thId, &writePointId);

    loop(&map, &interestPoints, &bg,& twoPoints, &printList, ALL_Buttons, &position, &wheelChair, &boomer, cursor, angle, thId, writePointId);

    return 0;
}

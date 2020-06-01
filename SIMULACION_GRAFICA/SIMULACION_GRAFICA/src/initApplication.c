#include <stdio.h>
#include "general.h"
#include "initApplication.h"

void reInitAll(MAP** map, LINE lines[], INTERLIST** interestPoints, SDL_Texture** bg, STARTEND* twoPoints)
{
    *map = loadMap();
    *bg = bgInit((*map)->IMGPath);
    *interestPoints = initInterestpoints(*map);
    getLines(lines, *map);
}
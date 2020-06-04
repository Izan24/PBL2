#include "general.h"
#include "userInterface.h"
#include <math.h>

void initApp(MAP* map, INTERLIST** interestPoints, SDL_Texture** bg, STARTEND** twoPoints, ANODE** printList, MOUSE_POS** position, WHEELCHAIR** wheelChair, BOOMER** boomer, struct Cursors cursor, double* angle, int* thId, int* writePointId)
{
    //*map = loadMap();

    *interestPoints = initInterestpoints(map); // Get all the interest poits

    *printList = NULL;

    (*twoPoints) = (STARTEND*)malloc(sizeof(STARTEND));
    (*twoPoints)->startP = NULL;
    (*twoPoints)->endP = NULL;

    cursor = initCursor();

    *bg = bgInit(map->IMGPath);

    *position = (MOUSE_POS*)malloc(sizeof(MOUSE_POS));

    *writePointId = -1;
    *thId = searchTH(map);
    *angle = 0;

    *wheelChair = (WHEELCHAIR*)malloc(sizeof(WHEELCHAIR));
    (*wheelChair)->boomerOnTop = FALSE;
    initWheelChair(*wheelChair);
    (*wheelChair)->x = (float)map->points[*thId].x;
    (*wheelChair)->y = (float)map->points[*thId].y;

    *boomer = (BOOMER*)malloc(sizeof(BOOMER));
    initBoomer(*boomer);
    (*boomer)->x = 0 - (*boomer)->dim.w;
}

BOOL loop(MAP** map, INTERLIST** interestPoints, SDL_Texture** bg, STARTEND** twoPoints, ANODE** printList, BUTTON* ALL_Buttons, MOUSE_POS** position, WHEELCHAIR** wheelChair, BOOMER** boomer, struct Cursors cursor, double angle, int thId, int writePointId)
{
    BOOL closeRequested = FALSE;

    do
    {
        closeRequested = checkActions(map, printList, twoPoints, interestPoints, ALL_Buttons, bg, position, wheelChair, boomer, cursor, &thId, &writePointId, angle);

        SDL_RenderClear(rend);
        drawAll(*bg, ALL_Buttons, *interestPoints, *wheelChair, *printList, *map, *boomer, angle, writePointId);
        SDL_RenderPresent(rend);
    } while (closeRequested == FALSE);

    return closeRequested;
}

BOOL checkActions(MAP** map, ANODE** printList, STARTEND** twoPoints, INTERLIST** interestPoints, BUTTON* ALL_Buttons, SDL_Texture** bg, MOUSE_POS** position, WHEELCHAIR** wheelChair, BOOMER** boomer, struct Cursors cursor, int* thId, int* writePointId, double angle)
{
    BOOL closeRequested = FALSE;
    SDL_Event mouse;
    NODEPOINT* mousePosition = (NODEPOINT*)malloc(sizeof(NODEPOINT));
    mousePosition->x = (*position)->x;
    mousePosition->y = (*position)->y;

    int action;
    int clickedPoint;


    if (SDL_PollEvent(&mouse))
    {
        switch (mouse.type)
        {
        case SDL_MOUSEMOTION:

            (*position)->x = mouse.motion.x;
            (*position)->y = mouse.motion.y;

            mousePosition->x = (*position)->x;
            mousePosition->y = (*position)->y;

            verifyMouseOnTop(ALL_Buttons, *position);
            break;
        case SDL_MOUSEBUTTONUP:
            if (mouse.button.button == SDL_BUTTON_LEFT)
            {
                action = checkClick(**position, ALL_Buttons);
                printf("%d", action);
                switch (action)
                {
                case START_PATH:
                    if ((*twoPoints)->startP != NULL && (*twoPoints)->endP != NULL)
                    {
                        if ((*boomer)->male == TRUE) (*boomer)->male = FALSE;
                        else (*boomer)->male = TRUE;

                        startPath(*map, *bg, ALL_Buttons, *interestPoints, *printList, *twoPoints, *wheelChair, *boomer, *thId);

                        setAllToRed(*interestPoints);
                        (*twoPoints)->startP = NULL;
                        (*twoPoints)->endP = NULL;
                        (*boomer)->x = 0 - (*boomer)->dim.w;
                    }
                    else errorMessage(ALL_Buttons, *bg, *interestPoints, *map, *printList, *wheelChair, *boomer, 0, *writePointId);

                    break;
                case SELECT_POINTS:

                    (*twoPoints)->startP = NULL;
                    (*twoPoints)->endP = NULL;
                    printInterestPoints(*interestPoints);
                    SDL_RenderPresent(rend);

                    selectPointsMap(twoPoints, *interestPoints, *position, *map);
                    break;
                case DEPLOYABLE_MENU:
                    swapButtonState(ALL_Buttons);
                    break;
                case EXIT_APP:
                    if (ALL_Buttons[3].enabled == TRUE)
                    {
                        closeRequested = TRUE;
                    }
                    break;
                case CHANGE_MAP:
                    if (ALL_Buttons[4].enabled == TRUE)
                    {
                        ALL_Buttons[3].enabled = FALSE;
                        ALL_Buttons[4].enabled = FALSE;

                        destroyAll(*map, *interestPoints, *bg, *twoPoints, *printList, *position, *wheelChair, *boomer, cursor);
                        *map = loadMap();
                        initApp(*map, interestPoints, bg, twoPoints, printList, position, wheelChair, boomer, cursor, &angle, thId, writePointId);
                        intro();
                    }
                    break;
                case CLICK_POINT:
                    *writePointId = checkClickInterestPoint(*map, *interestPoints, *mousePosition);
                    break;
                }
            }
            break;
        case SDL_QUIT:
            closeRequested = TRUE;
            break;
        }
    }

    free(mousePosition);

    return closeRequested;
}

int checkClick(MOUSE_POS position, BUTTON* ALL_Buttons)
{
    int action = -1;

    if (distMouseButton(ALL_Buttons[0], &position))
    {
        action = DEPLOYABLE_MENU;
    }

    else if (distMouseButton(ALL_Buttons[1], &position))
    {
        action = SELECT_POINTS;
    }

    else if (distMouseButton(ALL_Buttons[2], &position))
    {
        action = START_PATH;
    }

    else if (distMouseButton(ALL_Buttons[3], &position))
    {
        if (ALL_Buttons[3].enabled == TRUE)
        {
            action = EXIT_APP;
        }
    }

    else if (distMouseButton(ALL_Buttons[4], &position))
    {
        if (ALL_Buttons[4].enabled == TRUE)
        {
            action = CHANGE_MAP;
        }
    }

    else
    {
        action = CLICK_POINT;
    }

    return action;
}

void startPath(MAP* map, SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, ANODE* printList, STARTEND* twoPoints, WHEELCHAIR* wheeelChair, BOOMER* boomer, int thId)
{
    if (twoPoints->startP != NULL && twoPoints->endP != NULL)
    {
        boomer->x = twoPoints->startP->x;
        boomer->y = twoPoints->startP->y;

        printList = execAlgorithm(map, &map->points[thId], twoPoints->startP);
        drawPathDynamic(printList, map);
        moveWheelChair(map, bg, ALL_Buttons, interestPoints, printList, wheeelChair, boomer, -1);

        //
        boomer->x = 0 - boomer->dim.w;

        wheeelChair->boomerOnTop = TRUE;
        printList = execAlgorithm(map, twoPoints->startP, twoPoints->endP);
        drawPathDynamic(printList, map);
        moveWheelChair(map, bg, ALL_Buttons, interestPoints, printList, wheeelChair, boomer, -1);

        //
        boomer->x = twoPoints->endP->x;
        boomer->y = twoPoints->endP->y;

        wheeelChair->boomerOnTop = FALSE;
        printList = execAlgorithm(map, twoPoints->endP, &map->points[thId]);
        drawPathDynamic(printList, map);
        moveWheelChair(map, bg, ALL_Buttons, interestPoints, printList, wheeelChair, boomer, -1);

        //
    }
}

int checkClickInterestPoint(MAP* map, INTERLIST* interestList, NODEPOINT mousePosition)
{
    int id = -1;
    while (interestList != NULL) // check all interest Points
    {

        if (getCost(mousePosition, map->points[interestList->interestpoint.id]) < 10)
        {
            id = interestList->interestpoint.id;
        }
        interestList = interestList->ptrInterest;
    }

    return id;
}

void swapButtonState(BUTTON* ALL_Buttons)
{
    if (ALL_Buttons[3].enabled == FALSE && ALL_Buttons[4].enabled == FALSE)
    {
        ALL_Buttons[3].enabled = TRUE;
        ALL_Buttons[4].enabled = TRUE;
    }
    else
    {
        ALL_Buttons[3].enabled = FALSE;
        ALL_Buttons[4].enabled = FALSE;
    }
}

void drawAll(SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, WHEELCHAIR* wheelChair, ANODE* printList, MAP* map, BOOMER* boomer, double angle, int writePointId)
{
    SDL_RenderCopy(rend, bg, NULL, NULL);

    if (writePointId != -1)
    {
        drawText(map->points[writePointId].title);
    }

    printButtons(ALL_Buttons);

    printInterestPoints(interestPoints);

    drawPath(printList, map);

    drawWheelChair(wheelChair, angle);

    drawBoomer(boomer);
}

void printButtons(BUTTON* ALL_Buttons)
{
    for (int i = 0; i <= 5; i++)
    {
        if (ALL_Buttons[i].enabled == TRUE)
        {
            if (ALL_Buttons[i].mouseOnTop == TRUE)
            {
                SDL_QueryTexture(ALL_Buttons[i].grey_ver, NULL, NULL, &ALL_Buttons[i].dim.w, &ALL_Buttons[i].dim.h);
                SDL_RenderCopy(rend, ALL_Buttons[i].grey_ver, NULL, &ALL_Buttons[i].dim);
            }
            else
            {
                SDL_QueryTexture(ALL_Buttons[i].normal_ver, NULL, NULL, &ALL_Buttons[i].dim.w, &ALL_Buttons[i].dim.h);
                SDL_RenderCopy(rend, ALL_Buttons[i].normal_ver, NULL, &ALL_Buttons[i].dim);
            }
        }
    }
}

void verifyMouseOnTop(BUTTON* ALL_Buttons, MOUSE_POS* position)
{
    for (int i = 0; i < 5; i++)
    {
        if (distMouseButton(ALL_Buttons[i], position) == 1)
        {
            ALL_Buttons[i].mouseOnTop = TRUE;
        }
        else if (distMouseButton(ALL_Buttons[i], position) == 0)
        {
            ALL_Buttons[i].mouseOnTop = FALSE;
        }
    }
}

void printInterestPoints(INTERLIST* interestPoints)
{
    while (interestPoints != NULL)
    {
        switch (interestPoints->interestpoint.type)
        {
        case RED:
            SDL_RenderCopy(rend, interestPoints->interestpoint.textureRed, NULL, &interestPoints->interestpoint.dim);
            break;
        case START:
            SDL_RenderCopy(rend, interestPoints->interestpoint.textureStart, NULL, &interestPoints->interestpoint.dim);
            break;
        case END:
            SDL_RenderCopy(rend, interestPoints->interestpoint.textureEnd, NULL, &interestPoints->interestpoint.dim);
            break;
        }

        interestPoints = interestPoints->ptrInterest;
    }
}

void moveWheelChair(MAP* map, SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, ANODE* printList, WHEELCHAIR* wheelChair, BOOMER* boomer, int writePoint)
{

    int currentX, currentY, nextX, nextY;

    float vectorX, vectorY;

    double angle;

    NODEPOINT p1, p2;

    ANODE* pListAux = printList;

    while (printList->ptrAstar != NULL)
    {
        currentX = map->points[printList->astar.current].x;
        currentY = map->points[printList->astar.current].y;
        p1.x = currentX;
        p1.y = currentY;

        nextX = map->points[printList->ptrAstar->astar.current].x;
        nextY = map->points[printList->ptrAstar->astar.current].y;
        p2.x = nextX;
        p2.y = nextY;

        vectorX = nextX - currentX;
        vectorY = nextY - currentY;

        angle = returnAngleDegree(vectorX, p1, p2);

        unitaryVector(&vectorX, &vectorY);

        pListAux = pListAux->ptrAstar;
        while (round(wheelChair->x) != nextX || round(wheelChair->y) != nextY)
        {
            /*
                AQUI TENGO QUE HACER QUE SE MUEVA LA SILLA HASTA EL NEXTX E NEXTY
            */

            if (wheelChair->x != nextX) wheelChair->x += vectorX;
            if (wheelChair->y != nextY) wheelChair->y += vectorY;

            chechVectorStatus(wheelChair, vectorY, vectorX, nextY, nextX);

            SDL_RenderClear(rend);
            drawAll(bg, ALL_Buttons, interestPoints, wheelChair, pListAux, map, boomer, angle, writePoint);
            SDL_RenderPresent(rend);
        }


        printList = printList->ptrAstar;
    }
}

void unitaryVector(float* x, float* y)
{
    float module;
    float xCopy = *x;
    float YCopy = *y;

    float xSquared = (xCopy * xCopy);
    float ySquared = (YCopy * YCopy);
    float sum = (xSquared + ySquared);

    module = sqrt(sum);

    *x = *x / module;
    *y = *y / module;
}

void drawWheelChair(WHEELCHAIR* wheelChair, const double angle)
{
    wheelChair->dim.x = (int)wheelChair->x - (wheelChair->dim.w / 2);
    wheelChair->dim.y = (int)wheelChair->y - (wheelChair->dim.h / 2);

    //SDL_Point center;
    //center.x = wheelChair->dim.x;
    //center.y = wheelChair->dim.y;

    if (wheelChair->boomerOnTop == TRUE) SDL_RenderCopyEx(rend, wheelChair->textureWithBoomer, NULL, &wheelChair->dim, angle, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyEx(rend, wheelChair->textureNoBoomer, NULL, &wheelChair->dim, angle, NULL, SDL_FLIP_NONE);
}

void chechVectorStatus(WHEELCHAIR* wheelChair, float vectorY, float vectorX, int nextY, int nextX)
{

    if (vectorY > 0)
    {
        if (round((wheelChair->y + vectorY)) > nextY)
        {
            wheelChair->y = nextY;
        }
    }
    else if (vectorY < 0)
    {
        if (round((wheelChair->y + vectorY)) < nextY)
        {
            wheelChair->y = nextY;
        }
    }


    if (vectorX > 0)
    {
        if (round((wheelChair->x + vectorX)) > nextX)
        {
            wheelChair->x = nextX;
        }
    }
    else if (vectorX < 0)
    {
        if (round((wheelChair->x + vectorX)) < nextX)
        {
            wheelChair->x = nextX;
        }
    }

}

double returnAngleDegree(float vectorX, NODEPOINT p1, NODEPOINT p2)
{
    double angle = 0;

    angle = asin(vectorX / getCost(p1, p2));
    angle = (angle * 360) / (2 * M_PI);

    if (p2.y > p1.y)
    {
        angle = 180 - angle;
    }

    return angle;
}

void drawBoomer(BOOMER* boomer)
{
    if (boomer->x >= 0)
    {
        boomer->dim.x = boomer->x;
        boomer->dim.y = boomer->y - boomer->dim.h;

        if (boomer->male == TRUE) SDL_RenderCopy(rend, boomer->textureMale, NULL, &boomer->dim);
        else SDL_RenderCopy(rend, boomer->textureFemale, NULL, &boomer->dim);

    }
}

void destroyAll(MAP* map, INTERLIST* interestPoints, SDL_Texture* bg, STARTEND* twoPoints, ANODE* printList, MOUSE_POS* position, WHEELCHAIR* wheelChair, BOOMER* boomer, struct Cursors cursor)
{
    INTERLIST* intereestPAux;
    ANODE* printListAux;

    free(map);

    while (interestPoints != NULL)
    {
        intereestPAux = interestPoints;
        interestPoints = interestPoints->ptrInterest;

        free(intereestPAux);
    }

    SDL_DestroyTexture(bg);

    free(twoPoints);

    while (printList != NULL)
    {
        intereestPAux = printList;
        printList = printList->ptrAstar;

        free(intereestPAux);
    }

    free(position);

    SDL_DestroyTexture(wheelChair->textureNoBoomer);
    SDL_DestroyTexture(wheelChair->textureWithBoomer);
    free(wheelChair);
    
    SDL_DestroyTexture(boomer->textureFemale);
    SDL_DestroyTexture(boomer->textureMale);
    free(boomer);

    SDL_FreeCursor(cursor.arrow);
    SDL_FreeCursor(cursor.hand);
}
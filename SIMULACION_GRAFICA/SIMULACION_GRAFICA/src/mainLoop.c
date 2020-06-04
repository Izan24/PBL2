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

        vectorX = (float)nextX - (float)currentX;
        vectorY = (float)nextY - (float)currentY;

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

    module = (float)sqrt(sum);

    *x = *x / module;
    *y = *y / module;
}

void chechVectorStatus(WHEELCHAIR* wheelChair, float vectorY, float vectorX, int nextY, int nextX)
{
    float sum;
    if (vectorY > 0)
    {
        sum = wheelChair->y + vectorY;
        if (round(sum) > nextY)
        {
            wheelChair->y = (float)nextY;
        }
    }
    else if (vectorY < 0)
    {
        sum = wheelChair->y + vectorY;
        if (round(sum) < nextY)
        {
            wheelChair->y = (float)nextY;
        }
    }


    if (vectorX > 0)
    {
        sum = wheelChair->x + vectorX;
        if (round(sum) > nextX)
        {
            wheelChair->x = (float)nextX;
        }
    }
    else if (vectorX < 0)
    {
        sum = wheelChair->x + vectorX;
        if (round(sum) < nextX)
        {
            wheelChair->x = (float)nextX;
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
        printListAux = printList;
        printList = printList->ptrAstar;

        free(printListAux);
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

int distMouseButton(BUTTON button, MOUSE_POS* position)
{
    float distance = 0; int x, y; int boolean = 0;

    x = (button.dim.x + button.dim.w / 2);
    y = (button.dim.y + button.dim.h / 2);
    x = x - position->x;
    y = y - position->y;
    distance = (float)(x * x) + (float)(y * y);
    distance = (float)sqrt(distance);
    if (distance < button.radius)
    {
        boolean = 1;
    }
    return boolean;
}

void selectPointsMap(STARTEND** twoPoints, INTERLIST* iPointsList, MOUSE_POS* mousePos, MAP* map)
{
    INTERLIST* aux = iPointsList;

    BOOL done = FALSE;


    if (aux != NULL)
    {
        do
        {
            selectStartEndP(map, iPointsList, twoPoints, 0);

        } while ((*twoPoints)->startP == NULL);

        if ((*twoPoints)->startP != NULL) // To avoid warnings
        {
            setColor(iPointsList, START, (*twoPoints)->startP->id);
            printInterestPoints(iPointsList);
            SDL_RenderPresent(rend);
        }

        do
        {
            selectStartEndP(map, iPointsList, twoPoints, 1);
        } while ((*twoPoints)->endP == NULL);

        if ((*twoPoints)->endP != NULL)
        {
            setColor(iPointsList, END, (*twoPoints)->endP->id);
            printInterestPoints(iPointsList);
            SDL_RenderPresent(rend);
        }
    }
}

void selectStartEndP(MAP* map, INTERLIST* iPointsList, STARTEND** twoPoints, int startEnd)
{
    NODEPOINT mouse;
    SDL_Event click;
    INTERLIST* aux = iPointsList;
    BOOL done = FALSE;

    do
    {
        if (SDL_PollEvent(&click))
        {
            if (click.type == SDL_MOUSEBUTTONUP)
            {
                if (SDL_BUTTON_LEFT)
                {
                    done = TRUE;
                    mouse.x = click.motion.x;
                    mouse.y = click.motion.y;
                }
            }
        }
    } while (done == FALSE);

    while (aux != NULL)
    {
        if (getCost(mouse, map->points[aux->interestpoint.id]) < 10)
        {
            if (startEnd == 0)
            {
                (*twoPoints)->startP = &map->points[aux->interestpoint.id];
            }
            else if (startEnd == 1)
            {
                (*twoPoints)->endP = &map->points[aux->interestpoint.id];
            }
        }
        aux = aux->ptrInterest;
    }

    done = FALSE;
    aux = iPointsList;
}

int verifyPosMouse(BUTTON button, MOUSE_POS* position)
{
    if (distMouseButton(button, position))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int searchTH(MAP* map)
{
    int i = 0, thId = -1;
    BOOL found = FALSE;

    while (i < map->nodePointAmount && found == FALSE)
    {
        if (strcmp(map->points[i].title, "Ayuntamiento") == 0)
        {
            thId = map->points[i].id;
            found = TRUE;
        }
        i++;
    }

    return thId;
}

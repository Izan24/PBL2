#include "general.h"
#include "mainLoop.h"

void initApp(MAP* map, INTERLIST** interestPoints, SDL_Texture** bg, STARTEND** twoPoints, ANODE** printList, MOUSE_POS** position, WHEELCHAIR** wheelChair, BOOMER** boomer, struct Cursors cursor, double* angle, int* thId, int* writePointId, BUTTON *ALL_Buttons)
{

    initButtons(ALL_Buttons);

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

BOOL loop(MAP** map)
{
    BUTTON *ALL_Buttons = (BUTTON*)malloc(sizeof(BUTTON) * MAX_BUTTON_N);;
    INTERLIST* interestPoints = NULL;
    ANODE* printList = NULL;
    STARTEND* twoPoints = NULL;
    WHEELCHAIR* wheelChair = NULL;
    BOOMER* boomer = NULL;
    SDL_Texture* bg = NULL;
    MOUSE_POS* position = NULL;

    struct Cursors cursor;
    cursor.arrow = NULL;
    cursor.hand = NULL;

    int writePointId = -1;
    int thId = -1;
    double angle = 0;

    initApp(*map, &interestPoints, &bg, &twoPoints, &printList, &position, &wheelChair, &boomer, cursor, &angle, &thId, &writePointId, ALL_Buttons);

    BOOL closeRequested = FALSE;

    do
    {
        closeRequested = checkActions(map, &printList, &twoPoints, &interestPoints, ALL_Buttons, &bg, &position, &wheelChair, &boomer, cursor, &thId, &writePointId, angle);

        SDL_RenderClear(rend);
        drawAll(bg, ALL_Buttons, interestPoints, wheelChair, printList, *map, boomer, angle, writePointId);

#ifndef LINUX_SISTEMA
        SDL_Delay(1000 / 120);
#endif // !LINUX_SISTEMA

        SDL_RenderPresent(rend);
    } while (closeRequested == FALSE);

    free(ALL_Buttons);

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

                        closeRequested = startPath(*map, *bg, ALL_Buttons, *interestPoints, *printList, *twoPoints, *wheelChair, *boomer, *thId);

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
                    setAllToRed(*interestPoints);
                    SDL_RenderClear(rend);
                    drawAll(*bg, ALL_Buttons, *interestPoints, *wheelChair, *printList, *map, *boomer, angle, *writePointId);
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
                        initApp(*map, interestPoints, bg, twoPoints, printList, position, wheelChair, boomer, cursor, &angle, thId, writePointId, ALL_Buttons);
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

BOOL startPath(MAP* map, SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, ANODE* printList, STARTEND* twoPoints, WHEELCHAIR* wheeelChair, BOOMER* boomer, int thId)
{
    if (twoPoints->startP != NULL && twoPoints->endP != NULL)
    {
        boomer->x = twoPoints->startP->x;
        boomer->y = twoPoints->startP->y;

        printList = execAlgorithm(map, &map->points[thId], twoPoints->startP);
        drawPathDynamic(printList, map);
        if (moveWheelChair(map, bg, ALL_Buttons, interestPoints, printList, wheeelChair, boomer, -1) == TRUE) return TRUE;

        //
        boomer->x = 0 - boomer->dim.w;

        wheeelChair->boomerOnTop = TRUE;
        printList = execAlgorithm(map, twoPoints->startP, twoPoints->endP);
        drawPathDynamic(printList, map);
        if (moveWheelChair(map, bg, ALL_Buttons, interestPoints, printList, wheeelChair, boomer, -1) == TRUE) return TRUE;

        //
        boomer->x = twoPoints->endP->x;
        boomer->y = twoPoints->endP->y;

        wheeelChair->boomerOnTop = FALSE;
        printList = execAlgorithm(map, twoPoints->endP, &map->points[thId]);
        drawPathDynamic(printList, map);
        if (moveWheelChair(map, bg, ALL_Buttons, interestPoints, printList, wheeelChair, boomer, -1) == TRUE) return TRUE;

        return FALSE;
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

BOOL moveWheelChair(MAP* map, SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, ANODE* printList, WHEELCHAIR* wheelChair, BOOMER* boomer, int writePoint)
{

    int currentX, currentY, nextX, nextY;

    float vectorX, vectorY;

    double angle;

    NODEPOINT p1, p2;

    SDL_Event event;

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

            if (SDL_PollEvent(&event)) // Chech an action to avoid the windows defender
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    return TRUE; // return closerequested true
                    break;
                }
            }
            /*
                AQUI TENGO QUE HACER QUE SE MUEVA LA SILLA HASTA EL NEXTX E NEXTY
            */

            if (wheelChair->x != nextX) wheelChair->x += vectorX;
            if (wheelChair->y != nextY) wheelChair->y += vectorY;

            chechVectorStatus(wheelChair, vectorY, vectorX, nextY, nextX);
            SDL_Delay(1000 / 120);
            SDL_RenderClear(rend);
            drawAll(bg, ALL_Buttons, interestPoints, wheelChair, pListAux, map, boomer, angle, writePoint);
            SDL_RenderPresent(rend);
        }


        printList = printList->ptrAstar;
    }

    return FALSE;
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


    for (int i = 0; i < map->nodePointAmount; i++) {
        free(map->points[i].connections);
    }

    free(map->points);

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

 /*   for (int i = 0; i < MAX_BUTTON_N-1; i++) {
        SDL_DestroyTexture(ALL_Buttons[i].grey_ver);
        SDL_DestroyTexture(ALL_Buttons[i].normal_ver);
    }
    SDL_DestroyTexture(ALL_Buttons[5].normal_ver);

    free(ALL_Buttons);*/

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

int SDLDestroy()
{

    if (rend)// It enters here only if rend is defined and same with the other variables
    {
        SDL_DestroyRenderer(rend);
    }

    if (window)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    return 0;
}
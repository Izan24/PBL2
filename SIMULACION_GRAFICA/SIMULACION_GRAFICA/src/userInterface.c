#include "general.h"
#include "userInterface.h"
#include <math.h>

void intro()
{
    int alpha = 255;
    SDL_Texture* logo;
    SDL_Texture* logoUnfocus;

    logo = bgInit("../resources/backgrounds/introIMG.png");
    logoUnfocus = bgInit("../resources/backgrounds/introIMGunfocused.png");

    SDL_SetTextureBlendMode(logoUnfocus, SDL_BLENDMODE_BLEND);
    while (alpha > 0)
    {
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, logo, NULL, NULL);
        SDL_SetTextureAlphaMod(logoUnfocus, alpha);
        SDL_RenderCopy(rend, logoUnfocus, NULL, NULL);
        alpha -= 2;
        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }
    SDL_RenderCopy(rend, logo, NULL, NULL);
    SDL_RenderPresent(rend);

    SDL_Delay(250);
    SDL_RenderClear(rend);

    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(logoUnfocus);
}

//int initMenu(STARTEND* twoPoints, MAP** map, BUTTON* ALL_Buttons, LINE* lines, INTERLIST** interestPoints, SDL_Texture** bg, struct Cursors cursor) {
//
//    SDL_Event mouse;
//    MOUSE_POS position;
//    static int change_yes = 0, points_yes = 0, go_yes = 0, closeRequested = 0;
//    INTERLIST* interListAux = *interestPoints;
//    NODEPOINT mousePosition;
//    ANODE* printList = NULL;
//
//    /*
//        ¡¡¡¡¡¡ ESTO NO ES MUY OPTIMO PORQUE LO BUSCO TODAS LAS VUELTAS Y NO VA A ACAMBIAR, SOLO DEBERIA
//        VOLVER A BUSCARLO CUANDO HAYA UN CAMBIO DE MPA, CAMBIARE ESTO CUANDO EL MAIN LOOP NO SEA
//        EL INIT MENU. !"!!!!!!!!!"!"!"!"!"!"
//    */
//    int thId = searchTH(*map);
//
//
//    SDL_SetCursor(cursor.arrow);
//
//    if (SDL_PollEvent(&mouse))
//    {
//        if (SDL_MOUSEMOTION)
//        {
//            if (mouse.motion.x > 0 && mouse.motion.x <= WINDOW_WIDTH)
//            {
//                if (mouse.motion.y > 0 && mouse.motion.y <= WINDOW_HEIGHT)
//                {
//                    position.x = mouse.motion.x;
//                    position.y = mouse.motion.y;
//                    mousePosition.x = mouse.motion.x;
//                    mousePosition.y = mouse.motion.y;
//                }
//            }
//
//            change_yes = verifyPosMouse(ALL_Buttons[0], &position);
//            points_yes = verifyPosMouse(ALL_Buttons[1], &position);
//            go_yes = verifyPosMouse(ALL_Buttons[2], &position);
//        }
//    }
//
//    selectTexture(change_yes, ALL_Buttons[0]);
//    selectTexture(points_yes, ALL_Buttons[1]);
//    selectTexture(go_yes, ALL_Buttons[2]);
//
//    switch (mouse.type)
//    {
//    case SDL_MOUSEBUTTONUP:
//        if (SDL_BUTTON_LEFT)
//        {
//            if (distMouseButton(ALL_Buttons[0], &position))
//            {
//                SDL_SetCursor(cursor.hand);
//                closeRequested = deployMenuCall(ALL_Buttons, &position, mouse, interestPoints, bg, map, lines, twoPoints, printList);
//            }
//
//            if (distMouseButton(ALL_Buttons[1], &position))
//            {
//                SDL_SetCursor(cursor.hand);
//                redrawAll(*bg, ALL_Buttons, *interestPoints, *map, printList);
//
//                twoPoints->startP = NULL;
//                twoPoints->endP = NULL;
//                drawAllInterestPoints(*interestPoints, RED);
//                SDL_RenderPresent(rend);
//                selectPointsMap(&twoPoints, *interestPoints, &position, *map);
//            }
//
//            if (distMouseButton(ALL_Buttons[2], &position))
//            {
//                if (twoPoints->startP != NULL && twoPoints->endP != NULL)
//                {
//                    printList = execAlgorithm(*map, lines, &(*map)->points[thId], twoPoints->startP);
//                    //
//                    printList = execAlgorithm(*map, lines, twoPoints->startP, twoPoints->endP);
//                    //
//                    printList = execAlgorithm(*map, lines, twoPoints->endP, &(*map)->points[thId]);
//                    //
//                }
//                else
//                {
//                    errorMessage(ALL_Buttons, *bg, *interestPoints, *map, printList);
//                }
//            }
//
//            while (interListAux != NULL) // check all interest Points
//            {
//
//                if (getCost(mousePosition, (*map)->points[interListAux->interestpoint.id]) < 10)
//                {
//                    redrawAll(*bg, ALL_Buttons, *interestPoints, *map, printList);
//                    drawText((*map)->points[interListAux->interestpoint.id].title);
//                }
//                interListAux = interListAux->ptrInterest;
//            }
//
//        }
//        break;
//    case SDL_QUIT:
//        return 0;
//    }
//
//
//        redrawAll(*bg, ALL_Buttons, *interestPoints, *map, printList);
//
//
//    return closeRequested;
//}
//
//int deployMenuCall(BUTTON* ALL_Buttons, MOUSE_POS* position, SDL_Event mouse, INTERLIST** interestPoints, SDL_Texture** bg, MAP** map, LINE lines[], STARTEND* twoPoints, ANODE* printlist)
//{
//    int swapTexture = 0, exit_yes = 0, bool = 0, closeRequested = 0;
//    MOUSE_POS position1;
//
//    while (bool == 0)
//    {
//        if (SDL_PollEvent(&mouse))
//        {
//            if (SDL_MOUSEMOTION)
//            {
//                if (mouse.motion.x > 0 && mouse.motion.x <= WINDOW_WIDTH)
//                {
//                    if (mouse.motion.y > 0 && mouse.motion.y <= WINDOW_HEIGHT)
//                    {
//                        position1.x = mouse.motion.x;
//                        position1.y = mouse.motion.y;
//                    }
//                }
//
//                swapTexture = verifyPosMouse(ALL_Buttons[3], &position1);
//                exit_yes = verifyPosMouse(ALL_Buttons[4], &position1);
//                selectTexture(swapTexture, ALL_Buttons[3]);
//                selectTexture(exit_yes, ALL_Buttons[4]);
//                SDL_RenderPresent(rend);
//
//                if (mouse.type == SDL_MOUSEBUTTONUP)
//                {
//                    if (distMouseButton(ALL_Buttons[4], &position1))
//                    {
//                        freeOnChange(*map, *bg, *interestPoints);
//                        changeMap(map, lines, interestPoints, bg, twoPoints, ALL_Buttons, printlist);
//                        bool = 1;
//                    }
//                    else if (distMouseButton(ALL_Buttons[0], &position1))
//                    {
//                        bool = 1;
//                    }
//                    else if (distMouseButton(ALL_Buttons[3], &position1))
//                    {
//                        sdl_destroy();
//                        closeRequested = 1;
//                        bool = 1;
//                    }
//                }
//            }
//        }
//    }
//
//    redrawAll(*bg, ALL_Buttons, *interestPoints, *map, printlist);
//
//    return closeRequested;
//}



//void selectTexture(int which, BUTTON button) {
//
//    if (which == 1) {
//        SDL_QueryTexture(button.grey_ver, NULL, NULL, &button.dim.w, &button.dim.h);
//        SDL_RenderCopy(rend, button.grey_ver, NULL, &button.dim);
//    }
//    else {
//        SDL_QueryTexture(button.normal_ver, NULL, NULL, &button.dim.w, &button.dim.h);
//        SDL_RenderCopy(rend, button.normal_ver, NULL, &button.dim);
//    }
//}

void initButtons(BUTTON* ALL_Buttons)
{
    ALL_Buttons[0].normal_ver = bgInit("../resources/Button_menu.png");
    ALL_Buttons[0].grey_ver = bgInit("../resources/Button_menu_grey.png");
    ALL_Buttons[1].normal_ver = bgInit("../resources/Button_points.png");
    ALL_Buttons[1].grey_ver = bgInit("../resources/Button_points_grey.png");
    ALL_Buttons[2].normal_ver = bgInit("../resources/Button_go.png");
    ALL_Buttons[2].grey_ver = bgInit("../resources/Button_go_grey.png");

    ALL_Buttons[3].normal_ver = bgInit("../resources/exit_button.png");
    ALL_Buttons[3].grey_ver = bgInit("../resources/exit_button_grey.png");
    ALL_Buttons[4].normal_ver = bgInit("../resources/Swap_button.png");
    ALL_Buttons[4].grey_ver = bgInit("../resources/Swap_button_grey.png");

    ALL_Buttons[5].normal_ver = bgInit("../resources/error_message.png");

    buttonSetDim(ALL_Buttons);
}

void errorMessage(BUTTON* ALL_Buttons, SDL_Texture* bg, INTERLIST* interestPoints, MAP* map, ANODE* printList, WHEELCHAIR* wheelChair, BOOMER* boomer, double angle, int writePointId)
{
    int bool = 0;
    SDL_Event mouse1;

    SDL_QueryTexture(ALL_Buttons[5].normal_ver, NULL, NULL, &(ALL_Buttons[5].dim.w), &(ALL_Buttons[5].dim.h));
    SDL_RenderCopy(rend, ALL_Buttons[5].normal_ver, NULL, &ALL_Buttons[5].dim);
    SDL_RenderPresent(rend);
    do
    {
        if (SDL_PollEvent(&mouse1))
        {
            if (mouse1.type == SDL_MOUSEBUTTONUP)
            {
                if (SDL_BUTTON_LEFT)
                {
                    bool = 1;
                }
            }
        }

    } while (bool == 0);

    drawAll(bg, ALL_Buttons, interestPoints, wheelChair, printList, map, boomer, angle, writePointId);
}

void buttonSetDim(BUTTON* ALL_Buttons)
{
    ALL_Buttons[0].dim.x = 10;
    ALL_Buttons[0].dim.y = 0;
    ALL_Buttons[0].dim.w = 75;
    ALL_Buttons[0].dim.h = 75;
    ALL_Buttons[0].radius = ALL_Buttons[0].dim.w / 2;
    ALL_Buttons[0].enabled = TRUE;
    ALL_Buttons[0].mouseOnTop = FALSE;

    ALL_Buttons[1].dim.x = 1250;
    ALL_Buttons[1].dim.y = 600;
    ALL_Buttons[1].dim.w = 75;
    ALL_Buttons[1].dim.h = 75;
    ALL_Buttons[1].radius = ALL_Buttons[1].dim.w / 2;
    ALL_Buttons[1].enabled = TRUE;
    ALL_Buttons[1].mouseOnTop = FALSE;

    ALL_Buttons[2].dim.x = 1250;
    ALL_Buttons[2].dim.y = 680;
    ALL_Buttons[2].dim.w = 75;
    ALL_Buttons[2].dim.h = 75;
    ALL_Buttons[2].radius = ALL_Buttons[2].dim.w / 2;
    ALL_Buttons[2].enabled = TRUE;
    ALL_Buttons[2].mouseOnTop = FALSE;

    ALL_Buttons[3].dim.x = 10;
    ALL_Buttons[3].dim.y = 200;
    ALL_Buttons[3].dim.w = 75;
    ALL_Buttons[3].dim.h = 75;
    ALL_Buttons[3].radius = ALL_Buttons[3].dim.w / 2;
    ALL_Buttons[3].enabled = FALSE;
    ALL_Buttons[3].mouseOnTop = FALSE;

    ALL_Buttons[4].dim.x = 10;
    ALL_Buttons[4].dim.y = 100;
    ALL_Buttons[4].dim.w = 75;
    ALL_Buttons[4].dim.h = 75;
    ALL_Buttons[4].radius = ALL_Buttons[4].dim.w / 2;
    ALL_Buttons[4].enabled = FALSE;
    ALL_Buttons[4].mouseOnTop = FALSE;

    ALL_Buttons[5].dim.x = 480;
    ALL_Buttons[5].dim.y = 234;
    ALL_Buttons[5].dim.w = 75;
    ALL_Buttons[5].dim.h = 75;
    ALL_Buttons[5].enabled = FALSE;
    ALL_Buttons[5].mouseOnTop = FALSE;
}

INTERLIST* initInterestpoints(MAP* map)
{
    INTERESTPOINT interestPoint;
    INTERLIST* interestList = NULL;

    for (int i = 0; i < map->nodePointAmount; i++)
    {
        if (map->points[i].pointType == INTEREST)
        {
            interestPoint.id = map->points[i].id;
            interestPoint.x = map->points[i].x;
            interestPoint.y = map->points[i].y;
            interestPoint.type = RED;
            interestPoint.textureRed = bgInit("../resources/Button_red_locate.png");
            interestPoint.textureStart = bgInit("../resources/Button_green_locate.png");
            interestPoint.textureEnd = bgInit("../resources/Button_purple_locate.png");
            interestPoint.dim.w = 20;
            interestPoint.dim.h = 27;
            interestPoint.dim.x = interestPoint.x - 10;
            interestPoint.dim.y = interestPoint.y - 27;
            insertInterestPointInHead(&interestList, interestPoint);
        }
    }

    return(interestList);
}

void insertInterestPointInHead(INTERLIST** list, INTERESTPOINT point) {
    if (*list == NULL) {
        *list = (INTERLIST*)malloc(sizeof(INTERLIST));
        (*list)->interestpoint = point;
        (*list)->ptrInterest = NULL;
    }
    else {
        INTERLIST* aux = (INTERLIST*)malloc(sizeof(INTERLIST));
        aux->interestpoint = point;
        aux->ptrInterest = *list;
        *list = aux;
    }
}

//void drawAllInterestPoints(INTERLIST* interestPoints, STAGE type)
//{
//    while (interestPoints != NULL) // draw the interest points
//    {
//        if (type == RED)
//        {
//            if (interestPoints->interestpoint.type == type)
//            {
//                SDL_RenderCopy(rend, interestPoints->interestpoint.textureRed, NULL, &interestPoints->interestpoint.dim);
//                //SDL_RenderPresent(rend);
//            }
//        }
//        else if (type == START)
//        {
//            if (interestPoints->interestpoint.type == type)
//            {
//                SDL_RenderCopy(rend, interestPoints->interestpoint.textureStart, NULL, &interestPoints->interestpoint.dim);
//                //SDL_RenderPresent(rend);
//            }
//        }
//        else
//        {
//            if (interestPoints->interestpoint.type == type)
//            {
//                SDL_RenderCopy(rend, interestPoints->interestpoint.textureEnd, NULL, &interestPoints->interestpoint.dim);
//                //SDL_RenderPresent(rend);
//            }
//        }
//
//        interestPoints = interestPoints->ptrInterest;
//    }
//    //SDL_RenderPresent(rend);
//}

void setAllToRed(INTERLIST* interestList)
{
    while (interestList != NULL)
    {
        interestList->interestpoint.type = RED;
        interestList = interestList->ptrInterest;
    }
}

void setColor(INTERLIST* interestList, STAGE color, int id)
{
    BOOL done = FALSE;
    while (interestList != NULL && done == FALSE)
    {
        if (interestList->interestpoint.id == id)
        {
            interestList->interestpoint.type = color;
            done = TRUE;
        }
        else
        {
            interestList = interestList->ptrInterest;
        }
    }
}

//void redrawAll(SDL_Texture* bg, BUTTON ALL_Buttons[], INTERLIST* interestPoints, MAP* map, ANODE* printList)
//{
//    SDL_RenderCopy(rend, bg, NULL, NULL);
//
//    selectTexture(0, ALL_Buttons[0]);
//    selectTexture(0, ALL_Buttons[1]);
//    selectTexture(0, ALL_Buttons[2]);
//
//    setAllToRed(interestPoints);
//    drawAllInterestPoints(interestPoints, RED);
//
//    setAllToRed(interestPoints);
//
//    drawAllInterestPoints(interestPoints, RED);
//
//    drawPath(printList, map);
//}

//void changeMap(MAP** map, LINE lines[], INTERLIST** interestPoints, SDL_Texture** bg, STARTEND* twoPoints, BUTTON ALL_Buttons[], ANODE* printList)
//{
//    SDL_RenderClear(rend);
//    reInitAll(map, lines, interestPoints, bg, twoPoints);
//    redrawAll(*bg, ALL_Buttons, *interestPoints, *map, printList);
//}

//void freeOnChange(MAP* map, SDL_Texture* bg, INTERLIST* interestPoints)
//{
//    SDL_DestroyTexture(bg);
//    free(map);
//
//    INTERLIST* aux;
//
//    while (interestPoints != NULL)
//    {
//        SDL_DestroyTexture(interestPoints->interestpoint.textureEnd);
//        SDL_DestroyTexture(interestPoints->interestpoint.textureRed);
//        SDL_DestroyTexture(interestPoints->interestpoint.textureStart);
//
//        aux = interestPoints;
//        interestPoints = interestPoints->ptrInterest;
//        free(aux);
//    }
//}

void drawText(const char* message)
{
    int lenght;
    int pixelsPerCharacter = 13;
    lenght = strlen(message);

    TTF_Font* font = TTF_OpenFont("../resources/fonts/Calibri Regular.TTF", 100);

    SDL_Rect textLocation;
    textLocation.w = lenght * pixelsPerCharacter;
    textLocation.h = 30;
    textLocation.x = 10;
    textLocation.y = WINDOW_HEIGHT - textLocation.h + 3;

    SDL_Color color;
    color.a = 255;
    color.r = 255;
    color.g = 255;
    color.b = 255;

    SDL_Surface* textSurface;
    SDL_Texture* text;

    textSurface = TTF_RenderText_Blended(font, message, color);
    text = SDL_CreateTextureFromSurface(rend, textSurface);

    SDL_RenderCopy(rend, text, NULL, &textLocation);

    SDL_DestroyTexture(text);
    TTF_CloseFont(font);
    SDL_FreeSurface(textSurface);
}

void drawPathWheelChair(ANODE* printList, MAP* map)
{
    LINE aux;

    while (printList != NULL) {
        aux.x0 = map->points[printList->astar.from].x;
        aux.y0 = map->points[printList->astar.from].y;

        aux.x1 = map->points[printList->astar.current].x;
        aux.y1 = map->points[printList->astar.current].y;

        drawThiccLine(aux);
        printList = printList->ptrAstar;
    }
}

void initWheelChair(WHEELCHAIR* wheelChair)
{
    wheelChair->dim.w = 40;
    wheelChair->dim.h = 40;
    wheelChair->textureNoBoomer = bgInit("../resources/wheelNoboomer.png");
    wheelChair->textureWithBoomer = bgInit("../resources/wheelChair.png");
}

void initBoomer(BOOMER* boomer)
{
    boomer->dim.h = 40;
    boomer->dim.w = 30;
    boomer->male = TRUE;

    boomer->textureMale = bgInit("../resources/boomerMale.png");
    boomer->textureFemale = bgInit("../resources/boomerFemale.png");
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


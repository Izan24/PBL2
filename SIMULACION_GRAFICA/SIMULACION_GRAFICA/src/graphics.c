#include "general.h"
#include "graphics.h"

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

void drawLineTo(LINE line, int red, int green, int blue)
{
	SDL_SetRenderDrawColor(rend, red, green, blue, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(rend, line.x0, line.y0, line.x1, line.y1);
}

void drawPathDynamic(ANODE* printList, MAP* map) {
    LINE aux;

    while (printList != NULL) {
        aux.x0 = map->points[printList->astar.from].x;
        aux.y0 = map->points[printList->astar.from].y;

        aux.x1 = map->points[printList->astar.current].x;
        aux.y1 = map->points[printList->astar.current].y;

        drawThiccLine(aux);
        SDL_RenderPresent(rend);
        printList = printList->ptrAstar;
        SDL_Delay(1000 / 60);
    }
}

void drawPath(ANODE* printList, MAP* map) {
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

void drawThiccLine(LINE line) { // Ty Orib
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	for (int j = -1; j < 2; j++) {
		for (int k = -1; k < 2; k++) {
			SDL_RenderDrawLine(rend,
				line.x0 + j,
				line.y0 + k,
				line.x1 + j,
				line.y1 + k);
		}
	}
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

void drawWheelChair(WHEELCHAIR* wheelChair, const double angle)
{
    wheelChair->dim.x = (int)wheelChair->x - (wheelChair->dim.w / 2);
    wheelChair->dim.y = (int)wheelChair->y - (wheelChair->dim.h / 2);

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



#include "general.h"
#include "userInterface.h"

void intro()
{
    int alpha = 255;
    SDL_Texture* logo;
    SDL_Texture* logoUnfocus;


#ifndef LINUX_SISTEMA

    logo = bgInit("../resources/backgrounds/introIMG.png");
    logoUnfocus = bgInit("../resources/backgrounds/introIMGunfocused.png");

#endif // !LINUX_SISTEMA

#ifdef LINUX_SISTEMA

    logo = bgInit("./resources/backgrounds/introIMG.png");
    logoUnfocus = bgInit("./resources/backgrounds/introIMGunfocused.png");

#endif // LINUX_SISTEMA

    SDL_SetTextureBlendMode(logoUnfocus, SDL_BLENDMODE_BLEND);
    while (alpha > 0)
    {
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, logo, NULL, NULL);
        SDL_SetTextureAlphaMod(logoUnfocus, alpha);
        SDL_RenderCopy(rend, logoUnfocus, NULL, NULL);
        alpha -= 2;
        SDL_RenderPresent(rend);
#ifndef LINUX_SISTEMA

        SDL_Delay(1000 / 60);
#endif // !LINUX_SISTEMA

    }
    SDL_RenderCopy(rend, logo, NULL, NULL);
    SDL_RenderPresent(rend);

    SDL_Delay(250);
    SDL_RenderClear(rend);

    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(logoUnfocus);
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

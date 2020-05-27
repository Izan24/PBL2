#include "general.h"
#include "userInterface.h"
#include <math.h>


int initMenu(STARTEND* twoPoints, MAP* map, BUTTON* ALL_Buttons, LINE* lines) {

    SDL_Event mouse;
    MOUSE_POS* position = (MOUSE_POS*)malloc(sizeof(MOUSE_POS));
    static int change_yes = 0, points_yes = 0, go_yes = 0, closeRequested = 0;

    if (SDL_PollEvent(&mouse))
    {
        if (SDL_MOUSEMOTION)
        {
            if (mouse.motion.x > 0 && mouse.motion.x <= WINDOW_WIDTH)
            {
                if (mouse.motion.y > 0 && mouse.motion.y <= WINDOW_HEIGHT)
                {
                    position->x = mouse.motion.x;
                    position->y = mouse.motion.y;
                }
            }

            change_yes = verify_pos_mouse(ALL_Buttons[0], position);
            points_yes = verify_pos_mouse(ALL_Buttons[1], position);
            go_yes = verify_pos_mouse(ALL_Buttons[2], position);
        }
    }

    selectTexture(change_yes, ALL_Buttons[0]);
    selectTexture(points_yes, ALL_Buttons[1]);
    selectTexture(go_yes, ALL_Buttons[2]);

    switch (mouse.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (SDL_BUTTON_LEFT)
        {
            if (distMouseButton(ALL_Buttons[0], position))
            {
                closeRequested = deployMenuCall(ALL_Buttons, position);
            }

            if (distMouseButton(ALL_Buttons[1], position))
            {
                //select_points_map(&twoPoints, points);
            }

            if (distMouseButton(ALL_Buttons[2], position))
            {
                if (twoPoints->startP != NULL && twoPoints->endP != NULL)
                {

                    execAlgorithm(map, lines, twoPoints->startP, twoPoints->endP);
                }
                else
                {
                    error_message(ALL_Buttons[5]);
                }
            }
        }
        break;
    case SDL_QUIT:
        return 0;
    }

    return closeRequested;
}

int deployMenuCall(BUTTON* ALL_Buttons, MOUSE_POS* position)
{
    SDL_Event mouse; int swapTexture = 0, exit_yes = 0, bool = 0, closeRequested = 0;
    MOUSE_POS* position1 = (MOUSE_POS*)malloc(sizeof(MOUSE_POS));

    do
    {
        if (SDL_PollEvent(&mouse))
        {
            if (SDL_MOUSEMOTION)
            {
                if (mouse.motion.x > 0 && mouse.motion.x <= WINDOW_WIDTH)
                {
                    if (mouse.motion.y > 0 && mouse.motion.y <= WINDOW_HEIGHT)
                    {
                        position1->x = mouse.motion.x;
                        position1->y = mouse.motion.y;
                    }
                }

                swapTexture = verify_pos_mouse(ALL_Buttons[3], position1);
                exit_yes = verify_pos_mouse(ALL_Buttons[4], position1);

            }
        }

        selectTexture(swapTexture, ALL_Buttons[3]);
        selectTexture(exit_yes, ALL_Buttons[4]);
        SDL_RenderPresent(rend);

        if (mouse.type == SDL_MOUSEBUTTONDOWN)
        {
            if (distMouseButton(ALL_Buttons[4], position1))
            {
                printf("F");

            }
            if (distMouseButton(ALL_Buttons[0], position1))
            {
                bool = 1;
            }
            if (distMouseButton(ALL_Buttons[3], position1))
            {
                sdl_destroy();
                closeRequested = 1;
                bool = 1;
            }
        }

    } while (bool == 0);

    return closeRequested;
}

int distMouseButton(BUTTON button, MOUSE_POS* position)
{
    float distance = 0; int x, y; int boolean = 0;

    x = (button.dim.x + 37);
    y = (button.dim.y + 37);
    x = x - position->x;
    y = y - position->y;
    distance = (x * x) + (y * y);
    distance = sqrt(distance);
    if (distance < button.radius)
    {
        boolean = 1;
    }
    return boolean;
}

void selectTexture(int which, BUTTON button) {

    if (which == 1) {
        SDL_QueryTexture(button.grey_ver, NULL, NULL, &button.dim.w, &button.dim.h);
        SDL_RenderCopy(rend, button.grey_ver, NULL, &button.dim);
    }
    else {
        SDL_QueryTexture(button.normal_ver, NULL, NULL, &button.dim.w, &button.dim.h);
        SDL_RenderCopy(rend, button.normal_ver, NULL, &button.dim);
    }
}

int verify_pos_mouse(BUTTON button, MOUSE_POS* position)
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

void initButtons(BUTTON* ALL_Buttons)
{

    ALL_Buttons[0].normal_ver = bgInit("./resources/Button_menu.png");
    ALL_Buttons[0].grey_ver = bgInit("./resources/Button_menu_grey.png");
    ALL_Buttons[1].normal_ver = bgInit("./resources/Button_points.png");
    ALL_Buttons[1].grey_ver = bgInit("./resources/Button_points_grey.png");
    ALL_Buttons[2].normal_ver = bgInit("./resources/Button_go.png");
    ALL_Buttons[2].grey_ver = bgInit("./resources/Button_go_grey.png");

    ALL_Buttons[3].normal_ver = bgInit("./resources/exit_button.png");
    ALL_Buttons[3].grey_ver = bgInit("./resources/exit_button_grey.png");
    ALL_Buttons[4].normal_ver = bgInit("./resources/Swap_button.png");
    ALL_Buttons[4].grey_ver = bgInit("./resources/Swap_button_grey.png");

    ALL_Buttons[5].normal_ver = bgInit("./resources/error_message.png");

}

void error_message(BUTTON Error_button)
{
    int bool = 0;
    SDL_Event mouse1;

    SDL_QueryTexture(Error_button.normal_ver, NULL, NULL, &(Error_button.dim.w), &(Error_button.dim.h));
    SDL_RenderCopy(rend, Error_button.normal_ver, NULL, &Error_button);

    do
    {
        SDL_RenderPresent(rend);
        if (SDL_PollEvent(&mouse1))
        {
            if (mouse1.type == SDL_MOUSEBUTTONDOWN)
            {
                if (SDL_BUTTON_LEFT)
                {
                    bool = 1;
                }
            }
        }

    } while (bool == 0);
}

void buttonSetDim(BUTTON* ALL_Buttons)
{

    ALL_Buttons[0].dim.x = 10;
    ALL_Buttons[0].dim.y = 0;
    ALL_Buttons[0].dim.w = 75;
    ALL_Buttons[0].dim.h = 75;
    ALL_Buttons[0].radius = 37;


    ALL_Buttons[1].dim.x = 1250;
    ALL_Buttons[1].dim.y = 600;
    ALL_Buttons[1].dim.w = 75;
    ALL_Buttons[1].dim.h = 75;
    ALL_Buttons[1].radius = 37;


    ALL_Buttons[2].dim.x = 1250;
    ALL_Buttons[2].dim.y = 680;
    ALL_Buttons[2].dim.w = 75;
    ALL_Buttons[2].dim.h = 75;
    ALL_Buttons[2].radius = 37;


    ALL_Buttons[3].dim.x = 10;
    ALL_Buttons[3].dim.y = 200;
    ALL_Buttons[3].dim.w = 75;
    ALL_Buttons[3].dim.h = 75;
    ALL_Buttons[3].radius = 37;


    ALL_Buttons[4].dim.x = 10;
    ALL_Buttons[4].dim.y = 100;
    ALL_Buttons[4].dim.w = 75;
    ALL_Buttons[4].dim.h = 75;
    ALL_Buttons[4].radius = 37;


    ALL_Buttons[5].dim.x = 480;
    ALL_Buttons[5].dim.y = 234;
    ALL_Buttons[5].dim.w = 75;
    ALL_Buttons[5].dim.h = 75;
}


INTERLIST* initInterestpoints(MAP* map)
{
    INTERESTPOINT interestPoint;
    INTERLIST* interestList = NULL;

    for (int i = 0; i < map->nodePointAmount; i++)
    {
        if (map->points[i].pointType == INTEREST)
        {
            interestPoint.x = map->points[i].x;
            interestPoint.y = map->points[i].y;
            interestPoint.type = RED;
            interestPoint.texture = bgInit("./resources/Button_red_locate.png");
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
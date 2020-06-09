#include "general.h"
#include "init.h"

int SDLInit()
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("No se ha podido iniciar.");
        return 1;
    }

    window = SDL_CreateWindow("A* WheelChairs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

#ifndef LINUX_SISTEMA

    SDL_Surface* icon = IMG_Load("../debug/resources/aStaricon.png");
#endif // !LINUX_SISTEMA

#ifdef LINUX_SISTEMA
    SDL_Surface* icon = IMG_Load("./resources/aStaricon.png");
#endif // LINUX_SISTEMA


    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    if (!window)
    {
        printf("Error de ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
#ifndef LINUX_SISTEMA

    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#endif // !LINUS_SISTEMA

#ifdef LINUX_SISTEMA
    Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    rend = SDL_CreateRenderer(window, -1, flags);
#endif // LINUX_SISTEMA

    if (!rend)
    {
        printf("Error creating the renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Init();
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    return 0;
}

#ifndef LINUX_SISTEMA

struct Cursors initCursor() {
    struct Cursors cursor;
    SDL_Surface* cursorSurf = IMG_Load("./resources/interface/cursor1.png");
    cursor.arrow = SDL_CreateColorCursor(cursorSurf, 0, 0);
    SDL_FreeSurface(cursorSurf);
    cursorSurf = IMG_Load("./resources/interface/cursor2.png");
    cursor.hand = SDL_CreateColorCursor(cursorSurf, 0, 0);
    SDL_FreeSurface(cursorSurf);
    return cursor;
}
#endif // !LINUX_SISTEMA

#ifdef LINUX_SISTEMA
struct Cursors initCursor() {
    struct Cursors cursor;
    SDL_Surface* cursorSurf = IMG_Load("./resources/interface/cursor1.png");
    cursor.arrow = SDL_CreateColorCursor(cursorSurf, 0, 0);
    SDL_FreeSurface(cursorSurf);
    cursorSurf = IMG_Load("./resources/interface/cursor2.png");
    cursor.hand = SDL_CreateColorCursor(cursorSurf, 0, 0);
    SDL_FreeSurface(cursorSurf);
    return cursor;
}
#endif //



SDL_Texture* bgInit(const char* img)
{
    SDL_Surface* surface;
    SDL_Texture* bg;

    surface = IMG_Load(img);

    bg = SDL_CreateTextureFromSurface(rend, surface);

    SDL_FreeSurface(surface);

    return bg;
}

void initButtons(BUTTON* ALL_Buttons)
{
#ifndef LINUX_SISTEMA

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
#endif // !LINUX_SISTEMA

#ifdef LINUX_SISTEMA
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
#endif // LINUX_SISTEMA


    buttonSetDim(ALL_Buttons);
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
#ifndef LINUX_SISTEMA
            interestPoint.textureRed = bgInit("../resources/Button_red_locate.png");
            interestPoint.textureStart = bgInit("../resources/Button_green_locate.png");
            interestPoint.textureEnd = bgInit("../resources/Button_purple_locate.png");
#endif // !LINUX_SISTEMA


#ifdef LINUX_SISTEMA
            interestPoint.textureRed = bgInit("./resources/Button_red_locate.png");
            interestPoint.textureStart = bgInit("./resources/Button_green_locate.png");
            interestPoint.textureEnd = bgInit("./resources/Button_purple_locate.png");
#endif // LINUX_SISTEMA

            interestPoint.dim.w = 20;
            interestPoint.dim.h = 27;
            interestPoint.dim.x = interestPoint.x - 10;
            interestPoint.dim.y = interestPoint.y - 27;
            insertInterestPointInHead(&interestList, interestPoint);
        }
    }

    return(interestList);
}

void initWheelChair(WHEELCHAIR* wheelChair)
{
    wheelChair->dim.w = 40;
    wheelChair->dim.h = 40;
#ifndef LINUX_SISTEMA
    wheelChair->textureNoBoomer = bgInit("../resources/wheelNoboomer.png");
    wheelChair->textureWithBoomer = bgInit("../resources/wheelChair.png");
#endif

#ifdef LINUX_SISTEMA
    wheelChair->textureNoBoomer = bgInit("./resources/wheelNoboomer.png");
    wheelChair->textureWithBoomer = bgInit("./resources/wheelChair.png");
#endif
}

void initBoomer(BOOMER* boomer)
{
    boomer->dim.h = 40;
    boomer->dim.w = 30;
    boomer->male = TRUE;
#ifndef LINUX_SISTEMA

    boomer->textureMale = bgInit("../resources/boomerMale.png");
    boomer->textureFemale = bgInit("../resources/boomerFemale.png");
#endif // !LINUX_SISTEMA

#ifdef LINUX_SISTEMA
    boomer->textureMale = bgInit("./resources/boomerMale.png");
    boomer->textureFemale = bgInit("./resources/boomerFemale.png");
#endif // !LINUX_SISTEMA

}


#include "general.h"

int main(int argv, char* argc)
{
    MAP* map;

    SDLInit();

    map = loadMap();

    intro();

    loop(&map);

    return 0;
}

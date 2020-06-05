#include "general.h"

int main(int argc, char* argv[])
{
    MAP* map;

    SDLInit();

    map = loadMap();

    intro();

    loop(&map);

    return 0;
}

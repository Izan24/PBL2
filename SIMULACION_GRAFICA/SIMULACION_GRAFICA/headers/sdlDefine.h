#ifndef SDL_DEFINE
#define SDL_DEFINE

////////////////////SDL/////////////////////
#include "sdl/SDL.h"
#include "sdl/SDL_image.h"
#include "sdl/SDL_mixer.h"
#include "sdl/SDL_ttf.h"

SDL_Renderer* rend;
SDL_Window* window;

int sdl_init(); // Return 0 on success and 1 if there was a problem
int sdl_destroy(); // Destroys all the SDL stuff (Returns 1 on success)

#endif // !SDL_DEFINE

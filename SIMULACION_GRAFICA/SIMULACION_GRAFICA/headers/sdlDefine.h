#ifndef SDL_DEFINE
#define SDL_DEFINE

#include "sdl/SDL.h"
#include "sdl/SDL_image.h"
#include "sdl/SDL_mixer.h"
#include "sdl/SDL_ttf.h"

SDL_Renderer* rend; // A global variable for the renderer from the SDL
SDL_Window* window; // A global variable for the window from the SDL
SDL_Surface* surface;

// Initializes the SDL libraries. Returns 0 on success and 1 if there was a problem
int sdl_init();

// Destroys all the SDL variables (Returns 1 on success)
int sdl_destroy();

#endif // !SDL_DEFINE

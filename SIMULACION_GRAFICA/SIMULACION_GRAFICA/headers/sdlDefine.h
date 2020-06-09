#ifndef SDL_DEFINE
#define SDL_DEFINE

#include "sdl/SDL.h"
#include "sdl/SDL_image.h"
//#include "sdl/SDL_mixer.h"
#include "sdl/SDL_ttf.h"

SDL_Renderer* rend; // A global variable for the renderer from the SDL
SDL_Window* window; // A global variable for the window from the SDL

// Destroys all the SDL variables (Returns 1 on success)
int SDLDestroy();

#endif // !SDL_DEFINE

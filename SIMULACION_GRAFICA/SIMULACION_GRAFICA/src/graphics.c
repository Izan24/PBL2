#include <stdio.h>
#include "general.h"
#include "maps.h"
#include "sdlDefine.h"
#include "graphics.h"


void drawLineTo(LINE line, int red, int green, int blue)
{
	SDL_SetRenderDrawColor(rend, red, green, blue, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(rend, line.x0, line.y0, line.x1, line.y1);
}

SDL_Texture* bgInit(const char* img)
{
	SDL_Surface* surface;
	SDL_Texture* bg;

	surface = IMG_Load(img);

	bg = SDL_CreateTextureFromSurface(rend, surface);

	SDL_FreeSurface(surface);

	return bg;
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




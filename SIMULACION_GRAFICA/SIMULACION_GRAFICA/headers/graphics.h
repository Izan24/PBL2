#ifndef GRAPHICS_H
#define GRAPHICS_H


void drawLineTo(LINE line, int red, int green, int blue); // Draw a line 

SDL_Texture* bgInit(const char* img); //Returns a pointer to the Background

void drawThiccLine(LINE line); // Draw a THICC line

#endif // !GRAPHICS_H

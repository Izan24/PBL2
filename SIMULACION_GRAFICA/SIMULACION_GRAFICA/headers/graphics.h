#ifndef GRAPHICS_H
#define GRAPHICS_H

// Draws a line inputing a LINE structure. It also accepts colors as input
void drawLineTo(LINE line, int red, int green, int blue);

//Loads a textur inputing a file name
SDL_Texture* bgInit(const char* img);

// Draws a THICCCC line
void drawThiccLine(LINE line);


#endif // !GRAPHICS_H

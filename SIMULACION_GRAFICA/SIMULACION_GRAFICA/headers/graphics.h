#ifndef GRAPHICS_H
#define GRAPHICS_H


typedef struct line {
    int x1; // First point of the line (x axis)
    int x2; // Second point of the line (x axis)
    int y1; // First point of the line (x axis)
    int y2; // Second point of the line (y axis)
}LINE;


void draw_line_to(LINE line);

SDL_Texture* bg_init(char* img); //Returns a pointer to the Background


#endif // !GRAPHICS_H

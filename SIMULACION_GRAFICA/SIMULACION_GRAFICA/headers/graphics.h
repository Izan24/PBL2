#ifndef GRAPHICS_H
#define GRAPHICS_H

// draw all ths sprites of the app
void drawAll(SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, WHEELCHAIR* wheelChair, ANODE* printList, MAP* map, BOOMER* boomer, double angle, int writePointId);

// Draws a line inputing a LINE structure. It also accepts colors as input
void drawLineTo(LINE line, int red, int green, int blue);

// Draws a path step by step
void drawPathDynamic(ANODE* printList, MAP* map);

// Copies all the path to renderer
void drawPath(ANODE* printList, MAP* map);

// Draws the path of the wheelchair
void drawPathWheelChair(ANODE* printList, MAP* map);

// Draws a THICCCC line
void drawThiccLine(LINE line);

// it creates a image to warn the user that didn t choose the star / end points
void errorMessage(BUTTON* ALL_Buttons, SDL_Texture* bg, INTERLIST* interestPoints, MAP* map, ANODE* printList, WHEELCHAIR* wheelChair, BOOMER* boomer, double angle, int writePointId);

// prints all the buttons in the window
void printButtons(BUTTON* ALL_Buttons);

// prints the interest points of the selected map
void printInterestPoints(INTERLIST* interestPoints);

// draw the names of the interest points
void drawText(const char* message);

//draw the sprite of the wheelchair 
void drawWheelChair(WHEELCHAIR* wheelChair, const double angle);

// it draws the old person 
void drawBoomer(BOOMER* boomer);

#endif // !GRAPHICS_H

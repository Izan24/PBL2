#ifndef INIT_H
#define INIT_H


// Initializes the SDL libraries. Returns 0 on success and 1 if there was a problem
int SDLInit();

struct Cursors initCursor();

//Loads a textur inputing a file name
SDL_Texture* bgInit(const char* img);

// Inits the buttons
void initButtons(BUTTON* ALL_Buttons);

// Sets the values of the buttons 
void buttonSetDim(BUTTON* ALL_Buttons);

// Inits the interest points of the selected map
INTERLIST* initInterestpoints(MAP* map);

// give values to the Wheelchair 
void initWheelChair(WHEELCHAIR* wheelChair);

// give values to the old person 
void initBoomer(BOOMER* boomer);

#endif // !INIT_H


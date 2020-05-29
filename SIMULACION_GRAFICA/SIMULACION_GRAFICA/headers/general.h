#ifndef GENERAL_H

#define GENERAL_H
#define MAX_STR 128 // Max chars of a string
#define MAX_CONNECTIONS 10 // Max connections of a single point
#define WINDOW_WIDTH (1360) // The width of the window
#define WINDOW_HEIGHT (768) // The height of the window
#define MAX_NODE (300) // The number of the maximum nodes a map can have
#define MAX_BUTTON_N 6

typedef enum boolean{FALSE, TRUE}BOOL; // A simple boolean enum
typedef enum type{NODE, CROSSWALK, INTEREST}TYPE; // The types of the points being NODE (0), CROSSWALK (1) or INTEREST (2).

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <commdlg.h>
#include "sdlDefine.h"
#include "maps.h"
#include "algorithm.h"
#include "graphics.h"
#include "userInterface.h"
#include "initAplication.h"




#endif // GENERAL_H

#ifndef GENERAL_H

#define GENERAL_H
#define MAX_STR 128 // Max chars of a string
#define MAX_CONNECTIONS 10 // Max connections of a single point
#define WINDOW_WIDTH (1360) // The width of the window
#define WINDOW_HEIGHT (768) // The height of the window
#define MAX_NODE (300) // The number of the maximum nodes a map can have
#define MAX_BUTTON_N 6

typedef enum boolean{FALSE, TRUE}BOOL; // A simple boolean enum


#include <stdlib.h>
#include <stdio.h>
#ifndef LINUX_SISTEMA
#include <windows.h>
#include <commdlg.h>
#endif // !LINUX_SISTEMA
#include <math.h>
#include "sdlDefine.h"
#include "loadJSON.h"
#include "algorithm.h"
#include "userInterface.h"
#include "graphics.h"
#include "mainLoop.h"
#include "init.h"

#endif // GENERAL_H

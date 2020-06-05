#ifndef MAINLOOP_H
#define MAINLOOP_H


enum action { DEPLOYABLE_MENU, SELECT_POINTS, START_PATH, EXIT_APP, CHANGE_MAP, CLICK_POINT };


void initApp(MAP* map, INTERLIST** interestPoints, SDL_Texture** bg, STARTEND** twoPoints, ANODE** printList, MOUSE_POS** position, WHEELCHAIR** wheelChair, BOOMER** boomer, struct Cursors cursor, double* angle, int* thId, int* writePointId, BUTTON* ALL_Buttons);

BOOL loop(MAP** map);
BOOL checkActions(MAP** map, ANODE** printList, STARTEND** twoPoints, INTERLIST** interestPoints, BUTTON* ALL_Buttons, SDL_Texture** bg, MOUSE_POS** position, WHEELCHAIR** wheelChair, BOOMER** boomer, struct Cursors cursor, int* thId, int* writePointId, double angle);

BOOL startPath(MAP* map, SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, ANODE* printList, STARTEND* twoPoints, WHEELCHAIR* wheeelChair, BOOMER* boomer, int thId);

BOOL moveWheelChair(MAP* map, SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, ANODE* printList, WHEELCHAIR* wheelChair, BOOMER* boomer, int writePoint);
void unitaryVector(float* x, float* y);
void chechVectorStatus(WHEELCHAIR* wheelChair, float vectorY, float vectorX, int nextY, int nextX);
double returnAngleDegree(float vectorX, NODEPOINT p1, NODEPOINT p2);

int verifyPosMouse(BUTTON button, MOUSE_POS* position);
int checkClick(MOUSE_POS position, BUTTON* ALL_Buttons);
int checkClickInterestPoint(MAP* map, INTERLIST* interestList, NODEPOINT mousePosition);
void verifyMouseOnTop(BUTTON* ALL_Buttons, MOUSE_POS* position);
int distMouseButton(BUTTON button, MOUSE_POS* position);

void selectPointsMap(STARTEND** twoPoints, INTERLIST* iPointsList, MOUSE_POS* mousePos, MAP* map);
void selectStartEndP(MAP* map, INTERLIST* iPointsList, STARTEND** twoPoints, int startEnd); // Satrtend == 0 if you want to get the start point and == 1 if you want to get the endP

int searchTH(MAP* map);

void destroyAll(MAP* map, INTERLIST* interestPoints, SDL_Texture* bg, STARTEND* twoPoints, ANODE* printList, MOUSE_POS* position, WHEELCHAIR* wheelChair, BOOMER* boomer, struct Cursors cursor);
#endif // !MAINLOOP_H
#ifndef MAINLOOP_H
#define MAINLOOP_H


enum action { DEPLOYABLE_MENU, SELECT_POINTS, START_PATH, EXIT_APP, CHANGE_MAP, CLICK_POINT };

void initApp(MAP* map, INTERLIST** interestPoints, SDL_Texture** bg, STARTEND** twoPoints, ANODE** printList, MOUSE_POS** position, WHEELCHAIR** wheelChair, BOOMER** boomer, struct Cursors cursor, double* angle, int* thId, int* writePointId);
BOOL loop(MAP** map, INTERLIST** interestPoints, SDL_Texture** bg, STARTEND** twoPoints, ANODE** printList, BUTTON* ALL_Buttons, MOUSE_POS** position, WHEELCHAIR** wheelChair, BOOMER** boomer, struct Cursors cursor, double angle, int thId, int writePointId);

BOOL checkActions(MAP** map, ANODE** printList, STARTEND** twoPoints, INTERLIST** interestPoints, BUTTON* ALL_Buttons, SDL_Texture** bg, MOUSE_POS** position, WHEELCHAIR** wheelChair, BOOMER** boomer, struct Cursors cursor, int* thId, int* writePointId, double angle);
int checkClick(MOUSE_POS position, BUTTON* ALL_Buttons);
void startPath(MAP* map, SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, ANODE* printList, STARTEND* twoPoints, WHEELCHAIR* wheeelChair, BOOMER* boomer, int thId);
int checkClickInterestPoint(MAP* map, INTERLIST* interestList, NODEPOINT mousePosition);
void swapButtonState(BUTTON* ALL_Buttons);
void drawAll(SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, WHEELCHAIR* wheelChair, ANODE* printList, MAP* map, BOOMER* boomer, double angle, int writePointId);
void printButtons(BUTTON* ALL_Buttons);
void verifyMouseOnTop(BUTTON* ALL_Buttons, MOUSE_POS* position);
void printInterestPoints(INTERLIST* interestPoints);
void moveWheelChair(MAP* map, SDL_Texture* bg, BUTTON* ALL_Buttons, INTERLIST* interestPoints, ANODE* printList, WHEELCHAIR* wheelChair, BOOMER* boomer, int writePoint);
void drawPathWheelChair(ANODE* printList, MAP* map);
void unitaryVector(float* x, float* y);
void drawWheelChair(WHEELCHAIR* wheelChair, const double angle);
void chechVectorStatus(WHEELCHAIR* wheelChair, float vectorY, float vectorX, int nextY, int nextX);
double returnAngleDegree(float vectorX, NODEPOINT p1, NODEPOINT p2);
void drawBoomer(BOOMER* boomer);
void destroyAll(MAP* map, INTERLIST* interestPoints, SDL_Texture* bg, STARTEND* twoPoints, ANODE* printList, MOUSE_POS* position, WHEELCHAIR* wheelChair, BOOMER* boomer, struct Cursors cursor);

#endif // !MAINLOOP_H
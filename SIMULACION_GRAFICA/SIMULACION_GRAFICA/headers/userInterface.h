#ifndef USERINTERFACE
#define USERINTERFACE

typedef enum Stage { RED, START, END }STAGE;

typedef struct Mouse_pos {
	int y;
	int x;
}MOUSE_POS;


struct Cursors {
	SDL_Cursor* arrow;
	SDL_Cursor* hand;
};

typedef struct Wheelchair {
	float x;
	float y;
	float angle;
	BOOL boomerOnTop;
	SDL_Texture* textureNoBoomer;
	SDL_Texture* textureWithBoomer;
	SDL_Rect dim;
}WHEELCHAIR;

typedef struct Boomer {
	int x;
	int y;
	SDL_Texture* textureMale;
	SDL_Texture* textureFemale;
	BOOL male;
	SDL_Rect dim;
}BOOMER;

typedef struct Button {
	SDL_Rect dim;
	BOOL enabled;
	int radius;
	BOOL mouseOnTop;
	SDL_Texture* normal_ver;
	SDL_Texture* grey_ver;
	//int state;
}BUTTON;

typedef struct startEnd {
    NODEPOINT* startP;
    NODEPOINT* endP;
}STARTEND;

typedef struct Interestpoint {
	int id;
	int x;
	int y;
	enum Stage type;
	SDL_Texture* textureRed;
	SDL_Texture* textureStart;
	SDL_Texture* textureEnd;
	SDL_Rect dim;
}INTERESTPOINT;

typedef struct interList {
	INTERESTPOINT interestpoint;
	struct interList* ptrInterest; // Pointer to the next item of the list
}INTERLIST;

void intro();
//int initMenu(STARTEND* twoPoints, MAP** map, BUTTON* ALL_Buttons, LINE* lines, INTERLIST** interestPoints, SDL_Texture** bg, struct Cursors cursor);
int verifyPosMouse(BUTTON button, MOUSE_POS* position);
//int deployMenuCall(BUTTON* ALL_Buttons, MOUSE_POS* position, SDL_Event mouse, INTERLIST** interestPoints, SDL_Texture** bg, MAP** map, LINE lines[], STARTEND* twoPoints, ANODE* printlist);
int distMouseButton(BUTTON button, MOUSE_POS* position);
//void selectTexture(int which, BUTTON button);
void selectPointsMap(STARTEND** twoPoints, INTERLIST* iPointsList, MOUSE_POS* mousePos, MAP* map);
void selectStartEndP(MAP* map, INTERLIST* iPointsList, STARTEND** twoPoints, int startEnd); // Satrtend == 0 if you want to get the start point and == 1 if you want to get the endP
int verifyPosMouse(BUTTON button, MOUSE_POS* position);
void initButtons(BUTTON* ALL_Buttons);
void errorMessage(BUTTON* ALL_Buttons, SDL_Texture* bg, INTERLIST* interestPoints, MAP* map, ANODE* printList, WHEELCHAIR* wheelChair, BOOMER* boomer, double angle, int writePointId);
void buttonSetDim(BUTTON* ALL_Buttons);
INTERLIST* initInterestpoints(MAP* map);
void insertInterestPointInHead(INTERLIST** list, INTERESTPOINT point);
//void drawAllInterestPoints(INTERLIST* interestPoints, STAGE type);
//void setAllToRed(INTERLIST* interestList);
void setColor(INTERLIST* interestList, STAGE color, int id);
//void redrawAll(SDL_Texture* bg, BUTTON ALL_Buttons[], INTERLIST* interestPoints, MAP* map, ANODE* printList);
//void changeMap(MAP** map, LINE lines[], INTERLIST** interestPoints, SDL_Texture** bg, STARTEND* twoPoints, BUTTON ALL_Buttons[], ANODE* printList);
//void freeOnChange(MAP* map, SDL_Texture* bg, INTERLIST* interestPoints);
void drawText(const char* message);
int searchTH(MAP* map);
void initWheelChair(WHEELCHAIR* wheelChair);
void initBoomer(BOOMER* boomer);



/*

0 deployable menu
1 points_button
2 go_button
3 exit_button
4 Swap_button
5 Error_button

*/


#endif


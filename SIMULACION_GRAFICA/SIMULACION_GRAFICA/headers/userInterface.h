#ifndef USERINTERFACE
#define USERINTERFACE

typedef enum Stage { RED, START, END };

typedef struct Mouse_pos {

	int y;
	int x;
}MOUSE_POS;

typedef struct Button {


	SDL_Rect dim;
	int radius;
	SDL_Texture* normal_ver;
	SDL_Texture* grey_ver;
}BUTTON;

typedef struct startEnd {
    NODEPOINT* startP;
    NODEPOINT* endP;
}STARTEND;

typedef struct Interestpoint {
	int x;
	int y;
	enum Stage type;
	SDL_Texture* texture;
	SDL_Rect dim;
}INTERESTPOINT;

typedef struct interList {
	INTERESTPOINT interestpoint;
	struct interList* ptrInterest; // Pointer to the next item of the list
}INTERLIST;

int initMenu(STARTEND* twoPoints, MAP* map, BUTTON* ALL_Buttons, LINE* lines);
int verify_pos_mouse(BUTTON button, MOUSE_POS* position);
int distMouseButton(BUTTON button, MOUSE_POS* position);
void selectTexture(int which, BUTTON button);
void buttonSetDim(BUTTON* ALL_Buttons);
void initButtons(BUTTON* ALL_Buttons);
void error_message(BUTTON Error_button);

int deployMenuCall(BUTTON* ALL_Buttons, MOUSE_POS* position);

INTERLIST* initInterestpoints(MAP* map);
void insertInterestPointInHead(INTERLIST** list, INTERESTPOINT point);
/*

0 change_map_button
1 points_button
2 go_button
3 exit_button
4 Swap_button
5 Error_button


*/
#endif


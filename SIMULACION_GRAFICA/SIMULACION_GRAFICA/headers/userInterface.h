#ifndef USERINTERFACE
#define USERINTERFACE

typedef enum Stage { RED, START, END }STAGE;

/*
Position of the mouse.
It has 2 coordinate points x and y
*/
typedef struct Mouse_pos {
	int y; // The Y position of the mouse in the screen
	int x; // The x position of the mouse in the screen
}MOUSE_POS;

/*
The sprite of the cursor
It has 2 types. The arrow and the hand
*/
struct Cursors {
	SDL_Cursor* arrow; // Normal arrow
	SDL_Cursor* hand; // hand cursor
};

/*
Wheelchair 
This is the object that is going to be mooving in the map
*/
typedef struct Wheelchair {
	float x; // The X coord
	float y; // The Y coord
	float angle; // the angle the chair is facing at
	BOOL boomerOnTop; // Specifies if there is an old person sat in the wheelchair
	SDL_Texture* textureNoBoomer; // Just the chair
	SDL_Texture* textureWithBoomer; // The chair with the old person on top of it
	SDL_Rect dim; // The dimension of the rect where the wheelchair is going to be drawn
}WHEELCHAIR;

typedef struct Boomer {
	int x; // the x coord
	int y; // the y coord
	SDL_Texture* textureMale; //the texture of the image of the old male
	SDL_Texture* textureFemale; //the texture of the image of the old female
	BOOL male; // condition to set a male o female
	SDL_Rect dim; // the values of the image
}BOOMER;

typedef struct Button {
	SDL_Rect dim;// the values of the image
	BOOL enabled;// condition to set the grey or normal texture
	int radius; // the radius of the button
	BOOL mouseOnTop; // condition to know if the mouse is over the button
	SDL_Texture* normal_ver; // the normal version of the image
	SDL_Texture* grey_ver; // the grey version of the image
	//int state;
}BUTTON;

typedef struct startEnd {
    NODEPOINT* startP; // the start point choose by the user
    NODEPOINT* endP; // the end point choose by the user
}STARTEND;

typedef struct Interestpoint {
	int id; // the identification number of the interest points
	int x;// the x coord
	int y;// the y coord
	enum Stage type; //  to know the point type
	SDL_Texture* textureRed; // to get the red image
	SDL_Texture* textureStart;// to get the start image (grenn)
	SDL_Texture* textureEnd;// to get the end image (purple)
	SDL_Rect dim;// the values of the image
}INTERESTPOINT;

typedef struct interList {
	INTERESTPOINT interestpoint; // to get a list of interest points
	struct interList* ptrInterest; // Pointer to the next item of the list
}INTERLIST;


//  creates the firts credits of the app
void intro();

// verify if the mouse is on one button
int verifyPosMouse(BUTTON button, MOUSE_POS* position);

// insert points in the main list
void insertInterestPointInHead(INTERLIST** list, INTERESTPOINT point);

//  change all the interest points images to red
void setAllToRed(INTERLIST* interestList);

//  select the color of the interst point
void setColor(INTERLIST* interestList, STAGE color, int id);

//  change the State of the buttons to change the color of the image
void swapButtonState(BUTTON* ALL_Buttons);

/*
0 deployable menu
1 points_button
2 go_button
3 exit_button
4 Swap_button
5 Error_button
*/

/*
	¡ALTO!
	Si lees esto
	Primero altoke mi rey.
	Segundo un minuto de silencio por mis panas
	RIP-> go_yes, change_yes, points_yes
*/

#endif


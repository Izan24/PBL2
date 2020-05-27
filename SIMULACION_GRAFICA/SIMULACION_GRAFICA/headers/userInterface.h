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
	struct Interestpoint* ptrInterest;

}INTERESTPOINT;



int init_menu(STARTEND* twoPoints, MAP* map, BUTTON* ALL_Buttons, LINE* lines);
int verify_pos_mouse(BUTTON button, MOUSE_POS* position);
int dist_mouse_button(BUTTON button, MOUSE_POS* position);
void select_texture(int which, BUTTON button);
void button_set_dim(BUTTON* ALL_Buttons);
void init_buttons(BUTTON* ALL_Buttons);
void error_message(BUTTON Error_button);

int deploy_menu_call(BUTTON* ALL_Buttons, MOUSE_POS* position);

INTERESTPOINT* initInterestpoints(MAP* map);
void insertInterestPointInHead(INTERESTPOINT** list, INTERESTPOINT* point);

/*

0 change_map_button
1 points_button
2 go_button
3 exit_button
4 Swap_button
5 Error_button


*/
#endif


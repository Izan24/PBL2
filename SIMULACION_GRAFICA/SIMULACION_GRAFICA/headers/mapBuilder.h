#ifndef MAPBUILDER_H
#define MAPBUILDER_H

SDL_Window* windowMB;
SDL_Renderer* rendMB;

typedef struct mapAndImg {
	char rarPath[MAX_STR];
	char jsonName[MAX_STR];
	char IMGName[MAX_STR];
}MAPnames;

int mapBuilderMain();
void MBinit();
char* imageScreen();
MAP* mapScreen(char* imgFile);



#endif // !MABUILDER_H

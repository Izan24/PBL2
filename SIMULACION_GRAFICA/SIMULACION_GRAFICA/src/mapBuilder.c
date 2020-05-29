#include "general.h"
#include "mapBuilder.h"


int mapBuilderMain() {
	//MBinit();
	//char* pngFile = FileName("png");
	char * filename = imageScreen();
	if (filename == -1) return -1;
	mapScreen(filename);
}

void MBinit() {
	windowMB = SDL_CreateWindow("Creador de Mapas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if (!windowMB) {
		printf("No se ha podido iniciar: %s\n", SDL_GetError());
		return -1;
	}

	Uint32 rendMBer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	rendMB = SDL_CreateRenderer(windowMB, -1, rendMBer_flags);

	if (rendMB == NULL) {
		printf("No se ha podido inicializar el renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(windowMB);
		return -1;
	}
	return 0;
}

char* imageScreen() {
	int close_requested = 0, exit = 0;
	SDL_Texture* IMGbg = bgInit("./resources/interface/MBimgscreen.png");
	printf("\n%d", SDL_RenderClear(rend));
	printf("\n%d", SDL_RenderCopy(rend, IMGbg, NULL, NULL));

	SDL_Rect imgIconRect;
	imgIconRect.w = 200;
	imgIconRect.h = 200;
	imgIconRect.x = WINDOW_WIDTH / 2 - 200 / 2;
	imgIconRect.y = WINDOW_HEIGHT / 2 - 200 / 2;
	SDL_Texture* imgIcon = bgInit("./resources/interface/imgFile.png");
	printf("\n%d", SDL_RenderCopy(rend, imgIcon, NULL, &imgIconRect));
	SDL_RenderPresent(rend);

	SDL_Event event;
	while (exit == 0){
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				close_requested = 1;
				exit = 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.x > imgIconRect.x && event.button.x < imgIconRect.x + imgIconRect.w)
					if (event.button.y > imgIconRect.y && event.button.y < imgIconRect.y + imgIconRect.h) {
						exit = 1;
						break;
					}
			}
		}
	}

	if (close_requested != 1) {
		char* pngFIleAux = FileName("png");
		char* pngFile = (char*)malloc(sizeof(pngFIleAux));
		strcpy(pngFile, pngFIleAux);
		return pngFile;
	}
	else return -1;

	SDL_DestroyTexture(IMGbg);
	SDL_DestroyTexture(imgIcon);
}

MAP* mapScreen(char * imgFile) {
	SDL_Texture* mapBg = bgInit(imgFile);
	printf("\n%d", SDL_RenderClear(rend));
	printf("\n%d", SDL_RenderCopy(rend, mapBg, NULL, NULL));

	SDL_Rect itSelector;
	itSelector.w = 50;
	itSelector.h = 50;
	itSelector.x = WINDOW_WIDTH - 75;
	itSelector.y = WINDOW_HEIGHT - 75;

	//SDL_Texture* imgIcon = bgInit("../../resources/interface/imgFile.png");
	SDL_Texture* itSelectorTx = bgInit("../../resources/interface/Selector.png");
	LPTSTR currentDir = (LPTSTR*)malloc(sizeof(LPTSTR));
	DWORD bufferLenght;
	GetCurrentDirectory( GetCurrentDirectory(0, NULL), currentDir);
	char izenArtx[MAX_PATH];
	int counterZeros = 0, count = 0, i = 0;
	while (counterZeros < 3) {
		if ((currentDir[i] != '\0')) {
			izenArtx[count] = *(currentDir + i);
			count++;
			counterZeros = 0;
		}
		else {
			counterZeros++;
		}
		i++;
	}
	izenArtx[count] = '\0';
	izenArtx[count+1] = '\0';
	izenArtx[count + 2] = '\0';
	printf("%s", izenArtx);
	printf("\n%d", SDL_RenderCopy(rend, itSelectorTx, NULL, &itSelector));
	SDL_RenderPresent(rend);

	getchar();
}
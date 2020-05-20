#include "general.h"
#include "maps.h"
#include "JSON-C/json.h"

MAP* loadMap() {
    MAP* map = (MAP*)malloc(sizeof(MAP));
    char* filename = mapFileName();
    char* unparsedJson = readJSON(filename);
}

char* mapFileName() { // Opens a dialog box to select a file and returns its name along with its path.
    CHAR filename[MAX_PATH];
	int i = 0, count=0, counterZeros=0;
    char *izenArtx = (char*)malloc(sizeof(char)*128);

    INT integerio = ChooseProgram(filename);
    if (integerio == 0) return '\0';
    while (counterZeros<3) {
        if ((filename[i] != '\0')) {
            izenArtx[count] = *(filename + i);
            count++;
            counterZeros = 0;
        }
        else {
            counterZeros++;
        }
        i++;
    }
    izenArtx[count] = '\0';
    return izenArtx;
}

INT ChooseProgram(CHAR* FileName) { // Uses windows.h function GetOpenFileName to open a dialog box and let the user select a file.
    OPENFILENAME  ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.hInstance = NULL;
    ofn.lpstrFilter = L"JSON files\0*.json\0\0";
    ofn.lpstrFile = FileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = L"Aukeratu mapa";
    ofn.Flags = OFN_NONETWORKBUTTON | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    if (!GetOpenFileName(&ofn))
        return(0);
    return 1;
}

char* readJSON(char * FileName) {
    char aux[MAX_STR];
    char* buffer = (char*)malloc(sizeof(char)*65536);
    FILE* fileJSON = fopen(FileName, "r");
    fread(buffer, sizeof(char), 65536, fileJSON);
    fclose(fileJSON);
    return buffer;
}

void printMap(MAP* map) {
    printf("\nName: %s", map->mapName);
    printf("\nPoint Amounts: %d", map->nodePointAmount);
    for (int i = 0; i < map->nodePointAmount; i++) {
        printf("\n\tID: %s", map->points[i].id);
        printf("\n\tPoint Type: %s", map->points[i].pointType);
        if (map->points[i].pointType == INTEREST) printf("\n\tTitle: %s", map->points[i].title);
        printf("\n\tConnection number: %d", map->points[i].connectionN);
        for (int j = 0; j < map->points[i].connectionN; j++) {
            printf("\n\t\tConnected to point ID: %d", map->points[i].connections[j].id);
        }
    }
}



#include "general.h"
#include "JSON-C/json.h"
#include "maps.h"


MAP* loadMap() { // This function loads the map using the other functions bellow
    MAP* map = (MAP*)malloc(sizeof(MAP));
    char* filename = mapFileName();
    char* unparsedJson = readJSON(filename);
    map = parseJSON(unparsedJson);
    //printMap(map);
    //getchar();
    return map;
}

char* mapFileName() { // Opens a dialog box to select a file and returns its name along with its path.
    int i = 0, count = 0, counterZeros = 0;
    char* izenArtx = (char*)malloc(sizeof(char) * 128);
    char* unlucky = (char*)malloc(sizeof(char) * 128);
    strcpy(unlucky, "Arre.json");
    CHAR* filename = ChooseProgram();
    if (filename == 1) return unlucky;
    while (counterZeros < 3) {
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

CHAR* ChooseProgram() { // Uses windows.h function GetOpenFileName to open a dialog box and let the user select a file.
    OPENFILENAME  ofn;
    CHAR filename[MAX_PATH];
    cutre(filename);
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.hInstance = NULL;
    ofn.lpstrFilter = L"JSON files\0*.json\0\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = L"Aukeratu mapa";
    ofn.Flags = OFN_NONETWORKBUTTON | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    if (!GetOpenFileName(&ofn)) {
        printf("%lu", CommDlgExtendedError());
        return 1;
    }
    else return filename;
}

void cutre(CHAR* filename) {
    filename[0] = 'S';
    filename[1] = 'e';
    filename[2] = 'l';
    filename[3] = 'e';
    filename[4] = 'c';
    filename[5] = 'c';
    filename[6] = 'i';
    filename[7] = 'o';
    filename[8] = 'n';
    filename[9] = 'a';
    filename[10] = 'r';
    filename[11] = ' ';
    filename[12] = 'A';
    filename[13] = 'r';
    filename[14] = 'c';
    filename[15] = 'h';
    filename[16] = 'i';
    filename[17] = 'v';
    filename[18] = 'o';
    filename[19] = '\0';
}

char* readJSON(char* FileName) { // Opens the file specified on filename, reads it and returns its value in a char buffer;
    char* buffer = (char*)malloc(sizeof(char) * 65536);
    FILE* fileJSON = fopen(FileName, "r");
    fread(buffer, sizeof(char), 65536, fileJSON);
    fclose(fileJSON);
    return buffer;
}

void printMap(MAP* map) { // DEBUGGING // Prints the content of a MAP struct
    printf("\nName: %s", map->mapName);
    printf("\nPoint Amounts: %d", map->nodePointAmount);
    for (int i = 0; i < map->nodePointAmount; i++) {
        printf("\n\tID: %d", map->points[i].id);
        if (map->points[i].pointType == CROSSWALK) printf("\n\tPoint Type: Crosswalk");
        if (map->points[i].pointType == INTEREST) {
            printf("\n\tPoint Type: Interest");
            printf("\n\tTitle: %s", map->points[i].title);
        }
        else printf("\n\tPoint Type: Node");
        printf("\n\tConnection number: %d", map->points[i].connectionN);
        for (int j = 0; j < map->points[i].connectionN; j++) {
            printf("\n\t\tConnected to point ID: %d", map->points[i].connections[j].id);
        }
    }
}

MAP* parseJSON(char* buffer) { // Parses a JSON buffer into usefull structs

    MAP* map = (MAP*)malloc(sizeof(MAP));

    struct json_object* parsedJson, * mapName, * IMGPath, * points, * point;
    struct json_object* pointType, * title, * x, * y, * id, * connections, * connection;

    parsedJson = json_tokener_parse(buffer);

    json_object_object_get_ex(parsedJson, "mapName", &mapName);
    strcpy(map->mapName, json_object_get_string(mapName));

    json_object_object_get_ex(parsedJson, "IMGPath", &IMGPath);
    strcpy(map->IMGPath, json_object_get_string(IMGPath));


    json_object_object_get_ex(parsedJson, "points", &points);
    map->nodePointAmount = (int)json_object_array_length(points);


    for (int i = 0; i < map->nodePointAmount; i++) {
        point = json_object_array_get_idx(points, i);

        json_object_object_get_ex(point, "pointType", &pointType);
        if (strcmp(json_object_get_string(pointType), "Interest") == 0) map->points[i].pointType = INTEREST;
        else if (strcmp(json_object_get_string(pointType), "Crosswalk") == 0) map->points[i].pointType = CROSSWALK;
        else map->points[i].pointType = NODE;

        if (strcmp(json_object_get_string(pointType), "Interest") == 0) {
            json_object_object_get_ex(point, "title", &title);
            strcpy(map->points[i].title, json_object_get_string(title));
        }
        else strcpy(map->points[i].title, "\0");

        json_object_object_get_ex(point, "x", &x);
        map->points[i].x = json_object_get_int(x);

        json_object_object_get_ex(point, "y", &y);
        map->points[i].y = json_object_get_int(y);

        json_object_object_get_ex(point, "id", &id);
        map->points[i].id = json_object_get_int(id);

        json_object_object_get_ex(point, "connections", &connections);
        map->points[i].connectionN = (int)json_object_array_length(connections);


        for (int j = 0; j < map->points[i].connectionN; j++) {
            connection = json_object_array_get_idx(connections, j);

            json_object_object_get_ex(connection, "id", &id);
            map->points[i].connections[j].id = json_object_get_int(id);
        }
    }
    return map;
}

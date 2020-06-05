#include "general.h"
#include "JSON-C/json.h"
#include "loadJSON.h"

MAP* loadMap() {
	MAP* map = (MAP*)malloc(sizeof(MAP));
	char* filename = mapFileName();
	char* unparsedJson = readJSON(filename);
	map = parseJSON(unparsedJson);
	//printMap(map);
	//getchar();
	return map;
}

char* mapFileName() {
	int i = 0, count = 0, counterZeros = 0;
	char* izenArtx = (char*)malloc(sizeof(char) * 128);
	CHAR* filename = NULL;
	filename = ChooseProgram();
	while (filename == '\0') {
		printf("\nNo selesionaste un archivo kabron...");
		filename = ChooseProgram();
	}
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

CHAR* ChooseProgram() {
	OPENFILENAME  ofn;
	CHAR *filename = (CHAR*)malloc(sizeof(CHAR) * MAX_PATH);
	defName(filename);
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = L"JSON files\0*.json\0\0";
	ofn.lpstrFile = (LPWSTR)filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = L"Aukeratu mapa";
	ofn.Flags = OFN_NONETWORKBUTTON | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	if (!GetOpenFileName(&ofn)) {
		printf("%lu", CommDlgExtendedError());
		return '\0';
	}
	else return filename;
}

char* readJSON(char* FileName) {
	char* buffer = (char*)malloc(sizeof(char) * 65536);
	FILE* fileJSON = fopen(FileName, "r");
	if (fileJSON == NULL) return '\0';
	fread(buffer, sizeof(char), 65536, fileJSON);
	fclose(fileJSON);
	return buffer;
}

void printMap(MAP* map) {
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

MAP* parseJSON(char* buffer) {

	MAP* map = (MAP*)malloc(sizeof(MAP));

	char aux[MAX_STR];

	struct json_object* parsedJson, * mapName, * IMGPath, * points, * point;
	struct json_object* pointType, * title, * x, * y, * id, * connections, * connection;

	parsedJson = json_tokener_parse(buffer);

	json_object_object_get_ex(parsedJson, "mapName", &mapName);
	strcpy(aux, json_object_get_string(mapName));
	map->mapName = (char*)malloc(sizeof(aux));
	strcpy(map->mapName, aux);

	json_object_object_get_ex(parsedJson, "IMGPath", &IMGPath);
	strcpy(aux, json_object_get_string(IMGPath));
	map->IMGPath = (char*)malloc(sizeof(aux));
	strcpy(map->IMGPath, aux);


	json_object_object_get_ex(parsedJson, "points", &points);
	map->nodePointAmount = (int)json_object_array_length(points);

	map->points = (NODEPOINT*)malloc(sizeof(NODEPOINT) * map->nodePointAmount);

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

		map->points[i].connections = (CONN*)malloc(sizeof(CONN) * map->points[i].connectionN);


		for (int j = 0; j < map->points[i].connectionN; j++) {
			connection = json_object_array_get_idx(connections, j);

			json_object_object_get_ex(connection, "id", &id);
			map->points[i].connections[j].id = json_object_get_int(id);
		}
	}
	return map;
}

void defName(CHAR* filename) {
	int i = 0, j = 0;
	char* filenameChar = "Seleccionar archivo";
	for (j = 0; j < (int)sizeof("Seleccionar archivo"); i++, j++) {
		filename[i] = filenameChar[j];
		filename[i + 1] = '\0';
		i++;
	}
	filename[i] = '\0';
}

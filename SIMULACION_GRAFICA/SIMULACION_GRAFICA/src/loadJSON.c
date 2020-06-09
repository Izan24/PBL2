#include "general.h"

#ifndef LINUX_SISTEMA
#include "JSON-C/json.h"
#endif // !LINUX_SISTEMA

#ifdef LINUX_SISTEMA
#include "tiny-json.h"
#endif // LINUX_SISTEMA

#include "loadJSON.h"



#ifndef LINUX_SISTEMA

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

#endif // WINDOWS_SISTEMA

#ifdef LINUX_SISTEMA

MAP* loadMap() {
	MAP* map = (MAP*)malloc(sizeof(MAP));
	char aux[128];
	int n;
	printf("Mete un numero del 0 al 2 para elegir mapa:\n");
	printf("0. Mutriku\n");
	printf("1. Arre\n");
	printf("2. Getaria\n");
	fgets(aux, 128, stdin);
	sscanf(aux, "%d", &n);
	char* filename = mapFileName(n);
	char* unparsedJson = readJSON(filename);
	map = parseJSON(unparsedJson);
	return map;
}


char* mapFileName(int n) {

	char* aux = (char*)malloc(sizeof(char) * 128);

	char names[5][128] = { "./maps/Mutriku.json", "./maps/Arre.json", "./maps/Getaria.json" };

	if (n == 0 || n == 1 || n == 2)
	{
		strcpy(aux, names[n]);
		return aux;
	}
	else
	{
		strcpy(aux, names[0]);
		return aux;
	}
}

char* readJSON(char* FileName) {
	char* buffer = (char*)malloc(sizeof(char) * 65536);
	FILE* fileJSON = fopen(FileName, "r");
	if (fileJSON == NULL) return '\0';
	fread(buffer, sizeof(char), 65536, fileJSON);
	fclose(fileJSON);
	return buffer;
}

MAP* parseJSON(char* buffer) {

	MAP* map = (MAP*)malloc(sizeof(MAP));
	//json_t *pool = (json_t*)malloc(sizeof(json_t)*3000);
	json_t pool[3000];
	char aux[MAX_STR];

	json_t const* parsedJson = json_create(buffer, pool, 3000);

	json_t const* mapNameField = json_getProperty(parsedJson, "mapName");
	strcpy(aux, json_getValue(mapNameField));
	map->mapName = (char*)malloc(sizeof(aux));
	strcpy(map->mapName, aux);


	json_t const* IMGPathField = json_getProperty(parsedJson, "IMGPath");
	strcpy(aux, json_getValue(IMGPathField));
	map->IMGPath = (char*)malloc(sizeof(aux));
	strcpy(map->IMGPath, aux);

	json_t const* nodePointAmountField = json_getProperty(parsedJson, "nodePointAmount");

	strcpy(aux, json_getValue(nodePointAmountField));
	sscanf(aux, "%d", &map->nodePointAmount);

	json_t const* pointsField = json_getProperty(parsedJson, "points");

	map->points = (NODEPOINT*)malloc(sizeof(NODEPOINT) * map->nodePointAmount);

	json_t const* point = json_getChild(pointsField);

	json_t const* pointTypeField;
	json_t const* titleField;
	json_t const* xField;
	json_t const* yField;
	json_t const* idField;
	json_t const* connectionNField;
	json_t const* connectionsField;
	json_t const* connectionIdField;
	json_t const* connectionField;

	for (int i = 0; i < map->nodePointAmount; i++) {

		pointTypeField = json_getProperty(point, "pointType");

		connectionsField = json_getProperty(point, "connections");
		connectionField = json_getChild(connectionsField);

		strcpy(aux, json_getValue(pointTypeField));
		if (strcmp(aux, "Interest") == 0) map->points[i].pointType = INTEREST;
		else if (strcmp(aux, "Crosswalk") == 0) map->points[i].pointType = CROSSWALK;
		else map->points[i].pointType = NODE;

		if (strcmp(aux, "Interest") == 0) {
			titleField = json_getProperty(point, "title");
			strcpy(map->points[i].title, json_getValue(titleField));

		}
		else strcpy(map->points[i].title, "\0");

		xField = json_getProperty(point, "x");
		strcpy(aux, json_getValue(xField));
		sscanf(aux, "%d", &map->points[i].x);

		yField = json_getProperty(point, "y");
		strcpy(aux, json_getValue(yField));
		sscanf(aux, "%d", &map->points[i].y);

		idField = json_getProperty(point, "id");
		strcpy(aux, json_getValue(idField));
		sscanf(aux, "%d", &map->points[i].id);

		connectionNField = json_getProperty(point, "connectionN");
		strcpy(aux, json_getValue(connectionNField));
		sscanf(aux, "%d", &map->points[i].connectionN);
		map->points[i].connections = (CONN*)malloc(sizeof(CONN) * map->points[i].connectionN);

		for (int j = 0; j < map->points[i].connectionN; j++) {

			connectionIdField = json_getProperty(connectionField, "id");
			strcpy(aux, json_getValue(connectionIdField));
			sscanf(aux, "%d", &map->points[i].connections[j].id);

			if (map->points[i].connectionN != j + 1) {
				connectionField = json_getSibling(connectionField);
			}
		}

		if (map->nodePointAmount != i + 1) point = json_getSibling(point);
	}
	return map;
}
#endif // LINUX_SISTEMA


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
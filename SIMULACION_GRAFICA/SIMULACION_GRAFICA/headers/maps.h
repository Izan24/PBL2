#ifndef MAPS_H
#define MAPS_H


struct connection {
	int id; // the Id of the point which is connected to.
	float cost; // the cost of the connection.
};

typedef struct node { // Normal points
	TYPE pointType; // True == crosswalk, False == Not crosswalk.
	char title[MAX_STR];
	int x; // x coord.
	int y; // y coord.
	int id;
	int connectionN;
	struct connection connections[MAX_CONNECTIONS];
}NODEPOINT, * PNODEPOINT;


typedef struct map {
	char IMGPath[MAX_PATH]; // The location of the IMG on the PC.
	char mapName[MAX_STR]; // The nanme of the file that we are using.
	NODEPOINT points[300]; // All the coordinates of the points.
	int nodePointAmount; // Points that are connected int he map->
}MAP;

MAP* loadMap();
char* mapFileName();
CHAR* ChooseProgram();
char* readJSON(char* FileName);
void printMap(MAP* map);
MAP* parseJSON(char* buffer);



#endif // !MAPS_H

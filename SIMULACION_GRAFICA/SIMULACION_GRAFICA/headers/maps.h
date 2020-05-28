#ifndef MAPS_H
#define MAPS_H


typedef struct line {
	int x0; // First point of the line (x axis)
	int x1; // Second point of the line (x axis)
	int y0; // First point of the line (y axis)
	int y1; // Second point of the line (y axis)
	float cost; // The cost of moving through this line
}LINE;

struct connection {
	int id; // the Id of the point which is connected to.
	float cost; // The cost o the conection
	LINE lineTo;
};

typedef struct node { // Normal points
	TYPE pointType; // The type of the point, can be NODE (0), CROSSWALK (1) or INTEREST (2)
	char title[MAX_STR];
	int x; // x coord.
	int y; // y coord.
	int id; // Identification number of the node
	int connectionN; // Number of connections the node has
	struct connection connections[MAX_CONNECTIONS]; //Array of all the connections
	int distanceFromEnd; //The distance from the end point.
}NODEPOINT, * PNODEPOINT;


typedef struct map {
	char IMGPath[MAX_PATH]; // The location of the IMG on the PC.
	char mapName[MAX_STR]; // The nanme of the file that we are using.
	NODEPOINT points[MAX_NODE]; // All the coordinates of the points.
	int nodePointAmount; // Points that are connected int he map->
}MAP;

MAP* loadMap();
char* mapFileName();
CHAR* ChooseProgram();
char* readJSON(char* FileName);
void printMap(MAP* map);
MAP* parseJSON(char* buffer);
void cutre(CHAR* filename);



#endif // !MAPS_H

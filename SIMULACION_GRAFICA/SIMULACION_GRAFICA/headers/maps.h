#ifndef MAPS_H
#define MAPS_H

/*
Simple lines with the coordinates in X and Y axis as well as the cost (distance) of the line.
*/
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


/*
Nodepoints.
They consist of a point type, witch can be NODE (0), CROSSWALK (1) or INTEREST (2).
The title of the point in case the node is an Interest point.
The coordinates of the point on the X and Y axis.
The identification number of the point.
The amount of connections the point has and all the connections.
The distance from the selected END point to the current point.
*/
typedef struct node {
	TYPE pointType; // The type of the point, can be NODE (0), CROSSWALK (1) or INTEREST (2)
	char title[MAX_STR];
	int x; // x coord.
	int y; // y coord.
	int id; // Identification number of the node
	int connectionN; // Number of connections the node has
	struct connection connections[MAX_CONNECTIONS]; //Array of all the connections
	int distanceFromEnd; //The distance from the end point.
}NODEPOINT, * PNODEPOINT;


/*
The whole map structure.
Includes the path to the background image, the name of the map, all the points and the amount of the points.
*/
typedef struct map {
	char IMGPath[MAX_PATH]; // The location of the IMG on the PC.
	char mapName[MAX_STR]; // The nanme of the file that we are using.
	NODEPOINT points[MAX_NODE]; // All the coordinates of the points.
	int nodePointAmount; // Points that are connected int he map->
}MAP;

// This function loads the map using the other functions bellow.
MAP* loadMap();

// Opens a dialog box to select a file and returns its name along with its path.
char* mapFileName();

// Uses windows.h function GetOpenFileName to open a dialog box and let the user select a file.
CHAR* ChooseProgram();

// Opens the file specified on filename, reads it and returns its value in a char buffer.
char* readJSON(char* FileName);

// DEBUGGING   Prints the content of a MAP struct.
void printMap(MAP* map);

// Parses a JSON buffer into useful structs.
MAP* parseJSON(char* buffer);

//Sets the default name for the search bar.
void defName(CHAR* filename);



#endif // !MAPS_H

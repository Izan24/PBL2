#include "general.h"
#include "maps.h"

int main() {

	printf("%s", mapFileName());
}

struct connection {
	int id; // the Id of the point which is connected to.
	float cost; // the cost of the connection.
};

typedef struct nde{ // Normal points
	TYPE pointType; // True == crosswalk, False == Not crosswalk.
	char title[MAX_STR];
	int x; // x coord.
	int y; // y coord.
	int id;
	int connectionN;
	struct connection connections[MAX_CONNECTIONS];
}NODEPOINT, *PNODEPOINT;


typedef struct map {
	char IMGPath[MAX_PATH]; // The location of the IMG on the PC.
	char mapName[MAX_STR]; // The nanme of the file that we are using.
	POINT points[300]; // All the coordinates of the points.
	int nodePointAmount; // Points that are connected int he map.
}MAP;


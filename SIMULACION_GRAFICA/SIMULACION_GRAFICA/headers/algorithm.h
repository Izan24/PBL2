#ifndef ALGORITHM_H
#define ALGORITHM_H





typedef struct Astar{
    int current; // The point we currently are
    int from; // ID of the point you came from
    int cost; // The total cost for reaching this point
    int distance; // the distance from the start to this point
    int total; // cost + distance
}ASTAR;

typedef struct aNode {
    ASTAR astar;
    struct aNode * ptrAstar; // Pointer to the next item of the list
}ANODE;


ANODE* execAlgorithm(MAP* map, NODEPOINT* startP, NODEPOINT* endP); // Executes the A* algorithm and prints the shortest path. Returns the final list with the path

int getCost(NODEPOINT p1, NODEPOINT p2); // Gets the cost between 2 points
void getAllCost(MAP* map); // Gets all the cost of the hole the map
int distancePointToPoint(NODEPOINT startP, NODEPOINT endP); // Returns the distance between 2 points
void getAllDistances(MAP* map, NODEPOINT p); // Gets all the distances of all the points to the start point
ANODE* aStar(MAP* map, NODEPOINT* startP, NODEPOINT* endP);// makes all the A* algorithm
int findPInList(ANODE* list, ASTAR p); // Returns 1 if it finds the id on the list.
ANODE* returnANodePointer(ANODE* mainList, ASTAR currentPoint); // Returns the pointer to the currentPoint in the mainlist
void insertInList(ANODE** listen, ASTAR insertion); // Inserts the structure in the HEAD of the list
ASTAR searchTheLowestPoint(ANODE* mainList); // Searches and returns the point with the lowest TOTAL cost in the list
ANODE* returnPathAnode(ANODE* endList, int startId, int endId);
void insertInHead(ANODE** printList, ASTAR point);
void deleteFromList(ANODE** list, ASTAR deleteItem);
ANODE* previousItem(ANODE* list, ASTAR deleteitem);
void setPoint(MAP* map, ASTAR* currentPoint, ASTAR* nextPoint, int i);
void setPointDijkstra(MAP* map, ASTAR* currentPoint, ASTAR* nextPoint, int i);
ANODE* dijstra(MAP* map, LINE* lines, NODEPOINT* startP, NODEPOINT* endP);

#endif // !ALGORITHM_H

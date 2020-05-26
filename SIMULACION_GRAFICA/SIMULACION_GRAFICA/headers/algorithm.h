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


int getLines(LINE* lines, MAP* map); // It calculates all the lines of the map
int getCost(NODEPOINT p1, NODEPOINT p2); // Gets the cost between 2 points
void getAllCost(MAP* map); // Gets all the cost of the hole the map
int distancePointToPoint(NODEPOINT startP, NODEPOINT endP); // Returns the distance between 2 points
void getAllDistances(MAP* map, NODEPOINT p); // Gets all the distances of all the points to the start point
ANODE* aStar(MAP* map, LINE* lines, NODEPOINT* startP, NODEPOINT* endP); // makes all the A* algorithm
int findPInList(ANODE* list, ASTAR p); // Returns 1 if it finds the id on the list.
ANODE* returnANodePointer(ANODE* mainList, ASTAR currentPoint);
void insertInList(ANODE** listen, ASTAR insertion);
ASTAR searchTheLowestPoint(ANODE* mainList);
void execAlgorithm(MAP* map, LINE* lines, NODEPOINT* startP, NODEPOINT* endP);
ANODE* returnPathAnode(ANODE* endList, int startId, int endId);
void insertInHead(ANODE** printList, ASTAR point);
void drawPath(ANODE* printList, MAP* map);
void deleteFromList(ANODE** list, ASTAR deleteItem);
ANODE* previousItem(ANODE* list, ASTAR deleteitem);

#endif // !ALGORITHM_H

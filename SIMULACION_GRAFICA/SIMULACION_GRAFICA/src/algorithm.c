#include "general.h"
#include "algorithm.h"

void execAlgorithm(MAP* map, LINE* lines, NODEPOINT* startP, NODEPOINT* endP) {
    ANODE* endList = aStar(map, lines, startP, endP);
    ANODE* printList = returnPathAnode(endList, startP->id, endP->id);
    drawPath(printList, map);
}

int getLines(LINE* lines, MAP* map) {
    int count = 0, tmpX0, tmpY0, tmpX1, tmpY1, ordTmp;
    LINE tmpLine;
    for (int i = 0; i < map->nodePointAmount; i++) // Iterates every single point
    {
        tmpX0 = map->points[i].x;
        tmpY0 = map->points[i].y;
        for (int j = 0; j < map->points[i].connectionN; j++) // Iterates every connection of every point
        {
            tmpX1 = map->points[map->points[i].connections[j].id].x;
            tmpY1 = map->points[map->points[i].connections[j].id].y;
            tmpLine.x0 = tmpX0;
            tmpLine.y0 = tmpY0;
            tmpLine.x1 = tmpX1;
            tmpLine.y1 = tmpY1;

            if ((tmpLine.x0 != tmpLine.x1) || (tmpLine.y0 != tmpLine.y1))
            {
                if (map->points[i].id < map->points[map->points[i].connections[j].id].id) // Check that the ID of the current point isn't > than the point that we want to connect to because we have already drawn that line.
                {
                    lines[count] = tmpLine;
                    count++;
                }
            }
        }
    }
    return count;
}

int getCost(NODEPOINT p1, NODEPOINT p2) {
    int distX, distY, sum;
    distX = p1.x - p2.x;
    distY = p1.y - p2.y;

    distX *= distX;
    distY *= distY;

    sum = distX + distY;
    return sqrt(sum);
}

void getAllCost(MAP* map) {

    for (int i = 0; i < map->nodePointAmount; i++) { // Iterates every single point
        for (int j = 0; j < map->points[i].connectionN; j++) { // Iterates every connection of every point
            map->points[i].connections[j].cost = getCost(map->points[i], map->points[map->points[i].connections[j].id]);
        }
    }
}

int distancePointToPoint(NODEPOINT startP, NODEPOINT endP) {
    int distX = startP.x - endP.x;
    int distY = startP.y - endP.y;
    int dist;
    int sum;

    distX *= distX;
    distY *= distY;

    sum = distX + distY;

    dist = sqrt(sum);

    return dist;
}

void getAllDistances(MAP* map, NODEPOINT p) {
    for (int i = 0; i < map->nodePointAmount; i++) {
        map->points[i].distanceFromEnd = distancePointToPoint(p, map->points[i]);
    }
}

ANODE* aStar(MAP* map, LINE* lines, NODEPOINT* startP, NODEPOINT* endP)
{
    int startId = startP->id;
    int endId = endP->id;
    int n = 0;

    ASTAR currentPoint;
    ASTAR nextPoint;
    ASTAR endPoint;

    ANODE* mainList = (ANODE*)malloc(sizeof(ANODE));
    ANODE* endList = NULL;
    ANODE* aux = NULL;

    getAllDistances(map, *endP);

    currentPoint.current = startP->id;
    currentPoint.from = startP->id;
    currentPoint.cost = 0;
    currentPoint.distance = 0;
    currentPoint.total = 0;

    mainList->astar = currentPoint;
    mainList->ptrAstar = NULL;
    endPoint.current = endP->id;

    while (findPInList(endList, endPoint) == 0)
    {
        for (int i = 0; i < map->points[currentPoint.current].connectionN; i++)
        {
            setPoint(map, &currentPoint, &nextPoint, i);

            if (findPInList(endList, nextPoint) == 0)
            {
                if (findPInList(mainList, nextPoint)) { // If we find it in the main list we check that it's cost is less than the cost of the point that is already in the list.

                    aux = returnANodePointer(mainList, nextPoint);

                    if (aux->astar.total > nextPoint.total) //
                    {
                        aux->astar.total = nextPoint.total;
                        aux->astar.from = nextPoint.from;
                    }
                }
                else { // If we dont find it in the list we insert the point to the list
                    insertInList(&mainList, nextPoint);
                }
            }
        }
        insertInList(&endList, currentPoint); // Update the name from X AE A-12 to X AE A-XII
        deleteFromList(&mainList, currentPoint);
        currentPoint = searchTheLowestPoint(mainList);
    }

    return endList;
}

ANODE* dijstra(MAP* map, LINE* lines, NODEPOINT* startP, NODEPOINT* endP){
    int startId = startP->id;
    int endId = endP->id;
    int n = 0;

    ASTAR currentPoint;
    ASTAR nextPoint;
    ASTAR endPoint;

    ANODE* mainList = (ANODE*)malloc(sizeof(ANODE));
    ANODE* endList = NULL;
    ANODE* aux = NULL;

    getAllDistances(map, *endP);

    currentPoint.current = startP->id;
    currentPoint.from = startP->id;
    currentPoint.cost = 0;
    currentPoint.distance = 0;
    currentPoint.total = 0;

    mainList->astar = currentPoint;
    mainList->ptrAstar = NULL;
    endPoint.current = endP->id;

    while (mainList != NULL)
    {
        for (int i = 0; i < map->points[currentPoint.current].connectionN; i++)
        {
            setPointDijkstra(map, &currentPoint, &nextPoint, i);

            if (findPInList(endList, nextPoint) == 0)
            {
                if (findPInList(mainList, nextPoint)) { // If we find it in the main list we check that it's cost is less than the cost of the point that is already in the list.

                    aux = returnANodePointer(mainList, nextPoint);

                    if (aux->astar.total > nextPoint.total) //
                    {
                        aux->astar.total = nextPoint.total;
                        aux->astar.from = nextPoint.from;
                    }
                }
                else { // If we dont find it in the list we insert the point to the list
                    insertInList(&mainList, nextPoint);
                }
            }
        }
        insertInList(&endList, currentPoint); // Update the name from X AE A-12 to X AE A-XII
        deleteFromList(&mainList, currentPoint);
        if (mainList != NULL) currentPoint = searchTheLowestPoint(mainList);
    }

    return endList;
}

int findPInList(ANODE* list, ASTAR p) {
    int found = 0;
    ANODE* aux = list;

    if (list != NULL)
    {
        while (aux != NULL) {
            if (aux->astar.current == p.current) {
                found = 1;
                break;
            }
            aux = aux->ptrAstar;
        }
    }

    return found;
}

ANODE* returnANodePointer(ANODE* mainList, ASTAR currentPoint) {
    while (mainList != NULL) {
        if (mainList->astar.current == currentPoint.current) {
            return mainList;
        }
        mainList = mainList->ptrAstar;
    }
}

void insertInList(ANODE** listen, ASTAR insertion) // Joseba I wanna dieeeeewsasdfasdfasdfsadf "Izan & Urko"
{
    ANODE* aux = (ANODE*)malloc(sizeof(ANODE));
    aux->astar = insertion;
    aux->ptrAstar = NULL;

    if (*listen == NULL)
    {
        *listen = aux;
    }
    else
    {
        ANODE* aux2 = *listen;
        while (aux2->ptrAstar != NULL) {
            aux2 = aux2->ptrAstar;
        }
        aux2->ptrAstar = aux;
    }
}

ASTAR searchTheLowestPoint(ANODE* mainList) {

    ASTAR lowest = mainList->astar;

    while (mainList != NULL)
    {
        if (mainList->astar.total < lowest.total)
        {
            lowest = mainList->astar;
        }

        mainList = mainList->ptrAstar;
    }
    return lowest;
}

ANODE* returnPathAnode(ANODE* endList, int startId, int endId) {
    ANODE* aux = endList;
    ANODE* printList = NULL;
    while (aux->astar.current != endId) aux = aux->ptrAstar;
    insertInHead(&printList, aux->astar);

    while (printList->astar.current != startId) {
        aux = endList;
        while (printList->astar.from != aux->astar.current) aux = aux->ptrAstar;
        insertInHead(&printList, aux->astar);
    }
    return printList;
}

void insertInHead(ANODE** printList, ASTAR point) {
    if (*printList == NULL) {

        *printList = (ANODE*)malloc(sizeof(ANODE));
        (*printList)->astar = point;
        (*printList)->ptrAstar = NULL;
    }
    else {
        ANODE* aux = (ANODE*)malloc(sizeof(ANODE));
        aux->astar = point;
        aux->ptrAstar = *printList;
        *printList = aux;
    }
}

void drawPath(ANODE* printList, MAP* map) {
    LINE aux;

    while (printList != NULL) {
        aux.x0 = map->points[printList->astar.from].x;
        aux.y0 = map->points[printList->astar.from].y;

        aux.x1 = map->points[printList->astar.current].x;
        aux.y1 = map->points[printList->astar.current].y;

        drawThiccLine(aux);
        SDL_RenderPresent(rend);
        printList = printList->ptrAstar;
    }
}

void deleteFromList(ANODE** list, ASTAR deleteItem)
{
    ANODE* previous;
    ANODE* aux;

    previous = previousItem(*list, deleteItem);

    if (previous != NULL)
    {
        if ((*list)->astar.current == deleteItem.current)
        {
            aux = *list;
            (*list) = (*list)->ptrAstar;

            free(aux);
        }
        else
        {
            aux = previous->ptrAstar;

            previous->ptrAstar = previous->ptrAstar->ptrAstar;

            free(aux);
        }
    }
}

ANODE* previousItem(ANODE* list, ASTAR deleteitem)
{
    ANODE* previous = NULL;

    int found = 0;

    //Si el que quiero borrar es el primero devuelvo el primero
    if (list->astar.current == deleteitem.current)
    {
        previous = &list->astar;
    }
    else
    {
        //Si no es el primero lo busco y devuelvo el anterior al que quiero borrar
        while (found == 0 && list != NULL)
        {
            if (list->ptrAstar->astar.current == deleteitem.current)
            {
                previous = &list->astar;
                found = 1;
            }
            else
            {
                list = list->ptrAstar;
            }
        }

        //en caso de no encontrarlo devuelvo un null para poder poner luego que si ees null diga que el elemento  no esta en la lista
        if (found == 0)
        {
            previous = NULL;
        }
    }

    return(previous);
}


void setPoint(MAP* map, ASTAR* currentPoint, ASTAR* nextPoint, int i) {
    nextPoint->from = currentPoint->current;
    nextPoint->current = map->points[currentPoint->current].connections[i].id;
    nextPoint->cost = currentPoint->cost + getCost(map->points[currentPoint->current], map->points[nextPoint->current]);
    nextPoint->distance = map->points[map->points[currentPoint->current].connections[i].id].distanceFromEnd;
    nextPoint->total = nextPoint->cost + nextPoint->distance;
}

void setPointDijkstra(MAP* map, ASTAR* currentPoint, ASTAR* nextPoint, int i) {
    nextPoint->from = currentPoint->current;
    nextPoint->current = map->points[currentPoint->current].connections[i].id;
    nextPoint->cost = currentPoint->cost + getCost(map->points[currentPoint->current], map->points[nextPoint->current]);
    nextPoint->distance = 0;
    nextPoint->total = nextPoint->cost;
}
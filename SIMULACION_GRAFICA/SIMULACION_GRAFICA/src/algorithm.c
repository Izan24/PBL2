#include "general.h"
#include "algorithm.h"

int getLines(LINE* lines, MAP* map)
{
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
			map->points[i].connections[j].lineTo.x0 = tmpX0;
			map->points[i].connections[j].lineTo.y0 = tmpY0;
			map->points[i].connections[j].lineTo.x1 = tmpX1;
			map->points[i].connections[j].lineTo.y1 = tmpY1;

			if ((tmpLine.x0 != tmpLine.x1) && (tmpLine.y0 != tmpLine.y1))
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


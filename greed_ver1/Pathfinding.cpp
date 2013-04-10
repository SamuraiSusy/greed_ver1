#include "Pathfinding.h"
#include <Layer.h>
#include <Tile.h>
#include <iostream>

using namespace yam2d;
std::string HitboxLayerName = "Hitboxes";

Pathfinding::Pathfinding(TmxMap* Map, int DirectionList)
{

    switch (DirectionList)
    {
    case 0:
        directionsCount = 4;
            direction_x[0] = 0;         direction_y[0] = 1;
            direction_x[1] = 1;         direction_y[1] = 0;
            direction_x[2] = 0;         direction_y[2] = -1;
            direction_x[3] = -1;		direction_y[3] = 0;
        break;
    default:
        directionsCount = 8;
            direction_x[0] = 1;         direction_y[0] = 1;
            direction_x[1] = -1;		direction_y[1] = 1;
            direction_x[2] = -1;		direction_y[2] = -1;
            direction_x[3] = 1;         direction_y[3] = -1;
            direction_x[4] = 0;         direction_y[4] = -1;
            direction_x[5] = 1;         direction_y[5] = 0;
            direction_x[6] = -1;		direction_y[6] = 0;
            direction_x[7] = 0;         direction_y[7] = 1;
    }

    // extend map to every direction by 1 so later can surround map with hitboxes
    map_width = (int)Map->getWidth() + 2; 
    map_height = (int)Map->getHeight() + 2;

	// create map list
    map = new int*[map_width];
    for (int i = 0; i < map_width; i++)
        map[i] = new int[map_height];

	// mark everything free inside map
    for (int i = 1; i < map_width -1; i++)
    {
        for (int j = 1; j < map_height -1; j++)
        {

            map[i][j] = 5;
        }
    }

	// Surround map with Hitboxes
	for (int i = 0; i < map_width; i++)
	{
		map[i][0] = HITBOX;
		map[i][map_height-1] = HITBOX;
	}
	for (int i = 0; i < map_height; i++)
	{
		map[0][i] = HITBOX;
		map[map_width-1][i] = HITBOX;
	}

	// get Hitboxes from map
    if (Map->getLayer(HitboxLayerName))
    {
        for (unsigned int i = 0; i < Map->getLayer(HitboxLayerName)->getGameObjects().size() ; i++)
        {
            int x = (int)Map->getLayer(HitboxLayerName)->getGameObjects()[i]->getPosition().x;
            int y = (int)Map->getLayer(HitboxLayerName)->getGameObjects()[i]->getPosition().y;
            map[x+1][y+1] = HITBOX;
        }
    }
    else
    {
        std::cout<< "Error loading hitboxes to Pathfinder, map does not contain layer called " << HitboxLayerName << std::endl;
    }

    maxDistance = map_width * map_height / 2 + map_width + map_height;

    int stepLimit = map_width * 4 + map_height * 4;

    stepList = new int**[2];
        
    for (int i = 0; i < 2; i++)
    {
        stepList[i] = new int*[stepLimit];
        for (int j = 0; j < stepLimit; j++)
        {
            stepList[i][j] = new int[2];
            for (int k = 0; k < 2; k++)
                stepList[i][j][k] = 0;
        }
    }
    
	resetMap();
}


Pathfinding::~Pathfinding()
{
    for (int i = 0; i < map_width; i++)
            delete[] map[i];
    delete[] map;

    // Multidimensional dynamic arrays are the best
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < sizeof(stepList[i]); j++)
        {
                delete[] stepList[i][j];
        }
        delete[] stepList[i];
    }
    delete[] stepList;
}

std::vector<vec2> Pathfinding::GetPath()
{
	return Path;
}

bool Pathfinding::FindPathYam2D(float Start_X, float Start_Y, float Goal_X, float Goal_Y, float ObjectSizeInTiles)
{
	objectSizeInTiles = ceil(abs(ObjectSizeInTiles));

	coordinateDifference = 1.500001f - ObjectSizeInTiles / 2.0f;
	
	Start_X += coordinateDifference + 0.5f;
	Start_Y += coordinateDifference + 0.5f;
	Goal_X	+= coordinateDifference + 0.5f;
	Goal_Y	+= coordinateDifference + 0.5f;

    return FindPath((int)(Start_X), (int)(Start_Y), (int)(Goal_X), (int)(Goal_Y));
}

// Private

void Pathfinding::StartPath()
{
    Goal_Found = false;

    resetMap();

    current = 0;
    Checked_Steps = 0;
    Steps_Searched = 0;
}

bool Pathfinding::FindPath(int Start_X, int Start_Y, int Goal_X, int Goal_Y)
{
    StartPath();
	
	int USEDHITBOX = HITBOX - 1 + objectSizeInTiles;

    if (Start_X <= 0 ||
        Start_X >= map_width ||
        Start_Y <= 0 ||
        Start_Y >= map_height) return false;

    if (Goal_X <= 0 ||
        Goal_X >= map_width ||
        Goal_Y <= 0 ||
        Goal_Y >= map_height) return false;
        
    if (Goal_X == Start_X && Goal_Y == Start_Y) return false;

        
    if (map[Goal_X][Goal_Y] == HITBOX) return false;
    else if (map[Start_X][Start_Y] == HITBOX) return false;

        

    map[Start_X][Start_Y] = START;
    stepList[current][0][0] = Start_X;
    stepList[current][0][1] = Start_Y;
    stepsCount[current] = 1;
    stepsCount[1] = 0;


    while (Steps_Searched < maxDistance && !Goal_Found && stepsCount[current] > 0)
    {
        for (int step = 0; step < stepsCount[current]; step++)
        {
            for (a = 0; a < directionsCount; a++)
            {
                x = stepList[current][step][0] + direction_x[a];
                y = stepList[current][step][1] + direction_y[a]; 
                if (USEDHITBOX < map[x][y] && map[x][y] < LIMIT)
                {       
                    stepList[1 - current][stepsCount[1 - current]][0] = x;
                    stepList[1 - current][stepsCount[1 - current]][1] = y;
                    stepsCount[1 - current]++;

                    if (Goal_X == x && Goal_Y == y)
						Goal_Found = true;

                    map[x][y] = Steps_Searched;
                    Checked_Steps++;
                }
            }
        }

        current = 1 - current;
        stepsCount[1 - current] = 0;

        Steps_Searched++;
    }

    if (Goal_Found)
    {
        Path.clear();
        Path.resize(Steps_Searched);

        Path[Steps_Searched - 1] = vec2((float)Goal_X,(float)Goal_Y);
        for (int a = Steps_Searched - 1; a > 0; a--)
        {
            for (int b = 0; b < directionsCount; b++)
            {
                if (map
                    [(int)Path[a].x + direction_x[b]]
                    [(int)Path[a].y + direction_y[b]]
                        == a - 1)
                {
                    Path[a - 1] = vec2(
                        Path[a].x + direction_x[b],
                        Path[a].y + direction_y[b]);
                }
			}
        }
		for (int i = 0; i < Path.size(); i++)
			Path[i] -= vec2(coordinateDifference);
        return true;
    }

    return false;
}


void Pathfinding::resetMap()
{
	// go through the map exept the added hitboxes
	for (int x = map_width - 2; x > 0; x--)
    {
        for (int y = map_height - 2; y > 0; y--)
        {
            if (map[x][y] > LIMIT) // if tile is not already Hitbox
			{
                map[x][y] = map[x+1][y+1] +1; // get value from right
				
				if (map[x][y] > map[x][y+1] +1) // if value smaller than below -> distance from hitbox to tile below is smaller
					map[x][y] = map[x][y+1] +1; // get that value +1

				if (map[x][y] > map[x+1][y] +1) // if value smaller than on right -> distance from hitbox to tile below is smaller
					map[x][y] = map[x+1][y] +1; // get that value +1
			}
        }
    }
}
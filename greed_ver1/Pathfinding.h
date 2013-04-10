#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <Map.h>
#include <string>


class Pathfinding
{
public:
        Pathfinding(yam2d::TmxMap* Map, int DirectionList = 1);
        ~Pathfinding();

        std::vector<yam2d::vec2> GetPath();

        bool FindPathYam2D(float Start_X, float Start_Y, float Goal_X, float Goal_Y, float ObjectSizeInTiles = 1.0f);

private:

        void StartPath();

        bool FindPath(int Start_X, int Start_Y, int Goal_X, int Goal_Y);

		void resetMap();

        int** map;

        int*** stepList;
        int stepsCount[2];
        int current;

        int map_height;
        int map_width;

        int directionsCount;
        int direction_x[8];
        int direction_y[8];

        static const int START = 0;
		static const int LIMIT = -1;
        static const int HITBOX = -10000; // only works on maps smaller than 10 000 tiles wide or high

        int maxDistance;

		float coordinateDifference;

        bool Goal_Found;

        int x;
        int y;
        int a;
        int b;

        int Steps_Searched;
        int Checked_Steps;

        std::vector<yam2d::vec2> Path;

		int objectSizeInTiles;

};

#endif
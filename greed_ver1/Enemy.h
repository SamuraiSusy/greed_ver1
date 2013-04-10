#ifndef ENEMY_H
#define ENEMY_H

#include "HitCheck.h"
#include <AnimatedSpriteGameObject.h>
#include <Input.h>
#include "Pathfinding.h"

using namespace yam2d;

class Enemy : public AnimatedSpriteGameObject
{
public:
	Enemy(int gameObjectType, SpriteSheet* sprite, HitCheck* HitChecker, TmxMap* Map, Pathfinding* Pathfinder);
	virtual ~Enemy(void);
	void setTarget(vec2 goal); 
	virtual void update(float deltaTime);
private:
	vec2 goal;
	vec2 direction;
	vec2 destination;
	HitCheck* hitboxCheck;
	TmxMap* map;
	Pathfinding* pathfinder;
	std::vector<vec2> path;
};

#endif
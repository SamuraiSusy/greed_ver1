#ifndef ENEMY_H
#define ENEMY_H

#include "HitCheck.h"
#include <AnimatedSpriteGameObject.h>
#include <Input.h>

using namespace yam2d;

class Enemy : public AnimatedSpriteGameObject
{
public:
	Enemy(int gameObjectType, SpriteSheet* sprite, HitCheck* HitChecker, TmxMap* Map);
	virtual ~Enemy(void);
	void setTarget(vec2 destination); 
	virtual void update( float deltaTime );
private:
	vec2 direction;
	vec2 destination;
	HitCheck* hitboxCheck;
	TmxMap* map;
};

#endif
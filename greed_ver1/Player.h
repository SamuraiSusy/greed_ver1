#ifndef PLAYER_H
#define PLAYER_H

#include "HitCheck.h"
#include <AnimatedSpriteGameObject.h>
#include <Input.h>

using namespace yam2d;

class Player : public AnimatedSpriteGameObject
{
public:
	Player(int gameObjectType, SpriteSheet* sprite, HitCheck* HitChecker, TmxMap* Map);
	virtual ~Player(void);

	virtual void update( float deltaTime );


private:
	vec2 direction;
	vec2 destination;
	HitCheck* hitboxCheck;
	TmxMap* map;
};

#endif
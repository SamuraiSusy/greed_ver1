#ifndef FISH_H
#define FISH_H
#include <SpriteGameObject.h>
#include <Input.h>
#include "HitCheck.h"
#include "Player.h"

using namespace yam2d;

class Fish : public AnimatedSpriteGameObject
{
public:
	Fish(int gameObjectType, SpriteSheet* spriteSheet, Player* player, HitCheck* hitboxCheck);
	~Fish(void);

	void update(float deltaTime);

private:
	Player* player;
	HitCheck* hitboxCheck;
};


#endif
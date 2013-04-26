#ifndef FISH_H
#define FISH_H
#include <SpriteGameObject.h>
#include <Input.h>
#include "HitCheck.h"
#include "Player.h"

using namespace yam2d;

class Fish : public SpriteGameObject
{
public:
	Fish(int gameObjectType, Texture* texture, Player* player, HitCheck* hitboxCheck);
	~Fish(void);

	void update(float deltaTime);

	bool isGameFinished();

private:
	Player* player;
	HitCheck* hitboxCheck;
	bool finishedGame;
};


#endif
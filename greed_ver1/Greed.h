#ifndef GREED_H
#define GREED_H

#include <es_util.h>
#include <Map.h>
#include <Layer.h>
#include <Tile.h>
#include <Camera.h>
#include "Player.h"
#include "Enemy.h"
#include "HitCheck.h"

using namespace yam2d;

//class Player;

class Greed
{
public:
	Greed();
	~Greed();
	void Update(float DeltaTime);
	void Draw(ESContext *esContext);
private:
	SpriteBatchGroup* batch;
	TmxMap* map;
	Player* player;
	std::vector<Enemy*> enemies;
	HitCheck* HitChecker;
	Texture* enemyTexture;
	SpriteSheet* enemySprite;
};

#endif GREED_H

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
#include "Pathfinding.h"
#include "Fish.h"

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
	Fish* fish;
	
	SpriteGameObject* endscreen;
	Texture* fishTexture;
	SpriteSheet* fishSprite;
	std::vector<Enemy*>* enemies; // jos haluaa tehdä monta
	HitCheck* HitChecker;
	Texture* enemyTexture;
	SpriteSheet* enemySprite;
	Pathfinding* pathfinding;
};

#endif GREED_H

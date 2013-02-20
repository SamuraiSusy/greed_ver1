#ifndef HITCHECK_H
#define HITCHECK_H

#include <Map.h>
#include <Layer.h>
#include <Tile.h>
#include <GameObject.h>

using namespace yam2d;

class HitCheck
{
public:
	HitCheck(TmxMap* map);
	~HitCheck(void);
	vec2 CheckMapHit(GameObject *character);
	//vec2 CheckHit(GameObject* LightObject, GameObject* HeavyObject, vec2 Direction);
private:
	Layer::GameObjectList mapHitboxes;

	void distanceToBorder(GameObject *hitbox, GameObject *character, vec2 *whereToMove);
};

#endif

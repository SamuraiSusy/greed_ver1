#ifndef FISH_H
#define FISH_H
#include <SpriteGameObject.h>

using namespace yam2d;

class Fish : public SpriteGameObject
{
public:
	Fish(int gameObjectType, Texture* texture);
	~Fish(void);

	void update(float deltaTime);
};


#endif
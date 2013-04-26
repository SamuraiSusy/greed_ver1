#include "Fish.h"
#include "HitCheck.h"
#include <iostream>
#include <es_util.h>
#include <SpriteBatch.h>


// Fish ei tarvitse hitboxia eikä mappia, koska se ei liiku
Fish::Fish(int gameObjectType, Texture* texture, Player* player, HitCheck* hitboxCheck)
	: SpriteGameObject(gameObjectType, texture)  // cpp- ja h-filussa pitää olla samat muuttujat (cpp public)
{
	this->player = player; // pitää käyttää thisnuolihommaa, koska Player*player on sama h- ja cpp-filuissa
	setPosition(vec2(52,21));
	finishedGame = false;

	this->hitboxCheck = hitboxCheck;
}


Fish::~Fish(void)
{
}

void Fish::update(float deltaTime)
{
	GameObject::update(deltaTime);
	
	// kala katoaa
	if(player->collidesTo(this, 0))
		this->setSize(0,0);

	if(hitboxCheck->GetNameOfObject(player) == "Goal" && getSize() == vec2(0,0))
	{
		finishedGame = true;
	}
}

bool Fish::isGameFinished()
{
	return finishedGame;
}
#include "Fish.h"
#include "HitCheck.h"
#include <iostream>

// Fish ei tarvitse hitboxia eik� mappia, koska se ei liiku
Fish::Fish(int gameObjectType, SpriteSheet* spriteSheet, Player* player, HitCheck* hitboxCheck)
	: AnimatedSpriteGameObject(gameObjectType, spriteSheet)  // cpp- ja h-filussa pit�� olla samat muuttujat (cpp public)
{
	this->player = player; // pit�� k�ytt�� thisnuolihommaa, koska Player*player on sama h- ja cpp-filuissa
	setPosition(vec2(52,21));

	this->hitboxCheck = hitboxCheck;
}


Fish::~Fish(void)
{
}

void Fish::update(float deltaTime)
{
	AnimatedSpriteGameObject::update(deltaTime);
	
	// kala katoaa
	if(player->collidesTo(this, 0))
		this->setSize(0,0);

	if(hitboxCheck->GetNameOfObject(player) == "Goal" && getSize() == vec2(0,0))
	{
		std::cout << "P�llit sit muide ruoat >:(" << std::endl;
	}
}

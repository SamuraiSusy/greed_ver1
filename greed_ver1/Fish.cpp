#include "Fish.h"
#include "HitCheck.h"
#include <iostream>
#include <es_util.h>
#include <SpriteBatch.h>

namespace
{
	// SpriteBatchGroup is used to draw Sprites and Texts.
	SpriteBatchGroup* batch = 0;

	// Texture (loaded bitmap)
	Texture* openGLTexture = 0;
	// Sprite (specifies rendering paremeters for region of texture to be rendered to screen)
	Sprite* sprite = 0;

	bool finishedGame = false;
}

// Fish ei tarvitse hitboxia eikä mappia, koska se ei liiku
Fish::Fish(int gameObjectType, Texture* texture, Player* player, HitCheck* hitboxCheck)
	: SpriteGameObject(gameObjectType, texture)  // cpp- ja h-filussa pitää olla samat muuttujat (cpp public)
{
	this->player = player; // pitää käyttää thisnuolihommaa, koska Player*player on sama h- ja cpp-filuissa
	setPosition(vec2(52,21));

	this->hitboxCheck = hitboxCheck;

	batch = new SpriteBatchGroup();
	openGLTexture = new Texture("feebas.png");
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
		batch->clear();
		//batch->addSprite(openGLTexture, sprite, vec2(0,0), 0, vec2(100,100), vec2(0,0));
		//batch->render();
	}
}

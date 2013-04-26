#include "Player.h"


int playerAnimation = 0;

Player::Player(int gameObjectType, SpriteSheet* sprite, HitCheck* HitChecker, TmxMap* Map)
	: AnimatedSpriteGameObject(gameObjectType,sprite)
{
	hitboxCheck = HitChecker;
	map = Map;
	setPosition(vec2(15,20));
	destination = getPosition();
}


Player::~Player(void)
{
}

void Player::update( float deltaTime )
{
	AnimatedSpriteGameObject::update(deltaTime);

	float rotationSpeed = 1.0f; // Radians / second
	float moveSpeed = 30.0f; // tiles / second
	vec2 playerMovement;

	if (getKeyState(KEY_SPACE))
		this->setActiveAnimation((this->getActiveAnimation() + 1)%4);
	// Rotate gameobject accorging to keys
	float horizontal = float(getKeyState(KEY_RIGHT)-getKeyState(KEY_LEFT));

	// Get move direction from keyboard
	float vertical = float(getKeyState(KEY_DOWN)-getKeyState(KEY_UP));

	if (getMouseButtonState(MOUSE_LEFT))
		destination = map->screenToMapCoordinates(vec2(getMouseAxisX(), getMouseAxisY() ));

	//direction = vec2(horizontal,vertical);
	direction = (destination - getPosition());
	direction.Normalize();

	playerMovement = deltaTime*moveSpeed*direction;

	if(playerMovement.x > abs(playerMovement.y)) // liikkuu oikealle
	{
		if(this->getActiveAnimation()!= 0)
		this->setActiveAnimation(0);
	}
	else if(playerMovement.x < -abs(playerMovement.y)) // liikkuu vasemmalle
	{
		if(this->getActiveAnimation()!= 2)
		this->setActiveAnimation(2);
	}

	else if(playerMovement.y > abs(playerMovement.x)) // liikkuu alas
	{
		if(this->getActiveAnimation()!= 4)
		this->setActiveAnimation(4);
	}

	else if(playerMovement.y < -abs(playerMovement.x)) // liikkuu ylös
	{
		if(this->getActiveAnimation()!= 6)
		this->setActiveAnimation(6);
	}
	else
	{
		this->setActiveAnimation(this->getActiveAnimation());
	}

	if (playerMovement.Length() > (destination - getPosition()).Length())
		playerMovement = destination - getPosition();

	setPosition(getPosition() + playerMovement);
	//setPosition(destination);

	vec2 hit = hitboxCheck->CheckMapHit(this,16);

	if(hit.Length() > 0)
	{
		setPosition(hit);
	}
}
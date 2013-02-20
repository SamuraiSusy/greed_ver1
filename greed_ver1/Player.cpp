#include "Player.h"


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
	float moveSpeed = 8.0f; // tiles / second
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
		this->setActiveAnimation(3);
	}

	if(playerMovement.x < -abs(playerMovement.y)) // liikkuu vasemmalle
	{
		this->setActiveAnimation(2);
	}

	if(playerMovement.y > abs(playerMovement.x)) // liikkuu alas
	{
		this->setActiveAnimation(0);
	}

	if(playerMovement.y < -abs(playerMovement.x)) // liikkuu ylös
	{
		this->setActiveAnimation(1);
	}

	if (playerMovement.Length() > (destination - getPosition()).Length())
		playerMovement = destination - getPosition();

	setPosition(getPosition() + playerMovement);
	//setPosition(destination);

	vec2 hit = hitboxCheck->CheckMapHit(this);

	if(hit.Length() > 0)
	{
		setPosition(hit);
	}
}
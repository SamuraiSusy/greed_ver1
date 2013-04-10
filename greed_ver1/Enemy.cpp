#include "Enemy.h"


Enemy::Enemy(int gameObjectType, SpriteSheet* sprite, HitCheck* HitChecker, TmxMap* Map, Pathfinding* Pathfinder)
	: AnimatedSpriteGameObject(gameObjectType,sprite)
{
	hitboxCheck = HitChecker;
	map = Map;
	setPosition(vec2(20,20));
	destination = getPosition();
	pathfinder = Pathfinder;


	
	for( int i=0; i<4; ++i ) // ANIMAATIO
	{
		std::vector<int> indices;
		indices.resize(1);
		for( size_t j=0; j<indices.size(); ++j )
		{
			indices[j] = i + j;
		}

		// Add looping animation.
		addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,1, 1.0f, true));
	}
	
	setActiveAnimation(0);
}


Enemy::~Enemy(void)
{
}

void Enemy::setTarget(vec2 goal)
{
	this->goal = goal;
}

void Enemy::update(float deltaTime)
{
	AnimatedSpriteGameObject::update(deltaTime);

	float rotationSpeed = 1.0f; // Radians / second
	float moveSpeed = 5.0f; // tiles / second
	vec2 enemyMovement;

	if(pathfinder->FindPathYam2D(getPosition().x, getPosition().y, goal.x, goal.y,2))
    {
            path.clear();
            path = pathfinder->GetPath();

			if (path.size()>1)
				destination = *path.erase(path.begin());
    }

	//if (getKeyState(KEY_SPACE))
	//	this->setActiveAnimation((this->getActiveAnimation() + 1)%4);
	//// Rotate gameobject accorging to keys
	//float horizontal = float(getKeyState(KEY_RIGHT)-getKeyState(KEY_LEFT));

	//// Get move direction from keyboard
	//float vertical = float(getKeyState(KEY_DOWN)-getKeyState(KEY_UP));

	//direction = vec2(horizontal,vertical);
	direction = (destination - getPosition());
	direction.Normalize();

	enemyMovement = deltaTime * moveSpeed * direction;

	if(enemyMovement.x > abs(enemyMovement.y)) // liikkuu oikealle
	{
		this->setActiveAnimation(3);
	}

	if(enemyMovement.x < -abs(enemyMovement.y)) // liikkuu vasemmalle
	{
		this->setActiveAnimation(2);
	}

	if(enemyMovement.y > abs(enemyMovement.x)) // liikkuu alas
	{
		this->setActiveAnimation(0);
	}

	if(enemyMovement.y < -abs(enemyMovement.x)) // liikkuu ylös
	{
		this->setActiveAnimation(1);
	}

	if (enemyMovement.Length() > (destination - getPosition()).Length())
    {
        enemyMovement = destination - getPosition();
        if (path.size() > 1)
            destination = *path.erase(path.begin());
    }

	setPosition(getPosition() + enemyMovement);
	//setPosition(destination);

	vec2 hit = hitboxCheck->CheckMapHit(this);

	if(hit.Length() > 0)
	{
		setPosition(hit);
	}
}
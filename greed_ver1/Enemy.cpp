#include "Enemy.h"

#include <iostream>


Enemy::Enemy(int gameObjectType, SpriteSheet* sprite, HitCheck* HitChecker, TmxMap* Map, Pathfinding* Pathfinder, std::vector<Enemy*> *enemies)
	: AnimatedSpriteGameObject(gameObjectType,sprite),
	  enemies(enemies)
{
	hitboxCheck = HitChecker;
	map = Map;
	setPosition(vec2(20,20));
	destination = getPosition();
	pathfinder = Pathfinder;

for(int i = 0; i < 8; ++i) // ANIMAATIO
	{
		std::vector<int> indices;
		indices.resize(2);
		float fps = 10.0f;

		for( size_t j = 0; j < indices.size(); ++j )
		{
			indices[j] = i + j;
		}

		// Add looping animation.
		addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices, fps, 1.0f, true));
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

			destination = path[0];
			if (path.size()>1)
				*path.erase(path.begin());
    }

	direction = (destination - getPosition());
	direction.Normalize();

	enemyMovement = deltaTime * moveSpeed * direction;


	if(enemyMovement.x > abs(enemyMovement.y)) // liikkuu oikealle
	{
		if(this->getActiveAnimation()!= 4)
		this->setActiveAnimation(4);
	}
	else if(enemyMovement.x < -abs(enemyMovement.y)) // liikkuu vasemmalle
	{
		if(this->getActiveAnimation()!= 6)
		this->setActiveAnimation(6);
	}

	else if(enemyMovement.y > abs(enemyMovement.x)) // liikkuu alas
	{
		if(this->getActiveAnimation()!= 0)
		this->setActiveAnimation(0);
	}

	else if(enemyMovement.y < -abs(enemyMovement.x)) // liikkuu ylös
	{
		if(this->getActiveAnimation()!= 2)
		this->setActiveAnimation(2);
	}
	else
	{
		this->setActiveAnimation(this->getActiveAnimation());
	}

	if (enemyMovement.Length() > (destination - getPosition()).Length())
		enemyMovement = destination - getPosition();

	setPosition(getPosition() + enemyMovement);


	vec2 hit = hitboxCheck->CheckMapHit(this);

	if(hit.Length() > 0)
	{
		setPosition(hit);
	}

	//for(int i = 0; i < enemies->size(); ++i)
	//{
	//	if((*enemies)[i] != this)
	//	{
	//		std::cout<<"Hard"<<std::endl;
	//		vec2 dodge = getPosition();
	//		hitboxCheck->distanceToBorder((*enemies)[i],this,&dodge);
	//		setPosition(dodge);
	//	}
	//}
}
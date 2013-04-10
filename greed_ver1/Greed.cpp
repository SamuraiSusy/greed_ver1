#include "Greed.h"

Layer* createNewLayer(void* userData, Map* map, const std::string& name, float opacity, bool visible, const PropertySet& properties)
{		
	esLogMessage("Creating static layer!");

	// Check that if "static"-propery is set to Layer properties, and if it's value is "true" or 1
	if( properties.hasProperty("static") && 
		(properties.getLiteralProperty("static")=="true" || properties.getLiteralProperty("static")=="1")  )
	{
		// Is, so, then create static layer, which is batched only once, at first call to Map::render
		return new Layer(map, name, opacity, visible, true, properties);
	}

	// by default create dynamic layer, which is batced each frame
	return new Layer(map, name, opacity, visible, false, properties); 
}

Greed::Greed()
{
	batch = new SpriteBatchGroup();


	map = new TmxMap();
	map->registerCreateNewLayerFunc(createNewLayer);
	map->loadMapFile("greed_level1.tmx");
	HitChecker = new HitCheck(map);
	Texture* playerTexture = new Texture("player.png");
	SpriteSheet* playerSprite = SpriteSheet::generateSpriteSheet(playerTexture,32,32,0,0); // PELAAJA
	player = new Player(0,playerSprite,HitChecker, map);
	player->setSize(32,32);
	player->setName("Player");
	map->getLayer("GameObjects")->addGameObject(player);
	map->getCamera()->setPosition( vec2(map->getWidth()/2.0f -0.5f, map->getHeight()/2.0f -0.5f)); // Keskitet‰‰n kamera

	pathfinding = new Pathfinding(map,0);

	enemyTexture = new Texture("player.png");
	enemySprite = SpriteSheet::generateSpriteSheet(enemyTexture,32,32,0,0); // VIHU

	for (int i = 0; i <3 ; i++)
	{
		Enemy* enemy = new Enemy(0,enemySprite,HitChecker, map, pathfinding);
		enemies.push_back(enemy);
		enemy->setSize(32,32);
		enemy->setName("Enemy");
		map->getLayer("GameObjects")->addGameObject(enemy);
	}
	enemies[0]->setPosition(42,16);
	enemies[1]->setPosition(42,20);
	enemies[2]->setPosition(42,24);
	
	

	for(int i=0; i<4; ++i) // ANIMAATIO
	{
		std::vector<int> indices;
		indices.resize(1);
		for( size_t j = 0; j < indices.size(); ++j )
		{
			indices[j] = i + j;
		}

		// Add looping animation.
		player->addAnimation(i, SpriteAnimation::SpriteAnimationClip(indices,1, 1.0f, true));
	}

	player->setActiveAnimation(0);
}


Greed::~Greed()
{
	delete batch;
	delete map;
	delete HitChecker;
}

void Greed::Update(float DeltaTime)
{
	map->update(DeltaTime);
	/*map->getCamera()->setPosition(player->getPosition());*/
	for(int i = 0; i < enemies.size(); i++)
		enemies[i]->setTarget(player->getPosition());

	/*if(enemies[0]->collidesTo(enemies[1])
	*/
}

void Greed::Draw(ESContext *esContext)
{
	batch->clear();
	
	map->getCamera()->setScreenSize(esContext->width,esContext->height); 

	map->render();

	batch->render();
}
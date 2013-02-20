#ifndef RENDERSTATISTICS_H
#define RENDERSTATISTICS_H

#include <iostream>
#include <string>
#include <es_util.h>
#include <SpriteBatch.h>
#include <SpriteSheet.h>
#include <Text.h>
#include <Texture.h>
#include <sstream>


using namespace yam2d;

class RenderStatistics
{

public:
	RenderStatistics(std::string Font, std::string dat, std::string bitmap);
	void update(float deltaTime);
	void render(float x, float y);
	~RenderStatistics(void);

private:
	float count;
	float second;
	float fps;
	float textUpdater;
	int frameNumber;
	int prevFrameNumber;
	bool updateText;
	Text* text1;
	Text* text2;
	Text* text3;
	Text* text4;
	int lane;
	SpriteBatchGroup* batch;
	SpriteSheet* font;
	Texture* fontTexture;
};

#endif
#include "RenderStatistics.h"

template <class T>
std::string to_string(T & t)
{
	std::stringstream s;
	s << t;
	return s.str();
}

RenderStatistics::RenderStatistics(std::string Font, std::string dat, std::string bitmap)
{
	count = 0;
	frameNumber = 0;
	prevFrameNumber = 0;
	second = 0;
	textUpdater = 0;
		// Create new sprite batch group. This must be deleted at deinit.
	batch = new SpriteBatchGroup();
	
	// Load font texture. Made with font creation tool like bitmap font builder.
	fontTexture = new Texture("Fixedsys_24_Bold.png");

	// Create font clip areas (sprite sheet), from dat file and texture. Dat-file is made with bitmap font builder.
	font = SpriteSheet::autoFindFontFromTexture(fontTexture,"Fixedsys_24_Bold.dat");

	// Create new text-object
	lane = 30;
	text1 = new Text(font);
	text2 = new Text(font);
	text3 = new Text(font);
	text4 = new Text(font);

}


RenderStatistics::~RenderStatistics(void)
{
	delete text1;
	delete text2;
	delete text3;
	delete text4;
	delete batch;
}

void RenderStatistics::update(float deltaTime)
{
	// Update total time counter.
	count += deltaTime;
	frameNumber++;
	second += deltaTime;
	textUpdater += deltaTime;

	if (second > 1.0f)
	{
		fps = (frameNumber - prevFrameNumber)/second;
		prevFrameNumber = frameNumber;
		second -= 1.0f;
		text4->setText("FPS: " + to_string(fps));
	}

	if (textUpdater > 0.02f) 
	{
		textUpdater = 0;
		text1->setText("Total Running Time: " + to_string(count));
		text2->setText("Total Frames: " + to_string(frameNumber));
		float averagefps = frameNumber/count;
		text3->setText("Average FPS: " + to_string(averagefps));
		updateText = true;
	}

}

void RenderStatistics::render(float x, float y)
{
	if (updateText)
	{
		batch->clear();
		batch->addText(fontTexture, text1, vec2(x + text1->getWidth()/2 + lane,y-1*lane), 0);
		batch->addText(fontTexture, text2, vec2(x + text2->getWidth()/2 + lane,y-2*lane), 0);
		batch->addText(fontTexture, text3, vec2(x + text3->getWidth()/2 + lane,y-3*lane), 0);
		batch->addText(fontTexture, text4, vec2(x + text4->getWidth()/2 + lane,y-4*lane), 0);
		updateText = false;
	}
	batch->render(0.5f);
}
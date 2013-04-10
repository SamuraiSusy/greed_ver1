#include <Input.h>
#include <es_util.h>
#include "RenderStatistics.h"
#include "Greed.h"

float count = 0.0f;

using namespace yam2d;

namespace
{

	RenderStatistics* RS = 0;

	Greed* Game;

	bool showRS = false;
	
}

// Initialize the game
bool init ( ESContext *esContext )
{

	RS = new RenderStatistics("Fixedsys_24_Bold.png","Fixedsys_24_Bold.dat","");

	Game = new Greed();
	
	return true;
}

// Deinitialize the game
void deinit ( ESContext *esContext )
{
	delete RS;
	delete Game;
}


// Update game
void update( ESContext* ctx, float deltaTime )
{
	// Update total time counter.
	count += deltaTime;

	if(getKeyState(KeyCodes::KEY_F1))
	{
		showRS = true;
	}

	else
	{
		showRS = false;
	}

	RS->update(deltaTime);

	if(deltaTime > 0.1f)
		deltaTime = 0.1f; // EI TARVI AALTOSULKEITA seuraavaa riviä varten

	Game->Update(deltaTime);
}


// Draw game
void draw ( ESContext *esContext )
{
	// Set OpenGL clear color
	glClearColor( 1.0f, 0.1f, 0.1f, 0.0f );

	// Clear the color buffer
	glClear ( GL_COLOR_BUFFER_BIT );
	
	// Set the viewport to be full window area.
	glViewport( 0, 0, esContext->width, esContext->height );
	
	// Set projection to identity
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		
	// Calculate half screen size
	float left = -0.5f*esContext->width;
	float right = 0.5f*esContext->width;
	float bottom = -0.5f*esContext->height;
	float top = 0.5f*esContext->height;
	
	// Set OpenGL orthogonal projection for screen size <esContext->width,esContext->height>
	glOrthof( float(int(left)), float(int(right)), float(int(bottom)), float(int(top)), -1.0, 1.0f);
	
	// Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	// Enable alpha blending (transparency)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	// Set model view matrix to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (showRS)
	{
		RS->render(esContext->width/-2.0f,esContext->height/2.0f);
	}

	Game->Draw(esContext);
}


int main ( int argc, char *argv[] )
{
	ESContext esContext;
	esInitContext ( &esContext );
	esCreateWindow( &esContext, "Greed", 960, 640, ES_WINDOW_DEFAULT ); // konsolin koko
   
	if ( !init ( &esContext ) )
		return 0;

	esRegisterDrawFunc( &esContext, draw );
	esRegisterUpdateFunc( &esContext, update );
	esRegisterDeinitFunc( &esContext, deinit);

	esMainLoop ( &esContext );
	return 0;
}

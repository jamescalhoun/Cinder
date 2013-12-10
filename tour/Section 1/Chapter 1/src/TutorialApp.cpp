#include "cinder/app/AppBasic.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/Texture.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;

class TutorialApp : public AppBasic {
 public:
	void prepareSettings( Settings *settings );
	void setup();
	void update();
	void draw();
	
	gl::Texture myImage;
	
	ParticleController mParticleController;
};

void TutorialApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 800, 600 );
	settings->setFrameRate( 60.0f );
}

void TutorialApp::setup()
{
	try {
        std::string p = getOpenFilePath( "", ImageIo::getLoadExtensions() );
        if( ! p.empty() ) { // an empty string means the user canceled
            myImage = gl::Texture( loadImage( p ) );
        }
    }
    catch( ... ) {
        console() << "Unable to load the image." << std::endl;
    }

	mParticleController.addParticles( 250 );
}

void TutorialApp::update()
{
	mParticleController.update();
}

void TutorialApp::draw()
{	
	gl::clear( Color( 0, 0, 0 ), true );
	
	myImage.enableAndBind();
    if( myImage )
        gl::draw( myImage, getWindowBounds() );

	glDisable( GL_TEXTURE_2D );
	glColor3f( 1, 1, 1 );
	mParticleController.draw();
}


CINDER_APP_BASIC( TutorialApp, RendererGl )

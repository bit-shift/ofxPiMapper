#include "Three60Source.h"

const size_t WIDTH = 1280;
const size_t HEIGHT = 1024;

Three60Source::Three60Source(const size_t index) 
	: ofx::piMapper::FboSource()
	, width_(WIDTH)
	, height_(HEIGHT)
	, offset_(index * 60.f)
{
	name = "360 FBO Source " + to_string(index);
}

void Three60Source::setup() 
{
	allocate(width_, height_);

	sphere_.setRadius(400);
	
	// light_.setup();
	// light_.setPosition(-100, 200, 0);

	image_.load("data/sources/images/test_screen.jpg");

	cam_.rotate(offset_, 0.0, 1.0, 0.0);
}

void Three60Source::update()
{
	
}

void Three60Source::draw() 
{
	ofClear(0);
	ofDisableArbTex();

	ofPushMatrix();
	cam_.setPosition(ofVec3f(0, 100, 100));
	cam_.begin();
	{
		// image_.getTexture().bind();
		// sphere_.draw();
		sphere_.drawWireframe();
		// image_.getTexture().unbind();
	}	
	cam_.end();	
	ofPopMatrix();
}
#include "Three60Source.h"

const size_t WIDTH = 800;
const size_t HEIGHT = 600;

Three60Source::Three60Source(const size_t index) 
	: ofx::piMapper::FboSource()
	, width_(WIDTH)
	, height_(HEIGHT) 
{
	name = "360 FBO Source " + to_string(index);
}

void Three60Source::setup() 
{
	allocate(width_, height_);

	sphere_.setRadius(100);
	
	// light_.setup();
    // light_.setPosition(-100, 200, 0);

	box_.rotate(60.0f, 1.0, 0.0, 0.0);
	// sphere_.setPosition(WIDTH / 2, HEIGHT / 2, 0);
    // sphere_.rotate(spinX, 1.0, 0.0, 0.0);
	// sphere_.rotate(spinY, 0, 1.0, 0.0);
	
	boxMaterial_.setDiffuseColor(ofFloatColor::red);
	boxMaterial_.setShininess(0.02);
}

void Three60Source::update() 
{
	
}

void Three60Source::draw() 
{
	ofClear(0);
	// ofSetColor(255);
	
	// cam_.begin();
	{
		// boxMaterial_.begin();
		{
			sphere_.draw();
		}		
		// boxMaterial_.end();
	}	
    // cam_.end();
}
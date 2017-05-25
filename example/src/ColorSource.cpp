#include "ColorSource.h"

ColorSource::ColorSource() 
	: _state(237, 40, 255)
	, _interval(60)
{
	name = "Color FBO Source";
	allocate(500, 500);
}

void ColorSource::setup() {    
    ofSetFrameRate(60);  
    Tweenzor::init();    
    _lerpAmount = 255.f;  
    Tweenzor::add(&_lerpAmount, 0.f, 255.f, 0.f, 10.f);  
    Tweenzor::getTween(&_lerpAmount)->setRepeat(-1, true);  
}  

void ColorSource::update(){  
    Tweenzor::update(ofGetElapsedTimeMillis());  
}  

void ColorSource::draw(){
	ofClear(0);

	ofSetColor(255, 40, _lerpAmount);
	ofSetColor(_lerpAmount, 40, _lerpAmount);

	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		ofDrawRectangle(0, 0, getWidth(), getHeight());
	#else
		ofRect(0, 0, getWidth(), getHeight());
	#endif
}

void ColorSource::exit()
{
	Tweenzor::destroy();
}
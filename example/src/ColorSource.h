#pragma once

#include "ofMain.h"
#include "ofColor.h"
#include "ofxTweenzor.h"

#include "FboSource.h"


class ColorSource : public ofx::piMapper::FboSource {
	
public:
	ColorSource();

	void setup();
	void update();
	void draw();
	void exit();

private:
	ofColor _state;
	size_t	_counter;
	size_t	_interval;

	float 	_lerpAmount;
};
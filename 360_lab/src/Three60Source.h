#pragma once

#include "ofMain.h"
#include "FboSource.h"

class Three60Source : public ofx::piMapper::FboSource {
public:
	Three60Source(size_t index);
	~Three60Source() = default;

    void setup();
	void update();
	void draw();

private:
	size_t width_;
	size_t height_;
	float offset_;

	ofSpherePrimitive sphere_;
	ofLight light_;
	ofEasyCam cam_;

	ofImage image_;
};
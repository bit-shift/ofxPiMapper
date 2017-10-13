#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "Three60Source.h"
#include "VideoSource.h"

class ofApp : public ofBaseApp {
	public:
		ofApp();
		~ofApp();

		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
		void keyReleased(int key);
	
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);

		ofxPiMapper piMapper_;

		// By using a custom source that is derived from FboSource
		// you will be able to see the source listed in sources editor
		Three60Source source0_= {0};
		Three60Source source1_= {1};
		Three60Source source2_= {2};
		Three60Source source3_= {3};
		Three60Source source4_= {4};
		Three60Source source5_= {5};

		ofVideoPlayer player_;
};

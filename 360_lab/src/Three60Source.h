#pragma once

#include "ofMain.h"
#include "FboSource.h"

class Three60Source : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();

		unique_ptr<ofVideoPlayer> _videoPlayer;
		bool _initialVolumeSet;
};
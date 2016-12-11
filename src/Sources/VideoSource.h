#pragma once

#include <memory>

#include "ofMain.h"
#include "BaseSource.h"

#ifdef TARGET_RASPBERRY_PI
 #include "ofxOMXPlayer.h"
 #include "OMXPlayerCache.h"
#endif

namespace ofx {
namespace piMapper {

class VideoSource : public BaseSource {

	public:

		// TODO: Create enableAudio() and disableAudio() methods
		//       for live audio enabling and disabling.
		static bool enableAudio;
		static bool useHDMIForAudio;

		VideoSource();
		~VideoSource();

		string & getPath();
		void loadVideo(string & path);
		void clear();
        void togglePause();

		#ifndef TARGET_RASPBERRY_PI
			void update(ofEventArgs & args);
		#endif

	private:

		#ifdef TARGET_RASPBERRY_PI
			// TODO: Naming different for less confusion
			std::unique_ptr<ofxOMXPlayer> _omxPlayer;     
		#else
			// Go with ofVideoPlayer or
			// TODO: High Performance Video player on newer Macs
			std::unique_ptr<ofVideoPlayer> _videoPlayer;
			bool _initialVolumeSet;
		#endif

};

} // namespace piMapper
} // namespace ofx
#include "VideoSource.h"

namespace ofx {
namespace piMapper {

bool VideoSource::enableAudio = false;
bool VideoSource::useHDMIForAudio = false;

VideoSource::VideoSource(){
	loadable = true;
	loaded = false;
	type = SourceType::SOURCE_TYPE_VIDEO;
	#ifndef TARGET_RASPBERRY_PI
		_initialVolumeSet = false;		
	#endif
}

VideoSource::~VideoSource(){}

void VideoSource::loadVideo(string & filePath){
	path = filePath;
	setNameFromPath(filePath);
	#ifdef TARGET_RASPBERRY_PI
		_omxPlayer.reset(OMXPlayerCache::instance()->load(filePath));
		texture = &(_omxPlayer->getTextureReference());
	#else
		_videoPlayer.reset(new ofVideoPlayer());
		_videoPlayer->load(filePath);
		_videoPlayer->setLoopState(OF_LOOP_NORMAL);
		_videoPlayer->play();
		_videoPlayer->setVolume(VideoSource::enableAudio ? 1.0f : 0.0f);
		texture = &(_videoPlayer->getTexture());
		ofAddListener(ofEvents().update, this, &VideoSource::update);
	#endif
	loaded = true;
}

void VideoSource::clear(){
	texture = 0;
	#ifdef TARGET_RASPBERRY_PI
		OMXPlayerCache::instance()->unload(path);
	#else
		ofRemoveListener(ofEvents().update, this, &VideoSource::update);
		_videoPlayer->stop();
		_videoPlayer->close();
	#endif
	loaded = false;
}

void VideoSource::togglePause(){
    #ifdef TARGET_RASPBERRY_PI
        _omxPlayer->togglePause();
    #else
        _videoPlayer->setPaused(!_videoPlayer->isPaused());
    #endif
}

#ifndef TARGET_RASPBERRY_PI
	void VideoSource::update(ofEventArgs & args){
		if(_videoPlayer != 0){
			if(!_initialVolumeSet){
				if(_videoPlayer->isInitialized()){
					_videoPlayer->setVolume(VideoSource::enableAudio ? 1.0f : 0.0f);
					_initialVolumeSet = true;
				}
			}
			_videoPlayer->update();
		}
	}
#endif

} // namespace piMapper
} // namespace ofx
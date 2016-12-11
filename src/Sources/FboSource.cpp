#include "FboSource.h"

namespace ofx {
namespace piMapper {

FboSource::FboSource(){
	name = PIMAPPER_FBO_SOURCE_DEF_NAME;
	loadable = false;
	loaded = false;
	type = SourceType::SOURCE_TYPE_FBO;
	_disableDraw = false;
}

FboSource::~FboSource(){
	removeAppListeners();
	clear();
}

void FboSource::addAppListeners(){
	ofLogNotice("FboSource") << "Adding app listeners";
	ofAddListener(ofEvents().update, this,
				  &FboSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
	ofAddListener(ofEvents().draw, this,
				  &FboSource::onAppDraw, OF_EVENT_ORDER_BEFORE_APP);
	ofAddListener(ofEvents().exit, this,
				  &FboSource::onAppExit, OF_EVENT_ORDER_AFTER_APP);
}

void FboSource::removeAppListeners(){
	ofLogNotice("FboSource") << "Removing app listeners";
	ofRemoveListener(ofEvents().update, this,
					 &FboSource::onAppUpdate, OF_EVENT_ORDER_BEFORE_APP);
	ofRemoveListener(ofEvents().draw, this,
					 &FboSource::onAppDraw, OF_EVENT_ORDER_BEFORE_APP);
	ofRemoveListener(ofEvents().exit, this,
					 &FboSource::onAppExit, OF_EVENT_ORDER_AFTER_APP);
}

void FboSource::onAppUpdate(ofEventArgs & args){
	if(!_fbo || !_fbo->isAllocated()){
		ofLogWarning("FboSource") << "FBO not allocated";
		return;
	}
	update();
}

void FboSource::onAppDraw(ofEventArgs & args){
	if(!_fbo || !_fbo->isAllocated()){
		ofLogWarning("FboSource") << "FBO not allocated";
		return;
	}
	
	if(_disableDraw){
		return;
	}
	
	_fbo->begin();
	draw();
	_fbo->end();
}

void FboSource::onAppExit(ofEventArgs & args){
	exit();
}

void FboSource::setDisableDraw(bool b){
	_disableDraw = b;
}

void FboSource::allocate(int width, int height){
	clear();
	_fbo.reset(new ofFbo());
	_fbo->allocate(width, height);

	// Clear FBO
	_fbo->begin();
	ofClear(0);
	_fbo->end();
	
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		_texture = _fbo->getTexture();
	#else
		_texture = _fbo->getTextureReference();
	#endif
}

void FboSource::clear(){
	_fbo.reset(nullptr);
}

int FboSource::getWidth(){
	if(_fbo->isAllocated()){
		return _fbo->getWidth();
	}else{
		return 0;
	}
}

int FboSource::getHeight(){
	if(_fbo->isAllocated()){
		return _fbo->getHeight();
	}else{
		return 0;
	}
}

} // namespace piMapper
} // namespace ofx
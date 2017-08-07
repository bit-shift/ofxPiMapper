#include "SurfaceStack.h"

namespace ofx {
namespace piMapper {

SurfaceStack::SurfaceStack() {

#ifdef TARGET_OPENGLES
	ofLogError("FboSource::FboSource()") << "OpenGL ES not supported and no shaders provided.";
	shader.load("shaders/texture/shadersES2/shader");
#else
	if(ofIsGLProgrammableRenderer()){
		shader.load("shaders/texture/shadersGL3/shader");
	}else{
		ofLogError("FboSource::FboSource()") << "OpenGL 2.x not supported and no shaders provided.";
		shader.load("shaders/texture/shadersGL2/shader");
	}
#endif

	shadingFbo.allocate(ofGetWidth(), ofGetHeight());
	targetFbo.allocate(ofGetWidth(), ofGetHeight());
}

void SurfaceStack::push_back(BaseSurface * s){
	ofAddListener(s->verticesChangedEvent, this, &SurfaceStack::onVerticesChanged);
	ofAddListener(s->vertexChangedEvent, this, &SurfaceStack::onVertexChanged);
	_surfaces.push_back(s);
}

void SurfaceStack::pop_back(){
	ofRemoveListener(_surfaces.back()->verticesChangedEvent, this, &SurfaceStack::onVerticesChanged);
	ofRemoveListener(_surfaces.back()->vertexChangedEvent, this, &SurfaceStack::onVertexChanged);
	_surfaces.pop_back();
}

void SurfaceStack::erase(int i){
	ofRemoveListener(_surfaces[i]->verticesChangedEvent, this, &SurfaceStack::onVerticesChanged);
	ofRemoveListener(_surfaces[i]->vertexChangedEvent, this, &SurfaceStack::onVertexChanged);
	_surfaces.erase(_surfaces.begin() + i);
}

void SurfaceStack::swap(int a, int b){
	std::swap(_surfaces[a], _surfaces[b]);
}

void SurfaceStack::draw() {
	ofEnableAlphaBlending();

	for (auto* surface: _surfaces) {
		auto* source = surface ? surface->getSource() : nullptr;
		auto* texture = source ? source->getTexture() : nullptr;
		if (texture)
		{
			shader.begin();
			shader.setUniformTexture("tex0", *texture, 1);

			surface->draw();
			shader.end();
		}			
	}
}

void SurfaceStack::clear(){
	for(int i = 0; i < size(); ++i){
		ofRemoveListener(_surfaces[i]->verticesChangedEvent, this, &SurfaceStack::onVerticesChanged);
		ofRemoveListener(_surfaces[i]->vertexChangedEvent, this, &SurfaceStack::onVertexChanged);
	}
	_surfaces.clear();
}

int SurfaceStack::size(){
	return _surfaces.size();
}

BaseSurface * SurfaceStack::operator[](int i){
	return at(i);
}

BaseSurface * SurfaceStack::at(int i){
	if(i >= _surfaces.size()){
		throw runtime_error("SurfaceStack index out of bounds");
	}
	return _surfaces[i];
}

BaseSurface * SurfaceStack::back(){
	return _surfaces.back();
}

void SurfaceStack::onVerticesChanged(vector<ofVec3f> & vertices){
	ofNotifyEvent(verticesChangedEvent, vertices, this);
}

void SurfaceStack::onVertexChanged(int & i){
	ofNotifyEvent(vertexChangedEvent, i, this);
}

SurfaceStack * SurfaceStack::clone(){
	SurfaceStack * stack = new SurfaceStack();
	for(unsigned int i = 0; i < _surfaces.size(); ++i){
		BaseSurface * surface = _surfaces[i]->clone();
		stack->push_back(surface);
	}
	return stack;
}

} // namespace piMapper
} // namespace ofx

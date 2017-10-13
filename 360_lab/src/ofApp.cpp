#include "ofApp.h"

ofApp::ofApp()
	: ofBaseApp()
{

}

ofApp::~ofApp() 
{
	player_.stop();
	player_.close();
}

void ofApp::setup()
{
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
	piMapper_.registerFboSource(&source0_);
	piMapper_.registerFboSource(&source1_);
	piMapper_.registerFboSource(&source2_);
	piMapper_.registerFboSource(&source3_);
	piMapper_.registerFboSource(&source4_);
	piMapper_.registerFboSource(&source5_);
	piMapper_.setup();

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();
	
	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);

	// ofEnableDepthTest();
	// ofDisableAlphaBlending();
}

void ofApp::update(){
	piMapper_.update();
}

void ofApp::draw(){
	piMapper_.draw();
}

void ofApp::keyPressed(int key){
	piMapper_.keyPressed(key);
}

void ofApp::keyReleased(int key){
	piMapper_.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
	piMapper_.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	piMapper_.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	piMapper_.mouseDragged(x, y, button);
}

#include "ofMain.h"
#include "ofApp.h"
#include <string>
#include <vector>
#include "Settings.h"

int main(int argc, char * argv[]){
	auto win = std::make_shared<ofAppGLFWWindow>();
	
	ofGLWindowSettings settings;
	settings.width = 800;
	settings.height = 500;
	settings.windowMode = OF_WINDOW;
	settings.setGLVersion(4,5);

	ofInit();	
	ofGetMainLoop()->addWindow(win);
	
	win->setup(settings);
	win->setMultiDisplayFullscreen(true);
	
	ofRunApp(new ofApp());
}

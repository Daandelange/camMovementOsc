#include "ofApp.h"
#include "ofAppNoWindow.h"
//#include "ofAppEGLWindow.h"

int main(){
	ofSetupOpenGL(1, 1, OF_WINDOW);
	ofRunApp(new ofApp());
	
	//	ofGLFWWindowSettings settings;
	//	settings.visible = false;
	//	ofCreateWindow(settings);
	
	//ofEGLWindowSettings settings;
	//settings.visible = false;
	//ofCreateWindow(settings);
	
	//ofAppNoWindow window;
	//ofSetupOpenGL(&window, 0, 0, OF_WINDOW);
	//ofSetWindow(&window);
	//ofRunApp(new ofApp());	
}

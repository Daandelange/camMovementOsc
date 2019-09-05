#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofLogNotice("ofxCamMovementOsc", "No camera found. Exiting now.");
	
	ofLogNotice("ofxCamMovementOsc", "Grabbing first camera found. (no selection options yet!)");
	camera.setDeviceID(CAM_DEVICE);
	
	//get back a list of devices.
	vector<ofVideoDevice> devices = camera.listDevices();
	
	for(size_t i = 0; i < devices.size(); i++){
		//log the device
		ofLogNotice("ofxCamMovementOsc") << devices[i].id << ": " << devices[i].deviceName << (devices[i].bAvailable?" (ready)":" (unavailable)");
	}
	
	// a cheap resolution is enough. Old cams work well.
	camera.setup(CAM_W, CAM_H);
	
	// quit if no cam
	if(!camera.isInitialized()){
		ofLogNotice("ofxCamMovementOsc", "No camera found. Exiting now.");
		ofExit(EXIT_SUCCESS);
		return;
	}
	else {
		ofLogNotice("ofxCamMovementOsc") << "Camera successfully initialised.";
	}
	
	fb.setPyramidScale(.5);
	fb.setNumLevels(1);
	//fb.setWindowSize(64);
	fb.setWindowSize(32);
	fb.setNumIterations(1);
	fb.setPolyN(5);
	fb.setPolySigma(2.f);
	fb.setUseGaussian(false);
	//flowWindowDim = ofVec2f(fb.getWidth(), fb.getHeight());
	
	ofLogNotice("ofxCamMovementOsc") << "Setting up an OSC communication on " << HOST << ":" << PORT;
	// open an outgoing connection to HOST:PORT
	if( sender.setup(HOST, PORT) ){
		ofLogNotice("ofxCamMovementOsc") << "OSC server successfilly started.";
	}
	else {
		ofLogNotice("ofxCamMovementOsc") << "OSC connection failed.";
	}
	
	/// limit framerate
	ofSetFrameRate(24);
	
	ofLogNotice("ofxCamMovementOsc") << "Setup Complete. Running now...";
}

void ofApp::update(){
	camera.update();
	
	if(camera.isFrameNew()) {

		// you can use Flow polymorphically
		fb.calcOpticalFlow(camera);
		
		flowWindowDim = ofVec2f(fb.getWidth(), fb.getHeight());
		
		curFlow = fb.getTotalFlow() / (flowWindowDim*flowWindowDim);
		
		// stream data
		if(sender.getSettings().broadcast){
			ofxOscMessage m;
			m.setAddress("/cam/");
			m.addFloatArg(curFlow.x);
			m.addFloatArg(curFlow.y);
			sender.sendMessage(m, false);
		}
	}
}

void ofApp::draw(){
	if(false){
		ofPushMatrix();
		ofTranslate(ofGetWidth()*.5f, 0);
		ofDrawRectangle(0.f, 0.f, curFlow.x*(ofGetWidth()*.5), 20.f);
		ofTranslate(0,20);
		ofDrawBitmapString(curFlow, 0, 20);
		ofPopMatrix();
		
		ofPushMatrix();
		ofTranslate(250, 100);
		camera.draw(0,0,640,480);
		fb.draw(0,0,640,480);
		ofDrawBitmapStringHighlight(ofToString((int) ofGetFrameRate()) + "fps", 10, 20);
		ofPopMatrix();
		//gui.draw();
	}
}

void ofApp::exit(){
	// properly release interfaces
	if( camera.isInitialized() ) camera.close();
	sender.clear();
	
	ofLogNotice("ofxCamMovementOsc") << "Devices and interfaces were released. Exiting now.";
}

#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOsc.h"

// SETUP !
// send host (aka ip address)
//#define HOST "10.188.255.255" // multicast
#define HOST "localhost" // localhost
// send port
#define PORT 12200

// Cam settings
#define CAM_W 320
#define CAM_H 240
#define CAM_DEVICE 0 // first camera, see console output for exact id

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	ofVideoGrabber camera;
	
	ofxCv::FlowFarneback fb;
	
	ofVec2f flowWindowDim, curFlow;
	
	ofxOscSender sender;
};


#include "testApp.h"

void testApp::setup() {
	settings.setup('a', "App_Settings");
	settings.addMonitor(&ofGetFrameRate, "FPS");
	settings.addProperty(this, &testApp::getMode,
						 this, &testApp::setMode,
						 "Mode",
						 this, &testApp::getModeMin,
						 this, &testApp::getModeMax,
						 this, &testApp::getModeStep,
						 (int)APP_CAMERA_MODE);
	
	timbre.setup();
	timbreSettings.setup(&timbre);	
}

void testApp::update() {
	switch (this->mode) {
		case APP_VIDEO_MODE:
			videoInput.idleMovie();
			timbre.update(videoInput);
			break;
		case APP_CAMERA_MODE:
			cameraInput.update();
			if(cameraInput.isFrameNew()) timbre.update(cameraInput);
			break;
	}
}

void testApp::draw() {
	ofSetColor(255);
	timbre.draw();
	settings.draw(0,0);
	timbreSettings.draw(0,0);
}

void testApp::keyPressed(int key) {
	settings.keyPressed(key);
	timbreSettings.keyPressed(key);
}

void testApp::setMode(int mode)
{
	switch (this->mode) {
		case APP_VIDEO_MODE:
			videoInput.close();
			break;
		case APP_CAMERA_MODE:
			cameraInput.close();
			break;
	}
	this->mode = mode;
	switch (this->mode) {
		case APP_VIDEO_MODE:
			videoInput.loadMovie("source.m4v");
			videoInput.play();
			videoInput.setLoopState(OF_LOOP_NORMAL);
			break;
		case APP_CAMERA_MODE:
			cameraInput.initGrabber(640, 480);
			break;
	}
}
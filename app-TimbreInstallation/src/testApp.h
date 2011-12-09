#pragma once

#include "ofMain.h"
#include "TTimbre.h"
#include "TSettings.h"
#include "ofxKeyboardSettings.h"

enum AppMode {
	APP_VIDEO_MODE = 0,
	APP_CAMERA_MODE
};

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	void	setMode(int mode);
	int		getMode(){return mode;};
	int		getModeMin(){return APP_VIDEO_MODE;};
	int		getModeMax(){return APP_CAMERA_MODE;};
	int		getModeStep(){return 1;};
	
private:
	TTimbre			timbre;
	TSettings		timbreSettings;
	ofVideoGrabber	cameraInput;
	ofVideoPlayer	videoInput;
	
	float settingsX, settingsY;
	ofxKeyboardSettings settings;
	
	int		mode;

};

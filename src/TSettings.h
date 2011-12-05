//
//  TSettings.h
//  TimbreInstallation
//
//  Created by Paulo Barcelos on 11/30/11.
//  Copyright (c) 2011 paulobarcelos.com. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "TTimbre.h"
#include "ofxKeyboardSettings.h"
class TSettings {
	
public:
	void				setup(TTimbre* timbre, int accessKey = 't', string label = "Timbre");
	void				keyPressed(int key);	
	void				draw(float x, float y);
	
private:
	
	TTimbre*	timbre;
	ofxKeyboardSettings	settings;	
};
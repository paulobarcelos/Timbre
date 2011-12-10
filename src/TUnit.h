//
//  TTUnit.h
//  TimbreInstallation
//
//  Created by Paulo Barcelos on 11/30/11.
//  Copyright (c) 2011 paulobarcelos.com. All rights reserved.
//

#pragma once

#include "ofMain.h"

class TUnit {
public:
	
	TUnit();
	~TUnit();
	
	void				setup(int width, int height);
	void				update();	
	void				draw(float x, float y);

	ofImage				image;
	bool				active;
};
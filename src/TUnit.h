//
//  TTUnit.h
//  TimbreInstallation
//
//  Created by Paulo Barcelos on 11/30/11.
//  Copyright (c) 2011 paulobarcelos.com. All rights reserved.
//

#pragma once

#include "ofMain.h"

class TTUnit {
	
public:
	
	TTUnit();
	~TTUnit();
	
	void				setup(int width, int height);
	void				update();	
	void				draw();
	
private:
	ofImage				image;
};
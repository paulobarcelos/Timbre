//
//  TTimbre.h
//  TimbreInstallation
//
//  Created by Paulo Barcelos on 11/30/11.
//  Copyright (c) 2011 paulobarcelos.com. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "TUnit.h"
#include "ofxCv.h"

#define TIMBRE_INPUT_WIDTH 960
#define TIMBRE_INPUT_HEIGHT 540

#define TIMBRE_MAX_UNITS 100
#define TIMBRE_UNIT_WIDTH 100
#define TIMBRE_UNIT_HEIGHT 100

class TTimbre {
	
public:
	
	TTimbre();
	~TTimbre();
	
	void	setup();
	void	update(ofImage input);	
	void	update(ofVideoGrabber input);	
	void	update(ofVideoPlayer input);	
	void	draw();
	
	void	resetBackground();
	
	void	setBackgroundThreshold(int backgroundThreshold);
	int		getBackgroundThreshold(){return backgroundThreshold;};
	int		getBackgroundThresholdMin(){return 0;};
	int		getBackgroundThresholdMax(){return 255;};
	int		getBackgroundThresholdStep(){return 1;};
	
	void	setContourMinArea(float contourMinArea);
	float	getContourMinArea(){return contourMinArea;};
	float	getContourMinAreaMin(){return 0;};
	float	getContourMinAreaMax(){return 1;};
	float	getContourMinAreaStep(){return 0.0025;};
	
	void	setContourMaxArea(float contourMaxArea);
	float	getContourMaxArea(){return contourMaxArea;};
	float	getContourMaxAreaMin(){return 0;};
	float	getContourMaxAreaMax(){return 1;};
	float	getContourMaxAreaStep(){return 0.0025;};
	
	void	setWarpWidth(int width);
	int		getWarpWidth(){return warpWidth;};
	int		getWarpWidthMin(){return 0;};
	int		getWarpWidthMax(){return TIMBRE_INPUT_WIDTH;};
	int		getWarpWidthStep(){return 1;};
	void	setWarpHeight(int height);
	int		getWarpHeight(){return warpHeight;};
	int		getWarpHeightMin(){return 0;};
	int		getWarpHeightMax(){return TIMBRE_INPUT_HEIGHT;};
	int		getWarpHeightStep(){return 1;};
	
	void	setWarpTopLeftX(float value){warpPoints[0].x = value;};
	float	getWarpTopLeftX(){return warpPoints[0].x;};
	float	getWarpTopLeftXMin(){return 0;};
	float	getWarpTopLeftXMax(){return TIMBRE_INPUT_WIDTH;};
	float	getWarpTopLeftXStep(){return 1;};	
	void	setWarpTopLeftY(float value){warpPoints[0].y = value;};
	float	getWarpTopLeftY(){return warpPoints[0].y;};
	float	getWarpTopLeftYMin(){return 0;};
	float	getWarpTopLeftYMax(){return TIMBRE_INPUT_HEIGHT;};
	float	getWarpTopLeftYStep(){return 1;};

	void	setWarpTopRightX(float value){warpPoints[1].x = value;};
	float	getWarpTopRightX(){return warpPoints[1].x;};
	float	getWarpTopRightXMin(){return 0;};
	float	getWarpTopRightXMax(){return TIMBRE_INPUT_WIDTH;};
	float	getWarpTopRightXStep(){return 1;};	
	void	setWarpTopRightY(float value){warpPoints[1].y = value;};
	float	getWarpTopRightY(){return warpPoints[1].y;};
	float	getWarpTopRightYMin(){return 0;};
	float	getWarpTopRightYMax(){return TIMBRE_INPUT_HEIGHT;};
	float	getWarpTopRightYStep(){return 1;};
	
	void	setWarpBottomLeftX(float value){warpPoints[3].x = value;};
	float	getWarpBottomLeftX(){return warpPoints[3].x;};
	float	getWarpBottomLeftXMin(){return 0;};
	float	getWarpBottomLeftXMax(){return TIMBRE_INPUT_WIDTH;};
	float	getWarpBottomLeftXStep(){return 1;};	
	void	setWarpBottomLeftY(float value){warpPoints[3].y = value;};
	float	getWarpBottomLeftY(){return warpPoints[3].y;};
	float	getWarpBottomLeftYMin(){return 0;};
	float	getWarpBottomLeftYMax(){return TIMBRE_INPUT_HEIGHT;};
	float	getWarpBottomLeftYStep(){return 1;};
	
	void	setWarpBottomRightX(float value){warpPoints[2].x = value;};
	float	getWarpBottomRightX(){return warpPoints[2].x;};
	float	getWarpBottomRightXMin(){return 0;};
	float	getWarpBottomRightXMax(){return TIMBRE_INPUT_WIDTH;};
	float	getWarpBottomRightXStep(){return 1;};	
	void	setWarpBottomRightY(float value){warpPoints[2].y = value;};
	float	getWarpBottomRightY(){return warpPoints[2].y;};
	float	getWarpBottomRightYMin(){return 0;};
	float	getWarpBottomRightYMax(){return TIMBRE_INPUT_HEIGHT;};
	float	getWarpBottomRightYStep(){return 1;};
	
	
private:
	void	internalUpdate();
	void	allocateImages();
	
	int							warpWidth, warpHeight;
	vector<ofxCv::Point2f>		warpPoints;
	
	ofxCv::RunningBackground	background;
	unsigned int				backgroundThreshold;
	
	ofxCv::ContourFinder		contourFinder;
	float						contourMinArea, contourMaxArea;
	
	ofImage						originalImage;
	ofImage						unwarpedImage;
	ofImage						thresholdedForegroundImage;
	
	vector<TUnit*>				units;	
};
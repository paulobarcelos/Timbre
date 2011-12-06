//
//  TSettings.cpp
//  TimbreInstallation
//
//  Created by Paulo Barcelos on 11/30/11.
//  Copyright (c) 2011 paulobarcelos.com. All rights reserved.
//


#include "TSettings.h"

///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TSettings::setup(TTimbre* timbre, int accessKey, string label){	
	this->timbre = timbre;
	settings.setup(accessKey, label);
	
	// Background reset
	settings.addCallback(timbre, &TTimbre::resetBackground, "Reset_Background");
	
	// Background threshold
	settings.addProperty(timbre, &TTimbre::getBackgroundThreshold,
						 timbre, &TTimbre::setBackgroundThreshold,
						 "background_threshold",
						 timbre, &TTimbre::getBackgroundThresholdMin,
						 timbre, &TTimbre::getBackgroundThresholdMax,
						 timbre, &TTimbre::getBackgroundThresholdStep,
						 (int) 128);
	
	// Warp size
	settings.addProperty(timbre, &TTimbre::getWarpWidth,
						 timbre, &TTimbre::setWarpWidth,
						 "warp_width",
						 timbre, &TTimbre::getWarpWidthMin,
						 timbre, &TTimbre::getWarpWidthMax,
						 timbre, &TTimbre::getWarpWidthStep,
						 (int) TIMBRE_INPUT_WIDTH);
	settings.addProperty(timbre, &TTimbre::getWarpHeight,
						 timbre, &TTimbre::setWarpHeight,
						 "warp_height",
						 timbre, &TTimbre::getWarpHeightMin,
						 timbre, &TTimbre::getWarpHeightMax,
						 timbre, &TTimbre::getWarpHeightStep,
						 (int) TIMBRE_INPUT_HEIGHT);
	
	// Warp Coordinates
	settings.addProperty(timbre, &TTimbre::getWarpTopLeftX,
						 timbre, &TTimbre::setWarpTopLeftX,
						 "warp_top_left_x",
						 timbre, &TTimbre::getWarpTopLeftXMin,
						 timbre, &TTimbre::getWarpTopLeftXMax,
						 timbre, &TTimbre::getWarpTopLeftXStep,
						 (float)0);
	settings.addProperty(timbre, &TTimbre::getWarpTopLeftY,
						 timbre, &TTimbre::setWarpTopLeftY,
						 "warp_top_left_y",
						 timbre, &TTimbre::getWarpTopLeftYMin,
						 timbre, &TTimbre::getWarpTopLeftYMax,
						 timbre, &TTimbre::getWarpTopLeftYStep,
						 (float)0);
	
	settings.addProperty(timbre, &TTimbre::getWarpTopRightX,
						 timbre, &TTimbre::setWarpTopRightX,
						 "warp_top_right_x",
						 timbre, &TTimbre::getWarpTopRightXMin,
						 timbre, &TTimbre::getWarpTopRightXMax,
						 timbre, &TTimbre::getWarpTopRightXStep,
						 (float)TIMBRE_INPUT_WIDTH);
	settings.addProperty(timbre, &TTimbre::getWarpTopRightY,
						 timbre, &TTimbre::setWarpTopRightY,
						 "warp_top_right_y",
						 timbre, &TTimbre::getWarpTopRightYMin,
						 timbre, &TTimbre::getWarpTopRightYMax,
						 timbre, &TTimbre::getWarpTopRightYStep,
						 (float)0);
	
	settings.addProperty(timbre, &TTimbre::getWarpBottomLeftX,
						 timbre, &TTimbre::setWarpBottomLeftX,
						 "warp_bottom_left_x",
						 timbre, &TTimbre::getWarpBottomLeftXMin,
						 timbre, &TTimbre::getWarpBottomLeftXMax,
						 timbre, &TTimbre::getWarpBottomLeftXStep,
						 0.f);
	settings.addProperty(timbre, &TTimbre::getWarpBottomLeftY,
						 timbre, &TTimbre::setWarpBottomLeftY,
						 "warp_bottom_left_y",
						 timbre, &TTimbre::getWarpBottomLeftYMin,
						 timbre, &TTimbre::getWarpBottomLeftYMax,
						 timbre, &TTimbre::getWarpBottomLeftYStep,
						 (float)TIMBRE_INPUT_HEIGHT);
	
	settings.addProperty(timbre, &TTimbre::getWarpBottomRightX,
						 timbre, &TTimbre::setWarpBottomRightX,
						 "warp_bottom_right_x",
						 timbre, &TTimbre::getWarpBottomRightXMin,
						 timbre, &TTimbre::getWarpBottomRightXMax,
						 timbre, &TTimbre::getWarpBottomRightXStep,
						 (float)TIMBRE_INPUT_WIDTH);
	settings.addProperty(timbre, &TTimbre::getWarpBottomRightY,
						 timbre, &TTimbre::setWarpBottomRightY,
						 "warp_bottom_right_y",
						 timbre, &TTimbre::getWarpBottomRightYMin,
						 timbre, &TTimbre::getWarpBottomRightYMax,
						 timbre, &TTimbre::getWarpBottomRightYStep,
						 (float)TIMBRE_INPUT_HEIGHT);
}
///////////////////////////////////////////////////////////////////////////////////
// keyPressed ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TSettings::keyPressed(int key){
	settings.keyPressed(key);
}
///////////////////////////////////////////////////////////////////////////////////
// draw ---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TSettings::draw(float x, float y){
	settings.draw(x, y);
}
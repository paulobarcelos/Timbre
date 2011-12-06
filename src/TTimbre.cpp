//
//  TTimbre.cpp
//  TimbreInstallation
//
//  Created by Paulo Barcelos on 11/30/11.
//  Copyright (c) 2011 paulobarcelos.com. All rights reserved.
//


#include "TTimbre.h"

using namespace ofxCv;
using namespace cv;

///////////////////////////////////////////////////////////////////////////////////
// Constructor --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
TTimbre::TTimbre(){
}
///////////////////////////////////////////////////////////////////////////////////
// Destructor --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
TTimbre::~TTimbre(){
}
///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::setup(){
	contourFinder.setMinAreaRadius(10);
	contourFinder.setMaxAreaRadius(150);
	
	warpWidth = TIMBRE_INPUT_WIDTH;
	warpHeight = TIMBRE_INPUT_HEIGHT;
	
	allocateImages();
	
	warpPoints.resize(4);
}
///////////////////////////////////////////////////////////////////////////////////
// update -------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::update(ofImage input){
	originalImage = input;
	internalUpdate();
}
void TTimbre::update(ofVideoGrabber input){
	originalImage.setFromPixels(input.getPixels(), input.getWidth(),  input.getHeight(), OF_IMAGE_COLOR);
	internalUpdate();
}
void TTimbre::update(ofVideoPlayer input){
	originalImage.setFromPixels(input.getPixels(), input.getWidth(),  input.getHeight(), OF_IMAGE_COLOR);
	internalUpdate();
}
///////////////////////////////////////////////////////////////////////////////////
// allocateImages -----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::allocateImages(){
	unwarpedImage.allocate(warpWidth, warpHeight, OF_IMAGE_COLOR);
	background.reset();
}
///////////////////////////////////////////////////////////////////////////////////
// internalUpdate -----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::internalUpdate(){

	// Make sure the input image is in the corect size
	if(originalImage.getWidth() != TIMBRE_INPUT_WIDTH || originalImage.getHeight() != TIMBRE_INPUT_HEIGHT)
		originalImage.resize(TIMBRE_INPUT_WIDTH, TIMBRE_INPUT_HEIGHT);
	
	// Unwarp the image to the boundaries of the table
	unwarpPerspective(originalImage, unwarpedImage, warpPoints);
	unwarpedImage.update();
	
	/*originalMat = toCv(originalImage);
	if(originalMat.channels() == 1) {		
		greyImage.clone(originalImage);
	} else if(originalMat.channels() == 3) {
		ofxCv::convertColor(originalImage, greyImage, CV_RGB2GRAY);
	} else if(originalMat.channels() == 4) {
		ofxCv::convertColor(originalImage, greyImage, CV_RGBA2GRAY);
	}
	greyImage.update();*/
	
	background.update(unwarpedImage, thresholdedForegroundImage);
	thresholdedForegroundImage.update();
	contourFinder.findContours(contourImage);	
}
///////////////////////////////////////////////////////////////////////////////////
// draw ---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::draw(){
	ofPushStyle();
	ofPushMatrix();
		ofScale(0.5f, 0.5f);
		ofTranslate(0, 0);
		ofSetHexColor(0xffffff);
		originalImage.draw(0,0);
		ofSetHexColor(0xff0000);
		ofCircle(warpPoints[0].x, warpPoints[0].y, 10);
		ofCircle(warpPoints[1].x, warpPoints[1].y, 10);
		ofCircle(warpPoints[2].x, warpPoints[2].y, 10);
		ofCircle(warpPoints[3].x, warpPoints[3].y, 10);
	ofPopMatrix();
	ofPopStyle();
	
	ofPushStyle();
	ofPushMatrix();
		ofScale(0.5f, 0.5f);
		ofTranslate(TIMBRE_INPUT_WIDTH, 0);
		ofSetHexColor(0xffffff);
		unwarpedImage.draw(0,0);
	ofPopMatrix();
	ofPopStyle();
	
	ofPushStyle();
	ofPushMatrix();
		ofTranslate(0, TIMBRE_INPUT_HEIGHT/2);
		ofSetHexColor(0xff0000);
		thresholdedForegroundImage.draw(0,0);
		ofSetHexColor(0xffffff);
		contourFinder.draw();
	ofPopMatrix();
	ofPopStyle();
		
		
	
		//unwarpedImage.draw(0,TIMBRE_INPUT_HEIGHT/4,TIMBRE_INPUT_WIDTH/4, TIMBRE_INPUT_HEIGHT/4);
		//greyImage.draw(TIMBRE_INPUT_WIDTH/4,0,TIMBRE_INPUT_WIDTH/4, TIMBRE_INPUT_HEIGHT/4);
		//contourImage.draw(TIMBRE_INPUT_WIDTH/2,0,TIMBRE_INPUT_WIDTH/4, TIMBRE_INPUT_HEIGHT/4);
	/*ofPushMatrix();
	ofScale(0.25, 0.25);
		ofTranslate(TIMBRE_INPUT_WIDTH/2, 0);
		ofSetColor(redColor);
		contourFinder.draw();
	ofPopMatrix();*/
}
///////////////////////////////////////////////////////////////////////////////////
// resetBackground ----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::resetBackground(){
	background.reset();
}
///////////////////////////////////////////////////////////////////////////////////
// setBackgroundThreshold ---------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::setBackgroundThreshold(int threshold){
	this->threshold = threshold;
	background.setThresholdValue(threshold);
}
///////////////////////////////////////////////////////////////////////////////////
// setWarpWidth -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::setWarpWidth(int width){
	warpWidth = width;
	allocateImages();
}
///////////////////////////////////////////////////////////////////////////////////
// setWarpHeight ------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::setWarpHeight(int height){
	warpHeight = height;
	allocateImages();
}
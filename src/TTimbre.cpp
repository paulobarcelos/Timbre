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
	
	units.resize(TIMBRE_MAX_UNITS);
	for(int i = 0; i < TIMBRE_MAX_UNITS; i++){
		TUnit * unit = new TUnit();
		unit->setup(TIMBRE_UNIT_WIDTH, TIMBRE_UNIT_HEIGHT);
		units[i] = unit;
	}
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
	contourFinder.findContours(thresholdedForegroundImage);
	
	int n = contourFinder.size();
	for(int i = 0; i < TIMBRE_MAX_UNITS; i++) {
		bool isActive = false;
		// Post logic to evalute if countour is valid
		if (i < n) {
			isActive = true;
		}
		if (isActive) {
			// smallest rectangle that fits the contour
			ofPolyline minAreRect = toOf(contourFinder.getMinAreaRect(i));
			// convert the vertices to ofPoin2f vector
			vector<ofPoint> unitWarpOfPoints =  minAreRect.getVertices();
			vector<Point2f> unitWarpPoints;
			unitWarpPoints.resize(4);
			unitWarpPoints[0].x = unitWarpOfPoints[0].x;
			unitWarpPoints[0].y = unitWarpOfPoints[0].y;
			unitWarpPoints[1].x = unitWarpOfPoints[1].x;
			unitWarpPoints[1].y = unitWarpOfPoints[1].y;
			unitWarpPoints[2].x = unitWarpOfPoints[2].x;
			unitWarpPoints[2].y = unitWarpOfPoints[2].y;
			unitWarpPoints[3].x = unitWarpOfPoints[3].x;
			unitWarpPoints[3].y = unitWarpOfPoints[3].y;
						
			unwarpPerspective(unwarpedImage, units[i]->image, unitWarpPoints);
			units[i]->image.update();
			
			units[i]->active = true;
		}
		else{
			units[i]->active = false;
		}
	}

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
		ofFill();
		ofCircle(warpPoints[0].x, warpPoints[0].y, 2);
		ofCircle(warpPoints[1].x, warpPoints[1].y, 2);
		ofCircle(warpPoints[2].x, warpPoints[2].y, 2);
		ofCircle(warpPoints[3].x, warpPoints[3].y, 2);
		ofNoFill();
		ofCircle(warpPoints[0].x, warpPoints[0].y, 20);
		ofCircle(warpPoints[1].x, warpPoints[1].y, 20);
		ofCircle(warpPoints[2].x, warpPoints[2].y, 20);
		ofCircle(warpPoints[3].x, warpPoints[3].y, 20);
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
	
	ofPushStyle();
	ofPushMatrix();
		ofTranslate(TIMBRE_INPUT_WIDTH, 0);
		ofSetHexColor(0xffffff);
		int activeIndex = 0;
		for(int i = 0; i < TIMBRE_MAX_UNITS; i++) {
			if (units[i]->active) {
				units[i]->draw((float)activeIndex * (float)TIMBRE_UNIT_WIDTH, 0);
				activeIndex++;
			}
		}
	ofPopMatrix();
	ofPopStyle();
	
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
void TTimbre::setBackgroundThreshold(int backgroundThreshold){
	this->backgroundThreshold = backgroundThreshold;
	background.setThresholdValue(backgroundThreshold);
}
///////////////////////////////////////////////////////////////////////////////////
// setContourMinArea --------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::setContourMinArea(float contourMinArea){
	this->contourMinArea = contourMinArea;
	contourFinder.setMinAreaNorm(contourMinArea);
}
///////////////////////////////////////////////////////////////////////////////////
// setContourMaxArea --------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void TTimbre::setContourMaxArea(float contourMaxArea){
	this->contourMaxArea = contourMaxArea;
	contourFinder.setMaxAreaNorm(contourMaxArea);
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
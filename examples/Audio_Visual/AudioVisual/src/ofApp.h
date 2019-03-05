#pragma once

#include "ofMain.h"
#include "ofxProcessFFT.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
  
    ProcessFFT fft; 
		int ledVals[3];
  
    ofSerial serial; 
};

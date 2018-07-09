#pragma once


#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
  
    void onSliderEvent(ofxDatGuiSliderEvent e);
  
private:
    const int defaultBrightness = 50;
    
    // An instance of the serial object. One instance is needed for each active
    // serial connection.
    ofSerial serial;

    // Dat GUI.
    ofxDatGui *gui;
  
    // Themes
    vector<ofxDatGuiTheme*> themes;
    int tIndex = 6;
  
    // Arrays to hold LED values. 
    int led1[3]; int led2[3]; int led3[3];
};

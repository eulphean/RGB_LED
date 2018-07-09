#include "ofApp.h"

void ofApp::setup()
{
    ofBackground(0);
    
    // Give Arduino port name as the first parameter.
    serial.setup("/dev/cu.usbmodem1411", 9600);
  
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
  
    // LED1
    gui->addLabel("LED 1 (master)");
    gui->addSlider("LED1-Red", 0, 255, defaultBrightness);
    gui->addSlider("LED1-Green", 0, 255, 0);
    gui->addSlider("LED1-Blue", 0, 255, 0);
    for (int i = 0; i < 5; i++) {
      gui->addBreak();
    }
  
    // LED2
    gui->addLabel("LED 2 (master)");
    gui->addSlider("LED2-Red", 0, 255, 0);
    gui->addSlider("LED2-Green", 0, 255, defaultBrightness);
    gui->addSlider("LED2-Blue", 0, 255, 0);
    for (int i = 0; i < 5; i++) {
      gui->addBreak();
    }
  
    // LED3
    gui->addLabel("LED 3 (slave)");
    gui->addSlider("LED3-Red", 0, 255, 0);
    gui->addSlider("LED3-Green", 0, 255, 0);
    gui->addSlider("LED3-Blue", 0, 255, defaultBrightness);
  
    // Add a callback for the slider.
    gui->onSliderEvent(this, &ofApp::onSliderEvent);

    // Load GUI themes.
    themes = {  new ofxDatGuiTheme(true),
                new ofxDatGuiThemeSmoke(),
                new ofxDatGuiThemeWireframe(),
                new ofxDatGuiThemeMidnight(),
                new ofxDatGuiThemeAqua(),
                new ofxDatGuiThemeCharcoal(),
                new ofxDatGuiThemeAutumn(),
                new ofxDatGuiThemeCandy()
    };
  
    gui->setTheme(themes[tIndex]);
    gui->addHeader("RGB LED Interactive", false);
  
    // Initialize LED color values.
    led1[0] = defaultBrightness; led1[1] = 0; led1[2] = 0;
    led2[0] = 0; led2[1] = defaultBrightness; led2[2] = 0;
    led3[0] = 0; led3[1] = 0; led3[2] = defaultBrightness;
}


void ofApp::update()
{
    gui->setWidth(ofGetWidth());
    gui->setPosition(0, ofGetHeight()/2 - gui->getHeight()/2);
  
    // Send our LED values.
    std::string writeBuffer;
    
    // Create a buffer of the type
    // 50,50,50-50,50,50-50,50,50 [Led1, Led2, Led3] - Brightness values.
    writeBuffer += ofToString(led1[0]);
    writeBuffer += ",";
    writeBuffer += ofToString(led1[1]);
    writeBuffer += ",";
    writeBuffer += ofToString(led1[2]);
    writeBuffer += "-";
    writeBuffer += ofToString(led2[0]);
    writeBuffer += ",";
    writeBuffer += ofToString(led2[1]);
    writeBuffer += ",";
    writeBuffer += ofToString(led2[2]);
    writeBuffer += "-";
    writeBuffer += ofToString(led3[0]);
    writeBuffer += ",";
    writeBuffer += ofToString(led3[1]);
    writeBuffer += ",";
    writeBuffer += ofToString(led3[2]);
    writeBuffer += "\n";
  
    cout << writeBuffer << endl;

    serial.writeBytes(writeBuffer.data(), writeBuffer.size());
}


void ofApp::draw()
{
}

void ofApp::keyPressed(int key)
{
  if (key == ' ') {
    tIndex = tIndex < themes.size()-1 ? tIndex+1 : 0;
    gui->setTheme(themes[tIndex]);
  }
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
  string label = e.target->getLabel();
  
  if (label == "LED1-Red") {
    led1[0] = e.value;
  }
  
  if (label == "LED1-Green") {
    led1[1] = e.value;
  }
  
  if (label == "LED1-Blue") {
    led1[2] = e.value;
  }
  
  if (label == "LED2-Red") {
    led2[0] = e.value;
  }
  
  if (label == "LED2-Green") {
    led2[1] = e.value;
  }
  
  if (label == "LED2-Blue") {
    led2[2] = e.value;
  }
  
  if (label == "LED3-Red") {
    led3[0] = e.value;
  }
  
  if (label == "LED3-Green") {
    led3[1] = e.value;
  }
  
  if (label == "LED3-Blue") {
    led3[2] = e.value;
  }
}

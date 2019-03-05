#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetVerticalSync(true);
  ofSetFrameRate(60);
  fft.setup();
  fft.setNormalize(true); // Normalize all fft values.
  
  // Serial setup
  serial.setup("/dev/cu.usbmodem1421", 9600);
}

//--------------------------------------------------------------
void ofApp::update(){
  fft.update();
  
  // Read High, Mid, and Low sounds from processFFT and
  // map them between 0-255 for Red (high), Green (mid), and Blue (low)
  auto high = fft.getHighVal();
  auto mid = fft.getMidVal();
  auto low = fft.getLowVal();
  
  // Map 0 => Red, 1=>Green 2=>Blue
  ledVals[0] = ofMap(high, 0, 1, 0, 255, true);
  ledVals[1] = ofMap(mid, 0, 1, 0, 255, true);
  ledVals[2] = ofMap(low, 0, 1, 0, 255, true);
  
  //cout << "Red: "  << ledVals[0] << ", Green: " << ledVals[1] << ", Blue: " << ledVals[2] << "\n";
  
  // Send these values over to Arduino
  std::string writeBuffer;
  writeBuffer += ofToString(ledVals[0]);
  writeBuffer += ",";
  writeBuffer += ofToString(ledVals[1]);
  writeBuffer += ",";
  writeBuffer += ofToString(ledVals[2]);
  writeBuffer += "\n";
  
  cout << writeBuffer << endl;
  
  // Write data.
  serial.writeBytes(writeBuffer.data(), writeBuffer.size());
}

//--------------------------------------------------------------
void ofApp::draw(){
  fft.drawDebug();
  fft.drawBars();
  
  ofNoFill();
  ofDrawRectangle(824, 0, 200, 200);
  ofDrawRectangle(824, 200, 200, 200);
  ofDrawRectangle(824, 400, 200, 200);
  ofDrawRectangle(824, 600, 200, 200);

  fft.drawHistoryGraph(ofPoint(824,0), LOW);
  fft.drawHistoryGraph(ofPoint(824,200),MID );
  fft.drawHistoryGraph(ofPoint(824,400),HIGH );
  fft.drawHistoryGraph(ofPoint(824,600),MAXSOUND );
  ofDrawBitmapString("LOW",850,20);
  ofDrawBitmapString("HIGH",850,420);
  ofDrawBitmapString("MID",850,220);
  ofDrawBitmapString("MAX VOLUME",850,620);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  // Turn on/turn off audio reactive sound
  
}

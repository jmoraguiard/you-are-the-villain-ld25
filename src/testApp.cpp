#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofEnableAlphaBlending();
	ofSetBackgroundColor(0, 64, 192);

	game_manager_.setup();

}

//--------------------------------------------------------------
void testApp::update(){

	game_manager_.update();

}

//--------------------------------------------------------------
void testApp::draw(){

	game_manager_.draw(false);

	//ofSetColor(255, 255, 255);
	//ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 35);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	game_manager_.keyPressed(key);

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

	game_manager_.keyReleased(key);

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

	game_manager_.mouseMoved(x, y);

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	game_manager_.mouseDragged(x, y, button);

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	game_manager_.mousePressed(x, y, button);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	game_manager_.mouseReleased(x, y, button);

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
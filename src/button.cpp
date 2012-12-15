#include "button.h"

//--------------------------------------------------------------
ButtonClass::ButtonClass(){

}

//--------------------------------------------------------------
ButtonClass::~ButtonClass(){

}

//--------------------------------------------------------------
void ButtonClass::setup(string text, int text_size, ofVec2f pos, ofVec2f size) {

	text_font_.loadFont("visitor1.ttf", text_size, true);

	text_to_display_ = text;

	position_ = pos;
	size_ = size;

	text_position_.x = size_.x/2 - text_font_.getStringBoundingBox(text_to_display_, 0, 0).width/2;
	text_position_.y = size_.y/2 - text_font_.getStringBoundingBox(text_to_display_, 0, 0).height/2;

}

//--------------------------------------------------------------
bool ButtonClass::isUnderPoint(ofVec2f pos) {
	
	if(pos.x > position_.x && pos.x < position_.x+size_.x && pos.y > position_.y && pos.y < position_.y+size_.y)
		return true;
	return false;

}

//--------------------------------------------------------------
void ButtonClass::draw() {

	ofPushStyle();
	ofSetColor(255, 0, 0);
		ofRect(position_.x, position_.y, size_.x, size_.y);
		ofSetColor(255, 255, 255);
		text_font_.drawString(text_to_display_, position_.x+text_position_.x, position_.y+text_position_.y*2);
	ofPopStyle();

};
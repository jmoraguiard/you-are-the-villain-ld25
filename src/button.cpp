#include "button.h"

//--------------------------------------------------------------
ButtonClass::ButtonClass(){

}

//--------------------------------------------------------------
ButtonClass::~ButtonClass(){

}

//--------------------------------------------------------------
void ButtonClass::setup(string text, int text_size, ofVec2f pos, ofVec2f size, int time, bool active) {

	text_font_.loadFont("visitor1.ttf", text_size, true);

	text_to_display_ = text;

	position_ = pos;
	size_ = size;

	time_to_regenerate_ = time;

	if(active){
		last_time_used_ = ofGetElapsedTimeMillis()-time_to_regenerate_;
		percentage_completed_ = 1;
	}else{
		last_time_used_ = ofGetElapsedTimeMillis();
		percentage_completed_ = 0;
	}

	text_position_.x = size_.x/2 - text_font_.getStringBoundingBox(text_to_display_, 0, 0).width/2;
	text_position_.y = size_.y/2 - text_font_.getStringBoundingBox(text_to_display_, 0, 0).height/2;

	selected_ = false;

}

//--------------------------------------------------------------
bool ButtonClass::isUnderPoint(ofVec2f pos) {
	
	if(pos.x > position_.x && pos.x < position_.x+size_.x && pos.y > position_.y && pos.y < position_.y+size_.y)
		return true;
	return false;

}

//--------------------------------------------------------------
void ButtonClass::update(){

	if(percentage_completed_ < 1)
		percentage_completed_ = (ofGetElapsedTimeMillis()-last_time_used_)/time_to_regenerate_;
	else
		percentage_completed_ = 1;

}

//--------------------------------------------------------------
void ButtonClass::draw() {

	ofPushStyle();
		if(selected_)
			ofSetColor(255, 255, 255);
		else
			ofSetColor(0, 0, 0);
		ofRect(position_.x, position_.y, size_.x, size_.y);
		ofSetColor(255, 0, 0);
		ofRect(position_.x+3, position_.y+3, size_.x-6, size_.y-6);
		ofSetColor(0, 0, 0);
		text_font_.drawString(text_to_display_, position_.x+text_position_.x, position_.y+text_position_.y*2);
		ofSetColor(0, 0, 0, 128);
		ofRect(position_.x+3, position_.y+3, size_.x-6, (size_.y-6)-((size_.y-6)*percentage_completed_));
	ofPopStyle();

};

//--------------------------------------------------------------
void ButtonClass::setSelected(bool selected){
	selected_ = selected;
}

//--------------------------------------------------------------
void ButtonClass::setUsed(){

	percentage_completed_ = 0;
	last_time_used_ = ofGetElapsedTimeMillis();

}

//--------------------------------------------------------------
bool ButtonClass::canBeUsed(){

	return percentage_completed_ == 1;
}

//--------------------------------------------------------------
float ButtonClass::getPercentage(){
	return percentage_completed_;
}

//--------------------------------------------------------------
void ButtonClass::setPercentage(float percentage){

	int fake_time = (percentage_completed_-(percentage_completed_-percentage))*time_to_regenerate_;
	if(percentage > 0.1){
		percentage_completed_ = percentage;
		last_time_used_ = ofGetElapsedTimeMillis()-fake_time;
	}else{
		percentage_completed_ = 0;
		last_time_used_ = ofGetElapsedTimeMillis();
	}

}
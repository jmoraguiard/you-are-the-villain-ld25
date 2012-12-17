#include "explosion.h"

Explosion::Explosion(){

	text_font_.loadFont("visitor1.ttf", 20, true);

	position_.set(0, 0);

	partial_millis_ = 0;
	maximum_radius_ = 0;

	partial_millis_ = 0;
	total_millis_ = 0;

}

Explosion::~Explosion(){

}

void Explosion::setup(ofVec2f pos, int total_millis, int radius, int id, ofVec2f combo){

	explosion_id_ = id;

	combo_ = combo;
	position_ = pos;

	initial_millis_ = ofGetElapsedTimeMillis();
	total_millis_ = total_millis;
	maximum_radius_ = radius;

}

bool Explosion::update(){

	partial_millis_ = ofGetElapsedTimeMillis() - initial_millis_;

	if(partial_millis_ >= 0 && partial_millis_ <= total_millis_/2){
		partial_radius_ = (maximum_radius_*partial_millis_)/(total_millis_/2);
	}else{
		if(partial_millis_ >= total_millis_/2 && partial_millis_ <= total_millis_){
			partial_radius_ = maximum_radius_-((maximum_radius_*(partial_millis_-total_millis_/2))/(total_millis_/2));
		}else{
			return true;
		}
	}

	return false;

}

void Explosion::draw(bool air){

	ofSetColor(0, 0, 0);
	ofCircle(position_.x, position_.y, partial_radius_+2);

	if(air)
		ofSetColor(255, 64, 32);
	else
		ofSetColor(192, 0, 0);
	ofCircle(position_.x, position_.y, partial_radius_);

	ofSetColor(0, 0, 0);
	ofPushMatrix();
		ofTranslate(position_.x, position_.y);
		ofScale(partial_radius_/8, partial_radius_/8);
		text_font_.drawString("x"+ofToString(combo_.x), 0, 0);
	ofPopMatrix();

}

bool Explosion::isTouchingExplosion(ofVec2f pos){

	float dist = sqrt(pow(position_.x-pos.x,2)+pow(position_.y-pos.y,2));
	return dist <= partial_radius_+10;

}
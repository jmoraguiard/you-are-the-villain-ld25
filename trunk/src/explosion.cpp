#include "explosion.h"

Explosion::Explosion(){

	position_.set(0, 0);

	partial_millis_ = 0;
	maximum_radius_ = 0;

	partial_millis_ = 0;
	total_millis_ = 0;

}

Explosion::~Explosion(){

}

void Explosion::setup(ofVec2f pos, int total_millis, int radius){

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

void Explosion::draw(){

	ofSetColor(255, 0, 0);
	ofCircle(position_.x, position_.y, partial_radius_);
	ofSetColor(0, 0, 0);
	ofCircle(position_.x, position_.y, 1);

}

bool Explosion::isTouchingExplosion(ofVec2f pos){

	float dist = sqrt(pow(position_.x-pos.x,2)+pow(position_.y-pos.y,2));
	return dist <= partial_radius_;

}
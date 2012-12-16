#include "plane.h"

#include "ofMain.h"

//------------------------------------------------------------
Plane::Plane(){
	setup(0,0,0,0, ofVec2f(0,0));
}

//------------------------------------------------------------
void Plane::setup(float px, float py, float vx, float vy, ofVec2f end_point){

    position_.set(px,py);
	previous_position_.set(px,py);
	velocity_.set(vx,vy);
	heading_position_ = end_point;
	plane_.loadImage("plane.png");

}

//------------------------------------------------------------
void Plane::update(){

	float dirx = (heading_position_.x - position_.x);
	float diry = (heading_position_.y - position_.y);
	int magnitude = sqrt(pow(dirx, 2)+pow(diry, 2));
	velocity_.x = (dirx/magnitude)*0.6;
	velocity_.y = (diry/magnitude)*0.6;

	previous_position_ = position_;
	velocity_ = velocity_ + acceleration_;
	position_ = position_ + velocity_;

}

//------------------------------------------------------------
void Plane::draw(){

	float radians = atan2(position_.y-previous_position_.y, position_.x-previous_position_.x);
	float degrees = (radians/PI)*180;

	ofSetColor(255, 255, 255, 255);
	ofPushMatrix();
		ofTranslate(position_.x, position_.y);
		ofRotateZ(degrees-90);
		/*glBegin(GL_TRIANGLES);
			glVertex2f(-10, -10);
			glVertex2f(0, 10);
			glVertex2f(10, -10);
		glEnd();*/
		plane_.draw(-10, 20, 20, -35);
	ofPopMatrix();

}

//------------------------------------------------------------
bool Plane::getHasArrived(){


	float x = abs(position_.x - heading_position_.x);
	float y = abs(position_.y - heading_position_.y);
	float dist = sqrt(pow(x, 2)+pow(y, 2));

	if(dist < 2){
		return true;
	}
	return false;

}

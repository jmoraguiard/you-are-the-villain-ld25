#include "ship.h"

#include "ofMain.h"

//------------------------------------------------------------
Ship::Ship(){
	setup(0,0,0,0);
	damping_ = 0.05f;
}

//------------------------------------------------------------
void Ship::resetForce(){
    // we reset the forces every frame
    acceleration_.set(0,0);
}

//------------------------------------------------------------
void Ship::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    acceleration_.x = acceleration_.x + x;
    acceleration_.y = acceleration_.y + y;
}

//------------------------------------------------------------
void Ship::addDampingForce(){
	
	// the usual way to write this is  velocity_ *= 0.99
	// basically, subtract some part of the velocity_ocity 
	// damping is a force operating in the oposition_ite direction of the 
	// velocity_ocity vector
	
    acceleration_.x = acceleration_.x - velocity_.x * damping_;
    acceleration_.y = acceleration_.y - velocity_.y * damping_;
}

//------------------------------------------------------------
void Ship::setup(float px, float py, float vx, float vy){
    position_.set(px,py);
	previous_position_.set(px,py);
	velocity_.set(vx,vy);
}

//------------------------------------------------------------
void Ship::update(){
	previous_position_ = position_;
	velocity_ = velocity_ + acceleration_;
	position_ = position_ + velocity_;
}

//------------------------------------------------------------
void Ship::draw(){

	//ofSetColor(0, 130, 130, 200);
    //ofCircle(position_.x, position_.y, 3);

	float radians = atan2(position_.y-previous_position_.y, position_.x-previous_position_.x);
	float degrees = (radians/PI)*180;

	ofSetColor(0, 0, 0, 200);
	ofPushMatrix();
		ofTranslate(position_.x, position_.y);
		ofRotateZ(degrees-90);
		glBegin(GL_TRIANGLES);
			glVertex2f(-10, -10);
			glVertex2f(0, 10);
			glVertex2f(10, -10);
		glEnd();
	ofPopMatrix();

	//ofSetColor(255, 0, 0);
	//ofLine(position_.x, position_.y, previous_position_.x, previous_position_.y);

}


//------------------------------------------------------------
void Ship::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (position_.x > maxx){
		position_.x = maxx; // move to the edge, (important!)
		velocity_.x *= -1;
		bDidICollide = true;
	} else if (position_.x < minx){
		position_.x = minx; // move to the edge, (important!)
		velocity_.x *= -1;
		bDidICollide = true;
	}
	
	if (position_.y > maxy){
		position_.y = maxy; // move to the edge, (important!)
		velocity_.y *= -1;
		bDidICollide = true;
	} else if (position_.y < miny){
		position_.y = miny; // move to the edge, (important!)
		velocity_.y *= -1;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		velocity_ *= 0.3;
	}
	
}

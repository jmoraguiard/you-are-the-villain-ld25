#ifndef SHIP_H
#define SHIP_H

#include "ofMain.h"

class Ship
{
public:
    Ship();
	virtual ~Ship(){
	
	}

	void setup(float px, float py, float vx, float vy, ofVec2f start_point);
    void update();
    void draw();

    void resetForce();
    void addForce(float x, float y);
    void addDampingForce();
	
	void bounceOffWalls();

	void setDamping(float damp){ damping_ = damp; }
	float getDamping(){ return damping_; }

	bool getAffectedByForces();

	void setPosition(ofVec2f pos){ position_ = pos; }
	ofVec2f getPosition(){ return position_; }
	void setVelocity(ofVec2f vel){ velocity_ = vel; }
	ofVec2f getVelocity(){ return velocity_; }
	void setAcceleration(ofVec2f acc){ acceleration_ = acc; }
	ofVec2f getAcceleration(){ return acceleration_; }
	void setHeadingPosition(ofVec2f pos){ heading_position_ = pos; }
	ofVec2f getHeadingPosition(){ return heading_position_; }

	bool getHasArrived();

private:
	
	ofImage ship_;

	float damping_;

	ofVec2f position_;
	ofVec2f previous_position_;

	ofVec2f heading_position_;

    ofVec2f velocity_;
    ofVec2f acceleration_;

	bool affected_externally_;

};

#endif

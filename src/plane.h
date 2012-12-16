#ifndef PLANE_H
#define PLANE_H

#include "ofMain.h"

class Plane
{
public:
    Plane();
	virtual ~Plane(){
	
	}

	void setup(float px, float py, float vx, float vy, ofVec2f start_point);
    void update();
    void draw();

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
	
	ofVec2f position_;
	ofVec2f previous_position_;

	ofVec2f heading_position_;

    ofVec2f velocity_;
    ofVec2f acceleration_;

};

#endif

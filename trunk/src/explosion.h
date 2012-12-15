#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "ofMain.h"

class Explosion{

public:
	Explosion();
	~Explosion();

	void setup(ofVec2f pos, int total_millis, int radius);
	bool update();
	void draw();

	bool isTouchingExplosion(ofVec2f pos);

private:

	ofVec2f position_;

	float partial_radius_;
	int maximum_radius_;

	float initial_millis_;
	float partial_millis_;
	float total_millis_;

};

#endif
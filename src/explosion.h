#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "ofMain.h"

class Explosion{

public:
	Explosion();
	~Explosion();

	void setup(ofVec2f pos, int total_millis, int radius, int id, ofVec2f combo);
	bool update();
	void draw(bool air);

	bool isTouchingExplosion(ofVec2f pos);

	int getId(){ return explosion_id_; }

private:
	ofVec2f position_;
	ofVec2f combo_;

	ofTrueTypeFont text_font_;

	float partial_radius_;
	int maximum_radius_;

	float initial_millis_;
	float partial_millis_;
	float total_millis_;

	int explosion_id_;

};

#endif
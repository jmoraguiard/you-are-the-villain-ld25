#ifndef ISLAND_H
#define ISLAND_H

#include "ofMain.h"

class Island{

public:
	Island();
	~Island();

	void setup();
	void draw();

	bool isUnderPoint(ofVec2f pos);

private:
	vector<ofVec2f> island_shape_points_;

};

#endif

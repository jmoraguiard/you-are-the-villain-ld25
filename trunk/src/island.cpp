#include "island.h"

//--------------------------------------------------------------
Island::Island(){

}

//--------------------------------------------------------------
Island::~Island(){

}

//--------------------------------------------------------------
void Island::setup() {
	
	island_shape_points_.push_back(ofVec2f(0, 0));
	island_shape_points_.push_back(ofVec2f(720, 0));
	island_shape_points_.push_back(ofVec2f(720, 200));
	island_shape_points_.push_back(ofVec2f(0, 200));
	
}

//--------------------------------------------------------------
bool Island::isUnderPoint(ofVec2f pos) {

	int   i, j = island_shape_points_.size()-1;
	bool  oddNodes = false;

	for (i=0; i<island_shape_points_.size(); i++) {
		ofPoint pointI = island_shape_points_.at(i);
		ofPoint pointJ = island_shape_points_.at(j);
		if (pointI.y<pos.y && pointJ.y>=pos.y || pointJ.y<pos.y && pointI.y>=pos.y) {
			if (pointI.x+(pos.y-pointI.y)/(pointJ.y-pointI.y)*(pointJ.x-pointI.x)<pos.x) {
				oddNodes=!oddNodes;
			}
		}	
		j=i; 
	}
	return oddNodes;

}

//--------------------------------------------------------------
void Island::draw() {

	ofPushStyle();
		ofSetColor(128, 128, 0);
		glBegin(GL_POLYGON);
		for(int i = 0; i < island_shape_points_.size(); i++)
			glVertex2d(island_shape_points_[i].x, island_shape_points_[i].y);
		glEnd();
	ofPopStyle();

};
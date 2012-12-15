#ifndef SEA_H
#define SEA_H

#include "ofMain.h"

class Sea{
	
public:
    Sea();
    ~Sea();
		
	void setup(int width, int height, int columns, int rows);
	
    void clear();
	void propagate(float damping);
    void fadeField(float fadeAmount);
    void randomizeField(float scale);
    void draw();

	ofVec2f	getForceFromPos(float xpos, float ypos);

    void addCurrent(float x, float y, float vx, float vy, float radius, float strength);
	void addVortex(float x, float y, float radius, float strength);
	void addTsunami(float x, float y, float radius, float strength);

	ofPoint& operator [](int _index);
    
    int activeBuffer;

	vector <ofVec2f> sea_;
	ofPoint *buffer[2];

    int sea_columns_;
    int sea_rows_;
	int sea_size_;
	
	int sea_width_;
	int sea_height_;    

};

#endif

#ifndef BUTTON_H
#define BUTTON_H

#include "ofMain.h"

class ButtonClass{

public:
	ButtonClass();
	~ButtonClass();

	void setup(string text, int text_size, ofVec2f pos, ofVec2f size);
	void update();
	void draw();

	bool isUnderPoint(ofVec2f pos);

private:
	ofVec2f position_;
	ofVec2f size_;

	ofTrueTypeFont text_font_;
	string text_to_display_;
	ofVec2f text_position_;

};

#endif

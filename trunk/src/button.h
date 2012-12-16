#ifndef BUTTON_H
#define BUTTON_H

#include "ofMain.h"

class ButtonClass{

public:
	ButtonClass();
	~ButtonClass();

	void setup(string text, int text_size, ofVec2f pos, ofVec2f size, int time, bool active);
	void update();
	void draw();

	void setUsed();
	bool canBeUsed();

	void setSelected(bool selected);

	float getPercentage();
	void setPercentage(float percentage);

	bool isUnderPoint(ofVec2f pos);

private:
	ofVec2f position_;
	ofVec2f size_;

	ofTrueTypeFont text_font_;
	string text_to_display_;
	ofVec2f text_position_;

	int last_time_used_;
	float time_to_regenerate_;
	float percentage_completed_;

	bool selected_;

};

#endif

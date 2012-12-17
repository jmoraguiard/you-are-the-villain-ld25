#include "splashscreenState.h"

#include "tutorialState.h"

SplashscreenState SplashscreenState::splashscreen_state_;

//--------------------------------------------------------------
SplashscreenState::SplashscreenState(){

}

//--------------------------------------------------------------
SplashscreenState::~SplashscreenState(){

}

//--------------------------------------------------------------
SplashscreenState* SplashscreenState::Instance(){
	return (&splashscreen_state_);
}

//--------------------------------------------------------------
void SplashscreenState::setup(GameManager* game_manager){

	buttons_.clear();

	background_.loadImage("background.png");

	title_font_.loadFont("visitor1.ttf", 85, true);
	text_font_.loadFont("visitor1.ttf", 12, true);

	text_to_display_ = "Game created for Ludum Dare 25!\n"; 
	text_to_display_ += "Created by Freakill, December 2012\n";
	text_to_display_ += "Used:\n";
	text_to_display_ += "- openFrameworks\n";
	text_to_display_ += "- Paint .NET\n";
	text_to_display_ += "- SFXR\n";
	text_to_display_ += "'Visitor' Freeware Font by Brian Kent\n";

	ButtonClass button_temp;
	button_temp.setup("START", 70, ofVec2f(341, 306), ofVec2f(342, 156), 5000, true);

	buttons_.push_back(button_temp);

}

//--------------------------------------------------------------
void SplashscreenState::update(GameManager* game_manager){

	for(int i = 0; i < buttons_.size(); i++)
		buttons_[i].update();

}

//--------------------------------------------------------------
void SplashscreenState::draw(GameManager* game_manager, bool debug){

	ofSetColor(128, 128, 128);
	background_.draw(0, 0, 1024, 768);

	ofSetColor(64, 0, 0);
	title_font_.drawString("BAD MOTHA...", 205, 105);
	title_font_.drawString("Nature!", 305, 205);

	ofSetColor(0, 0, 0);
	title_font_.drawString("BAD MOTHA...", 200, 100);
	title_font_.drawString("Nature!", 300, 200);

	ofSetColor(255, 255, 255);
	text_font_.drawString(text_to_display_, 345, 640);

	for(int i = 0; i < buttons_.size(); i++)
		buttons_[i].draw();

	if(debug){
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("Splashscreen State", 20, 20);
	}

}

//--------------------------------------------------------------
void SplashscreenState::keyPressed(GameManager* game_manager, int key){

}

//--------------------------------------------------------------
void SplashscreenState::keyReleased(GameManager* game_manager, int key){

}

//--------------------------------------------------------------
void SplashscreenState::mouseMoved(GameManager* game_manager, int x, int y){

}

//--------------------------------------------------------------
void SplashscreenState::mouseDragged(GameManager* game_manager, int x, int y, int button){

}

//--------------------------------------------------------------
void SplashscreenState::mousePressed(GameManager* game_manager, int x, int y, int button){

	for(int i = 0; i < buttons_.size(); i++){
		if(buttons_[i].isUnderPoint(ofVec2f(x, y)) && buttons_[i].canBeUsed()){
			buttons_[i].setSelected(true);
			changeState(game_manager, TutorialState::Instance());
		}
	}

}

//--------------------------------------------------------------
void SplashscreenState::mouseReleased(GameManager* game_manager, int x, int y, int button){

}

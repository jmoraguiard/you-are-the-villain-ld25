#include "splashscreenState.h"

#include "playState.h"

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

	ButtonClass button_temp;
	button_temp.setup("START", 70, ofVec2f(341, 306), ofVec2f(342, 156));

	buttons_.push_back(button_temp);

}

//--------------------------------------------------------------
void SplashscreenState::update(GameManager* game_manager){

}

//--------------------------------------------------------------
void SplashscreenState::draw(GameManager* game_manager, bool debug){

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

	for(int i = 0; i < buttons_.size(); i++)
		if(buttons_[i].isUnderPoint(ofVec2f(x, y)))
			changeState(game_manager, PlayState::Instance());

}

//--------------------------------------------------------------
void SplashscreenState::mouseReleased(GameManager* game_manager, int x, int y, int button){

}

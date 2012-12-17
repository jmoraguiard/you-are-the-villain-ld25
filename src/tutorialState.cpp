#include "tutorialState.h"

#include "playState.h"

TutorialState TutorialState::tutorial_state_;

//--------------------------------------------------------------
TutorialState::TutorialState(){

}

//--------------------------------------------------------------
TutorialState::~TutorialState(){

}

//--------------------------------------------------------------
TutorialState* TutorialState::Instance(){
	return (&tutorial_state_);
}

//--------------------------------------------------------------
void TutorialState::setup(GameManager* game_manager){

	buttons_.clear();

	background_.loadImage("background.png");

	title_font_.loadFont("visitor1.ttf", 85, true);
	text_font_.loadFont("visitor1.ttf", 20, true);

	text_to_display_ = "You play as BAD MOTHER Nature!\n"; 
	text_to_display_ += "You have different powers to kill\n";
	text_to_display_ += "the inhabitants of an archipelago.\n";
	text_to_display_ += "Select them to create anomalies in\n";
	text_to_display_ += "the sea to affect ships or use the\n";
	text_to_display_ += "lightning to kill planes!\n\n";
	text_to_display_ += "Concatenate explosions to create\n";
	text_to_display_ += "combos of destruction!\n\n";
	text_to_display_ += "To create a water current select\n";
	text_to_display_ += "it and drag mouse on water!\n";
	text_to_display_ += "Vortex, Tsunami you must click on\n";
	text_to_display_ += "the water directly.\n";
	text_to_display_ += "For Lightning click on planes!\n";

	ButtonClass button_temp;
	button_temp.setup("GO!", 70, ofVec2f(341, 556), ofVec2f(342, 156), 5000, false);

	buttons_.push_back(button_temp);

}

//--------------------------------------------------------------
void TutorialState::update(GameManager* game_manager){

	for(int i = 0; i < buttons_.size(); i++)
		buttons_[i].update();

}

//--------------------------------------------------------------
void TutorialState::draw(GameManager* game_manager, bool debug){

	ofSetColor(128, 128, 128);
	background_.draw(0, 0, 1024, 768);

	ofSetColor(64, 0, 0);
	title_font_.drawString("TUTORIAL", 255, 85);

	ofSetColor(0, 0, 0);
	title_font_.drawString("TUTORIAL", 250, 80);

	ofSetColor(0, 0, 0);
	text_font_.drawString(text_to_display_, 265, 130);

	for(int i = 0; i < buttons_.size(); i++)
		buttons_[i].draw();

	if(debug){
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("Tutorial State", 20, 20);
	}

}

//--------------------------------------------------------------
void TutorialState::keyPressed(GameManager* game_manager, int key){

}

//--------------------------------------------------------------
void TutorialState::keyReleased(GameManager* game_manager, int key){

}

//--------------------------------------------------------------
void TutorialState::mouseMoved(GameManager* game_manager, int x, int y){

}

//--------------------------------------------------------------
void TutorialState::mouseDragged(GameManager* game_manager, int x, int y, int button){

}

//--------------------------------------------------------------
void TutorialState::mousePressed(GameManager* game_manager, int x, int y, int button){

	for(int i = 0; i < buttons_.size(); i++){
		if(buttons_[i].isUnderPoint(ofVec2f(x, y)) && buttons_[i].canBeUsed()){
			buttons_[i].setSelected(true);
			changeState(game_manager, PlayState::Instance());
		}
	}

}

//--------------------------------------------------------------
void TutorialState::mouseReleased(GameManager* game_manager, int x, int y, int button){

}

#include "highscoresState.h"

#include "gameManager.h"
#include "splashscreenState.h"

HighscoresState HighscoresState::highscores_state_;

//--------------------------------------------------------------
HighscoresState::HighscoresState(){

}

//--------------------------------------------------------------
HighscoresState::~HighscoresState(){

}

//--------------------------------------------------------------
HighscoresState* HighscoresState::Instance(){
	return (&highscores_state_);
}

//--------------------------------------------------------------
void HighscoresState::setup(GameManager* game_manager){

	buttons_.clear();

	text_font_.loadFont("visitor1.ttf", 17, true);

	text_to_display_ = "";
	game_manager->highscore_ = 0;

	for(int i = 0; i < game_manager->combos_.size(); i++){
		text_to_display_ += "Combo " + ofToString(i+1) + " -> " + ofToString(game_manager->combos_[i].x) + " x " + ofToString(game_manager->combos_[i].y) + " = " + ofToString(game_manager->combos_[i].x*game_manager->combos_[i].y) + " pts\n";
		game_manager->highscore_ += game_manager->combos_[i].x*game_manager->combos_[i].y;
	}

	text_to_display_ += "TOTAL: " + ofToString(game_manager->highscore_) + " pts";

	ButtonClass button_temp;
	button_temp.setup("Go to Start", 50, ofVec2f(286, 606), ofVec2f(452, 100), 5000, true);

	buttons_.push_back(button_temp);

}

//--------------------------------------------------------------
void HighscoresState::update(GameManager* game_manager){

	for(int i = 0; i < buttons_.size(); i++)
		buttons_[i].update();

}

//--------------------------------------------------------------
void HighscoresState::draw(GameManager* game_manager, bool debug){

	ofSetColor(255, 0, 0);
	text_font_.drawString(text_to_display_, 305, 40);

	for(int i = 0; i < buttons_.size(); i++)
		buttons_[i].draw();

	if(debug){
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("Splashscreen State", 20, 20);
	}

}

//--------------------------------------------------------------
void HighscoresState::keyPressed(GameManager* game_manager, int key){

}

//--------------------------------------------------------------
void HighscoresState::keyReleased(GameManager* game_manager, int key){

}

//--------------------------------------------------------------
void HighscoresState::mouseMoved(GameManager* game_manager, int x, int y){

}

//--------------------------------------------------------------
void HighscoresState::mouseDragged(GameManager* game_manager, int x, int y, int button){

}

//--------------------------------------------------------------
void HighscoresState::mousePressed(GameManager* game_manager, int x, int y, int button){

	for(int i = 0; i < buttons_.size(); i++){
		if(buttons_[i].isUnderPoint(ofVec2f(x, y)) && buttons_[i].canBeUsed()){
			buttons_[i].setSelected(true);
			changeState(game_manager, SplashscreenState::Instance());
		}
	}

}

//--------------------------------------------------------------
void HighscoresState::mouseReleased(GameManager* game_manager, int x, int y, int button){

}

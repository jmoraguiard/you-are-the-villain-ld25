#include "gameManager.h"

#include "gameState.h"
#include "splashscreenState.h"

//--------------------------------------------------------------
GameManager::GameManager(){

	current_game_state_ = 0;
	changeState(SplashscreenState::Instance());

}

//--------------------------------------------------------------
GameManager::~GameManager(){

}

//--------------------------------------------------------------
void GameManager::setup(){

	current_game_state_->setup(this);

}

//--------------------------------------------------------------
void GameManager::update(){

	current_game_state_->update(this);

}

//--------------------------------------------------------------
void GameManager::draw(bool debug){

	current_game_state_->draw(this, debug);

}

//--------------------------------------------------------------
void GameManager::keyPressed(int key){

	current_game_state_->keyPressed(this, key);

}

//--------------------------------------------------------------
void GameManager::keyReleased(int key){

	current_game_state_->keyReleased(this, key);

}

//--------------------------------------------------------------
void GameManager::mouseMoved(int x, int y){

	current_game_state_->mouseMoved(this, x, y);

}

//--------------------------------------------------------------
void GameManager::mouseDragged(int x, int y, int button){

	current_game_state_->mouseDragged(this, x, y, button);

}

//--------------------------------------------------------------
void GameManager::mousePressed(int x, int y, int button){

	current_game_state_->mousePressed(this, x, y, button);

}

//--------------------------------------------------------------
void GameManager::mouseReleased(int x, int y, int button){

	current_game_state_->mouseReleased(this, x, y, button);

}

//--------------------------------------------------------------
void GameManager::changeState(GameState* new_game_state){

	if(new_game_state != current_game_state_){
		current_game_state_ = new_game_state;
		current_game_state_->setup(this);
	}

}
#include "playState.h"

#include "gameManager.h"

PlayState PlayState::play_state_;

//--------------------------------------------------------------
PlayState::PlayState(){

}

//--------------------------------------------------------------
PlayState::~PlayState(){

}

//--------------------------------------------------------------
PlayState* PlayState::Instance(){
	return (&play_state_);
}

//--------------------------------------------------------------
void PlayState::setup(GameManager* game_manager){

	ships_.clear();
	islands_.clear();

	for (int i = 0; i < 35; i++){
		Ship *temp_ship = new Ship();
		temp_ship->setup(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
		ships_.push_back(temp_ship);
	}

	
	Island *is_temp = new Island();
	is_temp->setup();
	islands_.push_back(is_temp);

	game_manager->getSeaPointer()->setup(ofGetWidth(), ofGetHeight(), 60, 40);

}

//--------------------------------------------------------------
void PlayState::update(GameManager* game_manager){

	game_manager->getSeaPointer()->fadeField(0.99f);
	game_manager->getSeaPointer()->propagate(0.79f);

	for (int i = 0; i < ships_.size(); i++){
		ships_[i]->resetForce();
		
		// get the force from the vector field: 
		ofVec2f frc;
		frc = game_manager->getSeaPointer()->getForceFromPos(ships_[i]->getPosition().x, ships_[i]->getPosition().y);
		ships_[i]->addForce(frc.x, frc.y);
		ships_[i]->addDampingForce();
		ships_[i]->update();
	}

	for(std::vector<Ship *>::iterator it = ships_.begin() ; it != ships_.end(); ++it){
		
		bool have_to_break = false;

		for(int i = 0; i < ships_.size(); i++){
			if(ships_[i] != (*it)){
				float dist = sqrt(pow((*it)->getPosition().x-ships_[i]->getPosition().x,2)+pow((*it)->getPosition().y-ships_[i]->getPosition().y,2));
				if(dist < 20){
					Explosion *exp_temp = new Explosion();
					exp_temp->setup((*it)->getPosition(), 2500, 30);
					explosions_.push_back(exp_temp);
					it = ships_.erase(it);
					if(it == ships_.end()){
						have_to_break = true;
						break;
					}
				}
			}
		}

		if(have_to_break)
			break;

		for(int i = 0; i < islands_.size(); i++){
			if(islands_[i]->isUnderPoint((*it)->getPosition())){
				Explosion *exp_temp = new Explosion();
				exp_temp->setup((*it)->getPosition(), 2500, 30);
				explosions_.push_back(exp_temp);
				it = ships_.erase(it);
				if(it == ships_.end()){
					have_to_break = true;
					break;
				}
			}
		}

		if(have_to_break)
			break;

		for(int i = 0; i < explosions_.size(); i++){
			if(explosions_[i]->isTouchingExplosion((*it)->getPosition())){
				Explosion *exp_temp = new Explosion();
				exp_temp->setup((*it)->getPosition(), 2500, 30);
				explosions_.push_back(exp_temp);
				it = ships_.erase(it);
				if(it == ships_.end()){
					have_to_break = true;
					break;
				}
			}
		}

		if(have_to_break)
			break;

	}

	for(std::vector<Explosion *>::iterator it = explosions_.begin() ; it != explosions_.end(); ++it){
		if((*it)->update()){
			it = explosions_.erase(it);
			if(it == explosions_.end())
				break;
		}
	}

}

//--------------------------------------------------------------
void PlayState::draw(GameManager* game_manager, bool debug){

	ofEnableAlphaBlending();
	ofSetColor(0,130,130, 200);
	game_manager->getSeaPointer()->draw();

	for (int i = 0; i < ships_.size(); i++){
		ships_[i]->draw();
	}

	for (int i = 0; i < islands_.size(); i++){
		islands_[i]->draw();
	}

	for(int i = 0; i < explosions_.size(); i++){
		explosions_[i]->draw();
	}

	if(debug){
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("Play State", 20, 20);
	}

}

//--------------------------------------------------------------
void PlayState::keyPressed(GameManager* game_manager, int key){

}

//--------------------------------------------------------------
void PlayState::keyReleased(GameManager* game_manager, int key){

}

//--------------------------------------------------------------
void PlayState::mouseMoved(GameManager* game_manager, int x, int y){

}

//--------------------------------------------------------------
void PlayState::mouseDragged(GameManager* game_manager, int x, int y, int button){

	float diffx = x - previous_mouse_x_;
	float diffy = y - previous_mouse_y_;
	
	game_manager->getSeaPointer()->addCurrent((float)x, (float)y, diffx*0.3, diffy*0.3, 60, 0.3f);
	
	previous_mouse_x_ = x;
	previous_mouse_y_ = y;

}

//--------------------------------------------------------------
void PlayState::mousePressed(GameManager* game_manager, int x, int y, int button){

	previous_mouse_x_ = x; 
	previous_mouse_y_ = y;

	if(button == 0)
		game_manager->getSeaPointer()->addVortex((float)x, (float)y, 100, 3.0f);
	if(button == 1 || button == 2)
		game_manager->getSeaPointer()->addTsunami((float)x, (float)y, 100, 5.0f);

}

//--------------------------------------------------------------
void PlayState::mouseReleased(GameManager* game_manager, int x, int y, int button){

}

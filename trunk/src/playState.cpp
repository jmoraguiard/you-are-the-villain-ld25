#include "playState.h"

#include "gameManager.h"
#include "highscoresState.h"

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

	highscore_ = 0;
	combos_.clear();

	ships_.clear();
	sea_explosions_.clear();
	
	islands_.clear();
	refineries_.clear();
	cities_.clear();

	planes_.clear();
	air_explosions_.clear();

	refinery_[0].loadImage("refinery.png");
	refinery_[1].loadImage("refinery_2.png");

	city_[0].loadImage("city.png");
	city_[1].loadImage("city_2.png");

	animation_index_ = 0;

	current_attack_ = false;
	vortex_attack_ = false;
	tsunami_attack_ = false;
	lightning_attack_ = false;

	if(scenario_xml_.loadFile("scenario.xml")){
		cout << "mySettings.xml loaded!" << endl;
	}else{
		cout << "unable to load scenario.xml check data/ folder" << endl;
	}

	if(scenario_xml_.getNumTags("ISLANDS") > 0){
		cout << "Islands processing..." << endl;
		scenario_xml_.pushTag("ISLANDS");
		int numIslands = scenario_xml_.getNumTags("ISLAND");
		if(numIslands > 0){
			int totalIslands = numIslands;
			for(int i = 0; i < totalIslands; i++){
				scenario_xml_.pushTag("ISLAND", i);
				int numPoints = scenario_xml_.getNumTags("PT");
				if(numPoints > 0){
					Island *temp_island = new Island();
					int totalPoints = numPoints;
					for(int i = 0; i < totalPoints; i++){
						int x = scenario_xml_.getValue("PT:X", 0, i);
						int y = scenario_xml_.getValue("PT:Y", 0, i);
						temp_island->island_shape_points_.push_back(ofVec2f(x, y));
					}
					islands_.push_back(temp_island);
				}
				scenario_xml_.popTag();
			}
		}
		scenario_xml_.popTag();
	}

	if(scenario_xml_.getNumTags("REFINERIES") > 0){
		cout << "Refineries processing..." << endl;
		scenario_xml_.pushTag("REFINERIES");
		int numPoints = scenario_xml_.getNumTags("REFINERY");
		cout << " got " << numPoints << " refineries" << endl;
		if(numPoints > 0){
			int totalPoints = numPoints;
			for(int i = 0; i < totalPoints; i++){
				int x = scenario_xml_.getValue("REFINERY:X", 0, i);
				int y = scenario_xml_.getValue("REFINERY:Y", 0, i);
				refineries_.push_back(ofVec2f(x, y));
			}
		}
		scenario_xml_.popTag();
	}

	if(scenario_xml_.getNumTags("CITIES") > 0){
		cout << "Cities processing..." << endl;
		scenario_xml_.pushTag("CITIES");
		int numPoints = scenario_xml_.getNumTags("CITY");
		cout << " got " << numPoints << " cities" << endl;
		if(numPoints > 0){
			int totalPoints = numPoints;
			for(int i = 0; i < totalPoints; i++){
				int x = scenario_xml_.getValue("CITY:X", 0, i);
				int y = scenario_xml_.getValue("CITY:Y", 0, i);
				cities_.push_back(ofVec2f(x, y));
			}
		}
		scenario_xml_.popTag();
	}

	game_manager->getSeaPointer()->setup(ofGetWidth(), ofGetHeight(), 60, 40);

	current_button_.setup("Current", 7, ofVec2f(382, 698), ofVec2f(50, 50), 10000, true);
	vortex_button_.setup("Vortex", 7, ofVec2f(452, 698), ofVec2f(50, 50), 15000, false);
	tsunami_button_.setup("Tsunami", 7, ofVec2f(522, 698), ofVec2f(50, 50), 30000, false);
	lightning_button_.setup("Lightning", 7, ofVec2f(592, 698), ofVec2f(50, 50), 1000, false);

	last_time_ship_created_ = ofGetElapsedTimeMillis();
	last_time_plane_created_ = ofGetElapsedTimeMillis();
	last_time_changed_ = ofGetElapsedTimeMillis();

}

//--------------------------------------------------------------
void PlayState::update(GameManager* game_manager){

	game_manager->getSeaPointer()->fadeField(0.99f);
	game_manager->getSeaPointer()->propagate(0.79f);

	if((ofGetElapsedTimeMillis()-last_time_changed_) > 750){
		if(animation_index_ == 0)
			animation_index_ = 1;
		else
			animation_index_ = 0;
		last_time_changed_ = ofGetElapsedTimeMillis();
	}

	for (int i = 0; i < ships_.size(); i++){
		ships_[i]->resetForce();
		
		// get the force from the vector field: 
		ofVec2f frc;
		frc = game_manager->getSeaPointer()->getForceFromPos(ships_[i]->getPosition().x, ships_[i]->getPosition().y);
		ships_[i]->addForce(frc.x, frc.y);
		ships_[i]->addDampingForce();
		ships_[i]->update();
	}

	for (int i = 0; i < planes_.size(); i++){
		planes_[i]->update();
	}

	if((ofGetElapsedTimeMillis() - last_time_ship_created_) > 2000 && ships_.size() < 25 && refineries_.size() > 1){
		int start_refinery = ofRandom(0, refineries_.size());
		int end_refinery = 0;
		do{
			end_refinery = ofRandom(0, refineries_.size());
		}while(start_refinery == end_refinery);

		Ship *temp_ship = new Ship();
		temp_ship->setup(refineries_[start_refinery].x, refineries_[start_refinery].y, 0, 0, refineries_[end_refinery]);
		ships_.push_back(temp_ship);

		last_time_ship_created_ = ofGetElapsedTimeMillis();
	}

	if((ofGetElapsedTimeMillis() - last_time_plane_created_) > 4000 && planes_.size() < 15 && cities_.size() > 1){
		int start_city = ofRandom(0, cities_.size());
		int end_city = 0;
		do{
			end_city = ofRandom(0, cities_.size());
		}while(start_city == end_city);

		Plane *temp_plane = new Plane();
		temp_plane->setup(cities_[start_city].x, cities_[start_city].y, 0, 0, cities_[end_city]);
		planes_.push_back(temp_plane);

		last_time_plane_created_ = ofGetElapsedTimeMillis();
	}

	for(std::vector<Ship *>::iterator it = ships_.begin() ; it != ships_.end(); ++it){
		
		bool have_to_break = false;

		for(int i = 0; i < ships_.size(); i++){
			if(ships_[i] != (*it)){
				float dist = sqrt(pow((*it)->getPosition().x-ships_[i]->getPosition().x,2)+pow((*it)->getPosition().y-ships_[i]->getPosition().y,2));
				if(dist < 20 && ((*it)->getAffectedByForces() || ships_[i]->getAffectedByForces())){
					Explosion *exp_temp = new Explosion();
					exp_temp->setup((*it)->getPosition(), 2500, 30, combos_.size());
					cout << "Explosion ship and ship with id ";
					cout << combos_.size() << endl;
					combos_.push_back(ofVec2f(1, 100));
					cout << " with: " << combos_[exp_temp->getId()].x << " nums and " << combos_[exp_temp->getId()].y << " points" << endl;
					sea_explosions_.push_back(exp_temp);
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
			if(islands_[i]->isUnderPoint((*it)->getPosition()) && (*it)->getAffectedByForces()){
				Explosion *exp_temp = new Explosion();
				exp_temp->setup((*it)->getPosition(), 2500, 30, combos_.size());
				cout << "Explosion ship and island with id ";
				cout << combos_.size() << endl;
				combos_.push_back(ofVec2f(1, 100));
				cout << " with: " << combos_[exp_temp->getId()].x << " nums and " << combos_[exp_temp->getId()].y << " points" << endl;
				sea_explosions_.push_back(exp_temp);
				it = ships_.erase(it);
				if(it == ships_.end()){
					have_to_break = true;
					break;
				}
			}
		}

		if(have_to_break)
			break;

		for(int i = 0; i < sea_explosions_.size(); i++){
			if(sea_explosions_[i]->isTouchingExplosion((*it)->getPosition())){
				Explosion *exp_temp = new Explosion();
				exp_temp->setup((*it)->getPosition(), 2500, 30, sea_explosions_[i]->getId());
				cout << "Explosion ship and sea_explosion with id ";
				cout << sea_explosions_[i]->getId() << endl;
				combos_[sea_explosions_[i]->getId()].x += 1;
				combos_[sea_explosions_[i]->getId()].y += 100;
				cout << " with: " << combos_[sea_explosions_[i]->getId()].x << " nums and " << combos_[exp_temp->getId()].y << " points" << endl;
				sea_explosions_.push_back(exp_temp);
				it = ships_.erase(it);
				if(it == ships_.end()){
					have_to_break = true;
					break;
				}
			}
		}

		if(have_to_break)
			break;

		for(int i = 0; i < air_explosions_.size(); i++){
			if(air_explosions_[i]->isTouchingExplosion((*it)->getPosition())){
				Explosion *exp_temp = new Explosion();
				exp_temp->setup((*it)->getPosition(), 2500, 30, air_explosions_[i]->getId());
				cout << "Explosion ship and air_explosion with id ";
				cout << air_explosions_[i]->getId() << endl;
				combos_[air_explosions_[i]->getId()].x += 1;
				combos_[air_explosions_[i]->getId()].y += 500;
				cout << " with: " << combos_[air_explosions_[i]->getId()].x << " nums and " << combos_[exp_temp->getId()].y << " points" << endl;
				sea_explosions_.push_back(exp_temp);
				it = ships_.erase(it);
				if(it == ships_.end()){
					have_to_break = true;
					break;
				}
			}
		}

		if(have_to_break)
			break;

		if((*it)->getHasArrived()){
			it = ships_.erase(it);
			if(it == ships_.end()){
				have_to_break = true;
				break;
			}
		}

		if(have_to_break)
			break;

	}

	for(std::vector<Plane *>::iterator it = planes_.begin() ; it != planes_.end(); ++it){
		
		bool have_to_break = false;

		for(int i = 0; i < air_explosions_.size(); i++){
			if(air_explosions_[i]->isTouchingExplosion((*it)->getPosition())){
				Explosion *exp_temp = new Explosion();
				exp_temp->setup((*it)->getPosition(), 2500, 30, air_explosions_[i]->getId());
				cout << "Explosion plane and air_explosion with id ";
				cout << air_explosions_[i]->getId() << endl;
				combos_[air_explosions_[i]->getId()].x += 1;
				combos_[air_explosions_[i]->getId()].y += 250;
				cout << " with: " << combos_[air_explosions_[i]->getId()].x << " nums and " << combos_[exp_temp->getId()].y << " points" << endl;
				air_explosions_.push_back(exp_temp);
				it = planes_.erase(it);
				if(it == planes_.end()){
					have_to_break = true;
					break;
				}
			}
		}

		if(have_to_break)
			break;

		if((*it)->getHasArrived()){
			it = planes_.erase(it);
			if(it == planes_.end()){
				have_to_break = true;
				break;
			}
		}

		if(have_to_break)
			break;

	}

	for(std::vector<ofVec2f>::iterator it = refineries_.begin() ; it != refineries_.end(); ++it){
		
		bool have_to_break = false;

		for(int i = 0; i < sea_explosions_.size(); i++){
			if(sea_explosions_[i]->isTouchingExplosion((*it))){
				Explosion *exp_temp = new Explosion();
				exp_temp->setup((*it), 3500, 60, sea_explosions_[i]->getId());
				cout << "Explosion refinery and sea_explosion with id ";
				cout << sea_explosions_[i]->getId() << endl;
				combos_[sea_explosions_[i]->getId()].x += 1;
				combos_[sea_explosions_[i]->getId()].y += 1000;
				cout << " with: " << combos_[sea_explosions_[i]->getId()].x << " nums and " << combos_[exp_temp->getId()].y << " points" << endl;
				sea_explosions_.push_back(exp_temp);
				it = refineries_.erase(it);
				if(it == refineries_.end()){
					have_to_break = true;
					break;
				}
			}
		}

		if(have_to_break)
			break;

		for(int i = 0; i < air_explosions_.size(); i++){
			if(air_explosions_[i]->isTouchingExplosion((*it))){
				Explosion *exp_temp = new Explosion();
				exp_temp->setup((*it), 3500, 60, air_explosions_[i]->getId());
				cout << "Explosion refinery and air_explosion with id ";
				cout << air_explosions_[i]->getId() << endl;
				combos_[air_explosions_[i]->getId()].x += 1;
				combos_[air_explosions_[i]->getId()].y += 500;
				cout << " with: " << combos_[air_explosions_[i]->getId()].x << " nums and " << combos_[exp_temp->getId()].y << " points" << endl;
				sea_explosions_.push_back(exp_temp);
				it = refineries_.erase(it);
				if(it == refineries_.end()){
					have_to_break = true;
					break;
				}
			}
		}

		if(have_to_break)
			break;

	}

	for(std::vector<ofVec2f>::iterator it = cities_.begin() ; it != cities_.end(); ++it){
		
		bool have_to_break = false;

		for(int i = 0; i < sea_explosions_.size(); i++){
			if(sea_explosions_[i]->isTouchingExplosion((*it))){
				Explosion *exp_temp = new Explosion();
				exp_temp->setup((*it), 3500, 60, sea_explosions_[i]->getId());
				cout << "Explosion city and sea_explosion with id ";
				cout << sea_explosions_[i]->getId() << endl;
				combos_[sea_explosions_[i]->getId()].x += 1;
				combos_[sea_explosions_[i]->getId()].y += 1000;
				cout << " with: " << combos_[sea_explosions_[i]->getId()].x << " nums and " << combos_[exp_temp->getId()].y << " points" << endl;
				sea_explosions_.push_back(exp_temp);
				it = cities_.erase(it);
				if(it == cities_.end()){
					have_to_break = true;
					break;
				}
			}
		}

		if(have_to_break)
			break;

		for(int i = 0; i < air_explosions_.size(); i++){
			if(air_explosions_[i]->isTouchingExplosion((*it))){
				Explosion *exp_temp = new Explosion();
				exp_temp->setup((*it), 3500, 60, air_explosions_[i]->getId());
				cout << "Explosion city and air_explosion with id ";
				cout << air_explosions_[i]->getId() << endl;
				combos_[air_explosions_[i]->getId()].x += 1;
				combos_[air_explosions_[i]->getId()].y += 500;
				cout << " with: " << combos_[air_explosions_[i]->getId()].x << " nums and " << combos_[exp_temp->getId()].y << " points" << endl;
				sea_explosions_.push_back(exp_temp);
				it = cities_.erase(it);
				if(it == cities_.end()){
					have_to_break = true;
					break;
				}
			}
		}

		if(have_to_break)
			break;

	}

	for(std::vector<Explosion *>::iterator it = sea_explosions_.begin() ; it != sea_explosions_.end(); ++it){
		if((*it)->update()){
			it = sea_explosions_.erase(it);
			if(it == sea_explosions_.end())
				break;
		}
	}

	for(std::vector<Explosion *>::iterator it = air_explosions_.begin() ; it != air_explosions_.end(); ++it){
		if((*it)->update()){
			it = air_explosions_.erase(it);
			if(it == air_explosions_.end())
				break;
		}
	}

	if(cities_.size() <= 1 && refineries_.size() <= 1 && ships_.size() < 1 && planes_.size() < 1 && sea_explosions_.size() == 0 && air_explosions_.size() == 0){
		
		game_manager->combos_.clear();

		for(int i = 0; i < combos_.size(); i++){
			game_manager->combos_.push_back(combos_[i]);
		}

		changeState(game_manager, HighscoresState::Instance());
	}

	current_button_.update();
	vortex_button_.update();
	tsunami_button_.update();
	lightning_button_.update();

}

//--------------------------------------------------------------
void PlayState::draw(GameManager* game_manager, bool debug){

	ofEnableAlphaBlending();
	ofSetColor(0, 192, 255, 200);
	game_manager->getSeaPointer()->draw();

	for (int i = 0; i < islands_.size(); i++){
		islands_[i]->draw();
	}

	ofSetColor(255, 255, 255);
	for(int i = 0; i < refineries_.size(); i++){
		refinery_[animation_index_].draw(refineries_[i].x-25, refineries_[i].y-25);
	}

	for(int i = 0; i < cities_.size(); i++){
		city_[animation_index_].draw(cities_[i].x-25, cities_[i].y-25);
	}

	for (int i = 0; i < ships_.size(); i++){
		ships_[i]->draw();
	}

	for (int i = 0; i < planes_.size(); i++){
		planes_[i]->draw();
	}

	for(int i = 0; i < sea_explosions_.size(); i++){
		sea_explosions_[i]->draw(false);
	}

	for(int i = 0; i < air_explosions_.size(); i++){
		air_explosions_[i]->draw(true);
	}

	current_button_.draw();
	vortex_button_.draw();
	tsunami_button_.draw();
	lightning_button_.draw();

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

	if(current_attack_ && current_button_.getPercentage() > 0.1 && !current_button_.isUnderPoint(ofVec2f(x, y))){
		float diffx = x - previous_mouse_x_;
		float diffy = y - previous_mouse_y_;
	
		game_manager->getSeaPointer()->addCurrent((float)x, (float)y, diffx*0.3, diffy*0.3, 60, 0.9f*current_button_.getPercentage());
		current_button_.setPercentage(current_button_.getPercentage()-(current_button_.getPercentage()*0.1));
	
		previous_mouse_x_ = x;
		previous_mouse_y_ = y;
	}

}

//--------------------------------------------------------------
void PlayState::mousePressed(GameManager* game_manager, int x, int y, int button){

	previous_mouse_x_ = x; 
	previous_mouse_y_ = y;
	
	if(current_button_.isUnderPoint(ofVec2f(x, y))){
		current_attack_ = true;
		current_button_.setSelected(current_attack_);
		vortex_attack_ = false;
		vortex_button_.setSelected(vortex_attack_);
		tsunami_attack_ = false;
		tsunami_button_.setSelected(tsunami_attack_);
		lightning_attack_ = false;
		lightning_button_.setSelected(lightning_attack_);
		return;
	}
	if(vortex_button_.isUnderPoint(ofVec2f(x, y))){
		vortex_attack_ = true;
		vortex_button_.setSelected(vortex_attack_);
		current_attack_ = false;
		current_button_.setSelected(current_attack_);
		tsunami_attack_ = false;
		tsunami_button_.setSelected(tsunami_attack_);
		lightning_attack_ = false;
		lightning_button_.setSelected(lightning_attack_);
		return;
	}
	if(tsunami_button_.isUnderPoint(ofVec2f(x, y))){
		tsunami_attack_ = true;
		tsunami_button_.setSelected(tsunami_attack_);
		vortex_attack_ = false;
		vortex_button_.setSelected(vortex_attack_);
		current_attack_ = false;
		current_button_.setSelected(current_attack_);
		lightning_attack_ = false;
		lightning_button_.setSelected(lightning_attack_);
		return;
	}
	if(lightning_button_.isUnderPoint(ofVec2f(x, y))){
		lightning_attack_ = true;
		lightning_button_.setSelected(lightning_attack_);
		vortex_attack_ = false;
		vortex_button_.setSelected(vortex_attack_);
		tsunami_attack_ = false;
		tsunami_button_.setSelected(tsunami_attack_);
		current_attack_ = false;
		current_button_.setSelected(current_attack_);
		return;
	}

	if(button == 0){
		if(vortex_attack_ && vortex_button_.canBeUsed()){
			game_manager->getSeaPointer()->addVortex((float)x, (float)y, 100, 5.0f);
			vortex_button_.setUsed();
		}
		if(tsunami_attack_ && tsunami_button_.canBeUsed()){
			game_manager->getSeaPointer()->addTsunami((float)x, (float)y, 100, 8.0f);
			tsunami_button_.setUsed();
		}
		if(lightning_attack_ && lightning_button_.canBeUsed()){
			for(std::vector<Plane *>::iterator it = planes_.begin() ; it != planes_.end(); ++it){
				bool have_to_break = false;
				
				float dist = sqrt(pow((*it)->getPosition().x-x,2)+pow((*it)->getPosition().y-y,2));
				if(dist < 20){
					Explosion *exp_temp = new Explosion();
					exp_temp->setup((*it)->getPosition(), 2500, 30, combos_.size());
					cout << "Explosion lightning and plane with id ";
					cout << combos_.size() << endl;
					combos_.push_back(ofVec2f(1, 250));
					cout << " with: " << combos_[exp_temp->getId()].x << " nums and " << combos_[exp_temp->getId()].y << " points" << endl;
					air_explosions_.push_back(exp_temp);
					it = planes_.erase(it);
					lightning_button_.setUsed();
					if(it == planes_.end()){
						have_to_break = true;
						break;
					}
				}

				if(have_to_break)
					break;
			}
		}
	}		

}

//--------------------------------------------------------------
void PlayState::mouseReleased(GameManager* game_manager, int x, int y, int button){

}

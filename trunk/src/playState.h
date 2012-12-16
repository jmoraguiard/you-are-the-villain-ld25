#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "gameState.h"

#include "ofxXmlSettings.h"

#include "sea.h"
#include "ship.h"
#include "island.h"
#include "explosion.h"
#include "button.h"
#include "plane.h"

class PlayState: public GameState{

public:
	PlayState();
	~PlayState();
	static PlayState* Instance();

	virtual void setup(GameManager* game_manager);
	virtual void update(GameManager* game_manager);
	virtual void draw(GameManager* game_manager, bool debug);

	virtual void keyPressed(GameManager* game_manager, int key);
	virtual void keyReleased(GameManager* game_manager, int key);
	virtual void mouseMoved(GameManager* game_manager, int x, int y);
	virtual void mouseDragged(GameManager* game_manager, int x, int y, int button);
	virtual void mousePressed(GameManager* game_manager, int x, int y, int button);
	virtual void mouseReleased(GameManager* game_manager, int x, int y, int button);

private:
	static PlayState play_state_;

	vector<Island *> islands_;
	vector<Ship *> ships_;
	vector<Explosion *> sea_explosions_;
	
	vector<Plane *> planes_;
	vector<Explosion *> air_explosions_;

	vector<ofVec2f> refineries_;
	vector<ofVec2f> cities_;

	float previous_mouse_x_;
	float previous_mouse_y_;

	ofxXmlSettings scenario_xml_;

	ButtonClass current_button_;
	bool current_attack_;
	ButtonClass vortex_button_;
	bool vortex_attack_;
	ButtonClass tsunami_button_;
	bool tsunami_attack_;
	ButtonClass lightning_button_;
	bool lightning_attack_;

	int last_time_ship_created_;
	int last_time_plane_created_;

	vector<ofVec2f> combos_;
	int highscore_;

	int last_time_changed_;
	ofImage refinery_[2];
	ofImage city_[2];
	int animation_index_;

};

#endif
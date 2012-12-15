#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "gameState.h"

#include "sea.h"
#include "ship.h"
#include "island.h"
#include "explosion.h"

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
	vector<Explosion *> explosions_;

	float previous_mouse_x_;
	float previous_mouse_y_;

};

#endif
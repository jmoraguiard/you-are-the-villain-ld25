#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "sea.h"

class GameState;

class GameManager {

public:
	GameManager::GameManager();
	GameManager::~GameManager();

	void setup();
	void update();
	void draw(bool debug);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	void changeState(GameState* new_game_state);

	Sea* getSeaPointer(){ return &sea_; }

private:
	GameState* current_game_state_;

	Sea sea_;
	

};

#endif
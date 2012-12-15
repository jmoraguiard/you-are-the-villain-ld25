#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameManager;

class GameState{

public:
	GameState();
	virtual ~GameState();

	virtual void setup(GameManager* game_manager) = 0;
	virtual void update(GameManager* game_manager) = 0;
	virtual void draw(GameManager* game_manager, bool debug) = 0;

	virtual void keyPressed(GameManager* game_manager, int key) = 0;
	virtual void keyReleased(GameManager* game_manager, int key) = 0;
	virtual void mouseMoved(GameManager* game_manager, int x, int y) = 0;
	virtual void mouseDragged(GameManager* game_manager, int x, int y, int button) = 0;
	virtual void mousePressed(GameManager* game_manager, int x, int y, int button) = 0;
	virtual void mouseReleased(GameManager* game_manager, int x, int y, int button) = 0;

	void changeState(GameManager* game_manager, GameState* new_game_state);

private:

};

#endif
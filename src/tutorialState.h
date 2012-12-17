#ifndef TUTORIAL_STATE_H
#define TUTORIAL_STATE_H

#include "gameState.h"

#include "sea.h"
#include "button.h"

class TutorialState: public GameState{

public:
	TutorialState();
	~TutorialState();
	static TutorialState* Instance();

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
	static TutorialState tutorial_state_;

	ofImage background_;

	vector<ButtonClass> buttons_;

	ofTrueTypeFont title_font_;
	ofTrueTypeFont text_font_;
	string text_to_display_;

};

#endif
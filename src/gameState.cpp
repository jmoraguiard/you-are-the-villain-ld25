#include "gameState.h"

#include "gameManager.h"

GameState::GameState(){

}

GameState::~GameState(){

}

void GameState::changeState(GameManager* game_manager, GameState* new_game_state){

	game_manager->changeState(new_game_state);

}
#include"GameManager.h"
GameManager::GameManager(GameBoard* board) : mainMenuState(true), pauseState(false), endState(false), playState(false), board(board) {}
void GameManager::setMainMenuState(bool state) { mainMenuState = state; }
bool GameManager::getMainMenuState() const { return mainMenuState; }
void GameManager::setPauseState(bool state) { pauseState = state; }
bool GameManager::getPauseState() const { return pauseState; }
void GameManager::setEndState(bool state) { endState = state; }
bool GameManager::getEndState() const { return endState; }
void GameManager::setPlayState(bool state) { playState = state; }
bool GameManager::getPlayState() const { return playState; }
bool GameManager::checkEnd() const { return endState; }

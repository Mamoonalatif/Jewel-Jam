#include"GameBoard.h"
class GameManager {
    public:
    bool mainMenuState;
    bool pauseState;
    bool endState;
    bool playState;
    GameBoard* board;

public:
    GameManager(GameBoard* board) : mainMenuState(true), pauseState(false), endState(false), playState(false), board(board) {}

    void setMainMenuState(bool state) { mainMenuState = state; }
    bool getMainMenuState() const { return mainMenuState; }

    void setPauseState(bool state) { pauseState = state; }
    bool getPauseState() const { return pauseState; }

    void setEndState(bool state) { endState = state; }
    bool getEndState() const { return endState; }

    void setPlayState(bool state) { playState = state; }
    bool getPlayState() const { return playState; }

    GameBoard* getGameBoard() const { return board; } // Public getter for board
};

#include"GameBoard.h"
class GameManager {
public:
    bool mainMenuState;
    bool pauseState;
    bool endState;
    bool playState;
    GameBoard* board;
    GameManager(GameBoard* board);
    void setMainMenuState(bool state);
    bool getMainMenuState() const;
    void setPauseState(bool state);
    bool getPauseState() const;
    void setEndState(bool state);
    bool getEndState() const;
    void setPlayState(bool state); 
    bool getPlayState() const;
    bool checkEnd() const;
};

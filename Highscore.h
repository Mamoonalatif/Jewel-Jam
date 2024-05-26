#include"GameBoard.h"
#include<fstream> 
#include"Player.h"
class Highscore {
    Player* player;
public:
    Highscore(const Player& player);  
    ~Highscore();              
    float getScore();
    bool updateScore(const Player& player);  // Updates score if new score is higher
    bool loadScore(const std::string& filename);  // Loads score from a file (optional)
    bool saveScore(const std::string& filename);  // Saves score to a file (optional)
};

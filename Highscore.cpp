#include "Highscore.h"
Highscore::Highscore(const Player& player) {
    this->player = new Player(player.getName(), player.getScore());
}
Highscore::~Highscore() {
    delete player;
}
float Highscore::getScore() {
    return player->getScore();
}
bool Highscore::updateScore(const Player& player) {
    if (player.getScore() > this->player->getScore()) {
        *this->player = player;
        return true;
    }
    return false;
}
bool Highscore::loadScore(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    string name;
    float score;
    file >> name >> score;
    file.close();
    *this->player = Player(name, score);
    return true;
}
bool Highscore::saveScore(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file << player->getName() << " " << player->getScore() << endl;
    file.close();
    return true;
}

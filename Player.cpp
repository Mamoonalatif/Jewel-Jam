#include "Player.h"
Player::Player(string n, float s) {
    name = n;
    score = s;
}
void Player::addscore(int s) {
    score += s;
}
string Player::getName() const {
    return name;
}
float Player::getScore() const {
    return score;
}

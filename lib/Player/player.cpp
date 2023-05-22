#include <player.h>
#include <Arduino.h>

void Player::decreaseScore(int hitScore) {
    if (checkScore(hitScore)) {
        this->score = this->score - hitScore;
    }
    return;
}

bool Player::checkScore(int hitScore) {
    if ((this->score - hitScore) < 0) {
        Serial.println("Bust");
        return false;
    }
    return true;
}
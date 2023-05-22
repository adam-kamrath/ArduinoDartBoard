#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    int score;

public:
    void decreaseScore(int hitscore);
    bool checkScore(int hitScore);
};

#endif
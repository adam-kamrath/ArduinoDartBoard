#include <Arduino.h>
#include <ArrayList.h>
#include "player.h"

#define LED 7

bool gameOver = false;
uint8_t testHitScore;

ArrayList<Player*> players; 

//Checks voltage of analog input and determines what score it goes to
uint8_t getHit(uint8_t pin, uint8_t score1, uint8_t score2, uint8_t score3, uint8_t score4, uint8_t score5, uint8_t score6, uint8_t score7,  uint8_t score8) {
  float voltage = analogRead(pin) * (5.0/1024.0);
  if (voltage > 4.9) {
    return 0;
  }
  if (0.1 < voltage && voltage < 0.6) {
    testHitScore = score1;
    return score1;
  }
  if (0.7 < voltage && voltage < 1.2) {
    testHitScore = score2;
    return score2;
  }
  if (1.3 < voltage && voltage < 2.0) {
    testHitScore = score3;
    return score3;
  }
  if (2.1 < voltage && voltage < 2.9) {
    testHitScore = score4;
    return score4;
  }
  if (3.0 < voltage && voltage < 3.7) {
    testHitScore = score5;
    return score5;
  }
  if (3.8 < voltage && voltage < 4.3) {
    testHitScore = score6;
    return score6;
  }
  if (4.4 < voltage && voltage < 4.5) {
    testHitScore = score7;
    return score7;
  }
  if (4.6 < voltage && voltage < 4.85) {
    testHitScore = score8;
    return score8;
  }
}

//Gets an accurate score of the hit
uint8_t getHitScore() {
  while(true) {
    uint8_t analogA0 = getHit(A0, 1, 2, 3, 4, 5, 6, 7, 0);
    uint8_t analogA1 = getHit(A1, 8, 9, 10, 11, 12, 13, 14, 0);
    uint8_t analogA2 = getHit(A2, 15, 16, 17,18, 19, 20,21, 0);
    uint8_t analogA3 = getHit(A3, 22, 24, 25, 26, 27, 28, 30, 0);
    uint8_t analogA4 = getHit(A4, 32, 33, 34, 36, 38, 39, 40, 0);
    uint8_t analogA5 = getHit(A5, 42, 45, 48, 50, 51, 54, 57 ,60);
    if (analogA0 > 0 && analogA0 == testHitScore) {
      return analogA0;
    }
    if (analogA1 > 0 && analogA1 == testHitScore) {
      return analogA1;
    }
    if (analogA2 > 0 && analogA2 == testHitScore) {
      return analogA2;
    }
    if (analogA3 > 0 && analogA3 == testHitScore) {
      return analogA3;
    }
    if (analogA4 > 0 && analogA4 == testHitScore) {
      return analogA4;
    }
    if (analogA5 > 0 && analogA5 == testHitScore) {
      return analogA5;
    }
  } 
}

void game301Setup() {
  Serial.println("NEW GAME OF 301");
  //Gets the number of players
  Serial.println("Number of players?");
  while(!Serial.available());
  int numPlayers = Serial.parseInt();
  //Creates player objects in players arraylist
  for (int i = 0; i < numPlayers; i++) {
    Player* player = new Player();
    players.add(player);
  }
  //Changes all players scores to 301
  for (int i = 0; i < players.size(); i++) {
    players[i]->score = 301;
  }
}

void game301() {
  //Program stops if game ends
  while(gameOver);
  //Loops through all players
  for (uint8_t i = 0; i < players.size(); i++) {
    Serial.println("PLAYER " + String(i + 1) + "'s TURN");
    Serial.println("Current Score: " + String(players[i]->score));
    //Loops through a players turn (3 turns a player)
    for (uint8_t turn = 0; turn < 3; turn++) {
      uint8_t hitScore = getHitScore();
      Serial.println("Score Hit: " + String(hitScore));
      players[i]->decreaseScore(hitScore);
      delay(1500);
      //Checks if player has won
      if (players[i]->score == 0) {
        Serial.println("GAMEOVER!");
        Serial.println("Player " + String(i + 1) + " has won.");
        gameOver = true;
        return;
      }
      Serial.println("Current Score: " + String(players[i]->score));
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  game301Setup();
}

void loop() {
  game301();
}

#include <Arduino.h>
#include <ArrayList.h>
#include "player.h"

bool gameOver = false;

ArrayList<Player*> players; 

int getHitScore() {
  Serial.println("Score Hit?");
  while(!Serial.available());
  return Serial.parseInt();
}

void setup() {
  Serial.begin(9600);
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

void loop() {
  //Program stops if game ends
  while(gameOver);
  //Loops through all players
  for (int i = 0; i < players.size(); i++) {
    Serial.println("PLAYER " + String(i + 1) + "'s TURN");
    Serial.println("Current Score: " + String(players[i]->score));
    //Loops through a players turn (3 turns a player)
    for (int turn = 0; turn < 3; turn++) {
      int hitScore = getHitScore();
      Serial.println("Score Hit: " + String(hitScore));
      players[i]->decreaseScore(hitScore);
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

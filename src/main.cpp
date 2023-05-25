#include <Arduino.h>
#include <ArrayList.h>
#include "player.h"

bool gameOver = false;

ArrayList<Player*> players; 

//Test Comment
void setup() {
  Serial.begin(9600);
  Serial.println("NEW GAME OF 301");
  Serial.println("Number of players?");
  while(!Serial.available());
  int numberOfPlayers = Serial.parseInt();
  for (int i =0; i < numberOfPlayers; i++) {
    
  }
}

void loop() {
  if (gameOver) {
    return;
  }
  Serial.println(player1.score);
  Serial.println("Score Hit?");
  while(!Serial.available());
  int scorehit = Serial.parseInt();
  player1.decreaseScore(scorehit);
  if (player1.score == 0) {
    Serial.println("GameOver!");
    while(!Serial.available());
    gameOver = true;
  }
}

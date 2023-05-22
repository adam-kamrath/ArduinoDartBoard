#include <Arduino.h>
#include "player.h"

#define RESET 2
Player player1;
bool gameOver = false;

void setup() {
  Serial.begin(9600);
  Serial.println("NEW GAME OF 301");
  player1.score = 301;
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

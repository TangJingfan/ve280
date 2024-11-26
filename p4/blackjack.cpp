#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"

int main(int argc, char *argv[]) {
  // initialize the deck for the whole game
  Deck deck_for_game;
  // shuffle the deck for seven times
  for (int i = 0; i < 7; i++) {
    deck_for_game.shuffle(get_cut());
  }
}
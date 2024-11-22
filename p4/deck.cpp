#include "card.h"

#include <cstdlib>
#include <deck.h>

Deck::Deck() : next(0) {
  int index = 0;
  for (int suit = 0; suit < DIAMONDS; suit++) {
    for (int spot = 0; spot < ACE; spot++) {
      deck[index].suit = static_cast<Suit>(suit);
      deck[index].spot = static_cast<Spot>(spot);
      index++;
    }
  }
}
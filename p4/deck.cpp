#include "deck.h"
#include "card.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Deck::Deck() : next(0) {
  int index = 0;
  for (int suit = SPADES; suit <= DIAMONDS; suit++) {
    for (int spot = TWO; spot <= ACE; spot++) {
      deck[index].suit = static_cast<Suit>(suit);
      deck[index].spot = static_cast<Spot>(spot);
      index++;
    }
  }
}

void Deck::reset() {
  next = 0;
  int index = 0;
  for (int suit = SPADES; suit <= DIAMONDS; suit++) {
    for (int spot = TWO; spot <= ACE; spot++) {
      deck[index].suit = static_cast<Suit>(suit);
      deck[index].spot = static_cast<Spot>(spot);
      index++;
    }
  }
}

void Deck::shuffle(int n) {
  // from 0 to n - 1
  int left_index = 0;
  // from n to DeckSize - 1
  int right_index = n;
  // from 0 to DeckSize - 1
  int shuffled_index = 0;
  Card shuffled_deck[DeckSize];
  while (left_index < n && right_index < DeckSize) {
    shuffled_deck[shuffled_index++] = deck[right_index++];
    shuffled_deck[shuffled_index++] = deck[left_index++];
  }
  while (left_index < n) {
    shuffled_deck[shuffled_index++] = deck[left_index++];
  }
  while (right_index < DeckSize) {
    shuffled_deck[shuffled_index++] = deck[right_index++];
  }
  for (int i = 0; i < DeckSize; i++) {
    deck[i] = shuffled_deck[i];
  }
  next = 0;
}

Card Deck::deal() {
  if (next >= DeckSize) {
    throw DeckEmpty();
  }
  return deck[next++];
}

int Deck::cardsLeft() { return DeckSize - next; }
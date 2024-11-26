#include "hand.h"
#include "card.h"


Hand::Hand() : curValue({0, false}){};

void Hand::discardAll() {
  HandValue reset_handvalue;
  reset_handvalue.count = 0;
  reset_handvalue.soft = false;
  curValue = reset_handvalue;
}

void Hand::addCard(Card c) {
  if (TWO <= c.spot && c.spot <= TEN) {
    curValue.count += (static_cast<int>(c.spot) + 2);
  } else if (JACK <= c.spot && c.spot <= KING) {
    curValue.count += 10;
  } else {
    curValue.count += 11;
    curValue.soft = true;
  }
  if (curValue.count > 21 && curValue.soft) {
    curValue.count -= 10;
    curValue.soft = false;
  }
}

HandValue Hand::handValue() const { return curValue; }
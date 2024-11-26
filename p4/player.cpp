#include "player.h"
#include "card.h"

#include <iostream>

using namespace std;

class simple_player : public Player {
public:
  int bet(unsigned int bankroll, unsigned int minimum) override {
    return static_cast<int>(minimum);
  }

  bool draw(Card dealer, const Hand &player) override {
    if (!player.handValue().soft) {
      if (player.handValue().count <= 11) {
        return true;
      } else if (player.handValue().count == 12) {
        return !(FOUR <= dealer.spot && dealer.spot <= SIX);
      } else if (13 <= player.handValue().count &&
                 player.handValue().count <= 16) {
        return !(TWO <= dealer.spot && dealer.spot <= SIX);
      } else {
        return false;
      }
    } else {
      if (player.handValue().count <= 17) {
        return true;
      } else if (player.handValue().count == 18) {
        return !(dealer.spot == TWO || dealer.spot == SEVEN ||
                 dealer.spot == EIGHT);
      } else {
        return false;
      }
    }
  }

  void expose(Card c) {}

  void shuffled() {}
};

class counting_player : public simple_player {
private:
  int count;

public:
  counting_player() : count(0){};

  int bet(unsigned int bankroll, unsigned int minimum) override {
    if (count >= 2 && (bankroll >= 2 * minimum)) {
      return 2 * static_cast<int>(minimum);
    } else {
      return static_cast<int>(minimum);
    }
  }

  bool draw(Card dealer, const Hand &player) override {
    return simple_player::draw(dealer, player);
  }

  void expose(Card c) {
    if (TWO <= c.spot && c.spot <= SIX) {
      count++;
    } else if (TEN <= c.spot && c.spot <= ACE) {
      count--;
    }
  }

  void shuffled() override { count = 0; }
};

static simple_player simple_player_p4;

static counting_player counting_player_p4;

extern Player *get_Simple() { return &simple_player_p4; }

extern Player *get_Counting() { return &counting_player_p4; }
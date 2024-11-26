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

using namespace std;

void shuffle_for_deck(Deck &deck_for_game, Player *player_in_game) {
  std::cout << "Shuffling the deck" << std::endl;
  for (int i = 0; i < 7; i++) {
    int cut = get_cut();
    std::cout << "cut at " << cut << std::endl;
    deck_for_game.shuffle(cut);
    player_in_game->shuffled();
  }
}

void deal_initial_four_cards(Deck &deck_for_game, Hand &player_hand,
                             Hand &dealer_hand, Player *player_in_game,
                             Card &dealer_up_card, Card &dealer_hole_card) {
  // reset hand
  player_hand.discardAll();
  dealer_hand.discardAll();

  // first card
  Card first_card = deck_for_game.deal();
  player_hand.addCard(first_card);
  player_in_game->expose(first_card);
  cout << "Player dealt " << SpotNames[first_card.spot] << " of "
       << SuitNames[first_card.suit] << endl;

  // second card
  Card second_card = deck_for_game.deal();
  dealer_up_card = second_card;
  dealer_hand.addCard(second_card);
  player_in_game->expose(second_card);
  cout << "Dealer dealt " << SpotNames[second_card.spot] << " of "
       << SuitNames[second_card.suit] << endl;

  // third card
  Card third_card = deck_for_game.deal();
  player_hand.addCard(third_card);
  player_in_game->expose(third_card);
  cout << "Player dealt " << SpotNames[third_card.spot] << " of "
       << SuitNames[third_card.suit] << endl;

  // final card
  Card final_card = deck_for_game.deal();
  dealer_hole_card = final_card;
  dealer_hand.addCard(final_card);
}

bool check_natural21(Hand &player_hand, int &bankroll, int &wager) {
  if (player_hand.handValue().soft && player_hand.handValue().count == 21) {
    cout << "Player dealt natural 21" << endl;
    bankroll += (3 * wager) / 2;
    return true;
  }
  return false;
}

bool check_bust(Hand &hand) {
  if (hand.handValue().count <= 21) {
    return false;
  }
  return true;
}

void final_comparison(Hand &player_hand, Hand &dealer_hand, int &bankroll,
                      int &wager) {
  if (dealer_hand.handValue().count > player_hand.handValue().count) {
    cout << "Dealer wins" << endl;
    bankroll -= wager;
  } else if (dealer_hand.handValue().count < player_hand.handValue().count) {
    cout << "Player wins" << endl;
    bankroll += wager;
  } else {
    cout << "Push" << endl;
  }
}

int main(int argc, char *argv[]) {
  // const for the game
  const int minimum_bet = 5;
  // init bankroll
  int bankroll = atoi(argv[1]);

  // init target hands and current hands
  int current_hands = 0;
  int target_hands = atoi(argv[2]);

  // select mode for player
  const string player_mode = static_cast<string>(argv[3]);
  Player *player = nullptr;
  if (player_mode == "simple") {
    player = get_Simple();
  } else if (player_mode == "counting") {
    player = get_Counting();
  }

  // initialize the deck for the whole game
  Deck deck_for_game;

  // shuffle the deck for seven times
  // shuffle for the first time
  shuffle_for_deck(deck_for_game, player);

  // init hand for player and dealer
  Hand player_hand, dealer_hand;

  // simulation of the game
  while (bankroll >= minimum_bet && ++current_hands <= target_hands) {
    // init the hand
    cout << "Hand " << current_hands << " bankroll " << bankroll << endl;

    // check deck
    if (deck_for_game.cardsLeft() < 20) {
      shuffle_for_deck(deck_for_game, player);
    }

    // end game
    if (bankroll < minimum_bet) {
      break;
    }

    // player bet
    int wager = player->bet(bankroll, minimum_bet);
    cout << "Player bets " << wager << endl;

    // init dealer card
    Card dealer_up_card, dealer_hole_card;

    // deal the initial four cards
    deal_initial_four_cards(deck_for_game, player_hand, dealer_hand, player,
                            dealer_up_card, dealer_hole_card);

    if (check_natural21(player_hand, bankroll, wager)) {
      continue;
    }

    // player deal card
    while (player->draw(dealer_up_card, player_hand)) {
      Card next_card_for_player = deck_for_game.deal();
      player_hand.addCard(next_card_for_player);
      player->expose(next_card_for_player);
    }

    cout << "Player's total is " << player_hand.handValue().count << endl;

    // check whether player busts
    if (check_bust(player_hand)) {
      bankroll -= wager;
      cout << "Player busts" << endl;
      continue;
    }

    // show dealer's hole card
    player->expose(dealer_hole_card);
    cout << "Dealer's hole card is " << SpotNames[dealer_hole_card.spot]
         << " of " << SuitNames[dealer_hole_card.suit] << endl;

    // dealer gets new card
    while (dealer_hand.handValue().count < 17) {
      Card new_card_for_dealer = deck_for_game.deal();
      dealer_hand.addCard(new_card_for_dealer);
      player->expose(new_card_for_dealer);
      cout << "Dealer dealt " << SpotNames[new_card_for_dealer.spot] << " of "
           << SuitNames[new_card_for_dealer.suit] << endl;
    }

    cout << "Dealer's total is " << dealer_hand.handValue().count << endl;

    // check whether dealer busts
    if (check_bust(dealer_hand)) {
      cout << "Dealer busts" << endl;
      bankroll += wager;
      continue;
    }

    // if both don't bust, final check
    final_comparison(player_hand, dealer_hand, bankroll, wager);
  }

  // finalizing the game
  if (bankroll < minimum_bet) {
    cout << "Player has " << bankroll << " after " << current_hands << " hands"
         << endl;
  } else {
    cout << "Player has " << bankroll << " after " << --current_hands
         << " hands" << endl;
  }
  return 0;
}
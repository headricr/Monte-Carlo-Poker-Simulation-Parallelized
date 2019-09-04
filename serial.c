#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cardtests.h>
#include <deck.h>

void mains(int argc, char *argv[])
{
  unsigned long int cases = 1000000;
  int wins = 0;

  struct card fullDeck[DECKSIZE];
  init_deck(fullDeck);

  struct card userHand[] = {{.suit = 1, .rank = 2, .inDeck = -1},
                              {.suit = 3, .rank = 2, .inDeck = -1},
                              {.suit = 2, .rank = 2, .inDeck = -1},
                              {.suit = 1, .rank = 9, .inDeck = -1},
                              {.suit = 2, .rank = 10, .inDeck = -1}};

  int randomIndices[HANDSIZE];
  struct card randomHand[HANDSIZE];

  mark_player_deck(userHand, fullDeck);

  // for (int n = 0; n < DECKSIZE; n++)
  // {
  //   printf("%s of %s\n", rankName(fullDeck[n].rank), suitName(fullDeck[n].suit));
  // }


  // test_card_compares();

  // printf("Testing User Hand:\n");
  // print_hand(userHand);
  // printf("\nAgainst:\n");


  for (unsigned long int i = 0; i < cases; i++) {
    for (int j = 0; j < HANDSIZE; j++) {
      randomIndices[j] = get_card(fullDeck);
      randomHand[j] = fullDeck[randomIndices[j]];
    }

    int result = compare_hands(userHand, randomHand);

    // print_hand(randomHand);
    // printf("Result: %d\n\n", result);

    if (result == 1) {
      wins++;
    }

    for (int k = 0; k < HANDSIZE; k++) {
      fullDeck[randomIndices[k]].inDeck = 1;
    }
  }

  printf("Wins: %d Cases: %lu Probability: %f\n", wins, cases, ((float)wins/cases));


  // printf("Random hand:\n");
  // for (int n = 0; n < HANDSIZE; n++)
  // {
  //   printf("%s of %s\n", rankName(randomHand[n].rank), suitName(randomHand[n].suit));
  // }





  // Monte Carlo:
  // for (int i = 0; i < numTests; i++) {
    // Generate 5 random numbers

    // Compare user deck against random 5 cards

    // Increment win counter if win

  // Calculate odds as win/numTests
  // }
}

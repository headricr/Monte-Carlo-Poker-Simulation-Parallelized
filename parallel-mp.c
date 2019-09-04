#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <cardtests.h>
#include <deck.h>

void mainss(int argc, char *argv[])
{
  printf("OpenMP!!\n");

  unsigned long int cases;
  int threads;
  printf("Enter number of cases: \n");
  scanf("%lu", &cases);
  printf("Enter number of threads: \n");
  scanf("%d", &threads);

  int wins = 0;

  double start, elapsed;

  struct card fullDeck[DECKSIZE];
  init_deck(fullDeck);

  struct card userHand[] = {{.suit = 1, .rank = 2, .inDeck = -1},
                              {.suit = 3, .rank = 2, .inDeck = -1},
                              {.suit = 2, .rank = 8, .inDeck = -1},
                              {.suit = 1, .rank = 9, .inDeck = -1},
                              {.suit = 2, .rank = 10, .inDeck = -1}};


  mark_player_deck(userHand, fullDeck);

  start = omp_get_wtime();
  #pragma omp parallel for num_threads(threads) reduction (+:wins)
  for (unsigned long int i = 0; i < cases; i++) {
    int randomIndices[HANDSIZE];
    struct card randomHand[HANDSIZE];

    for (int j = 0; j < HANDSIZE; j++) {
      randomIndices[j] = get_card(fullDeck);
      randomHand[j] = fullDeck[randomIndices[j]];
    }

    int result = compare_hands(userHand, randomHand);

    if (result == 1) {
      wins++;
    }

    for (int k = 0; k < HANDSIZE; k++) {
      fullDeck[randomIndices[k]].inDeck = 1;
    }
  }
  elapsed = omp_get_wtime() - start;

  printf("Wins: %d Cases: %lu Probability: %f\n", wins, cases, ((float)wins/cases));
  printf("Elapsed time: %f\n", elapsed);
}

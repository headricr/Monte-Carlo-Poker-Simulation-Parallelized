#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <deck.h>

//#define TIME


void main(int argc, char *argv[])
{
  /* MPI Setup */
  int comm_sz;
  int my_rank;
  double local_start, local_finish, local_elapsed, elapsed;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  // Card MPI Datatype:
  MPI_Datatype mpi_card;
  MPI_Type_contiguous(3, MPI_INT, &mpi_card);
  MPI_Type_commit(&mpi_card);

  // Poker Stuff
  unsigned long int cases;
  int loc_wins = 0;
  int glob_wins = 0;
  unsigned long int loc_cases;

  srand(time(NULL));

  struct card loc_deck[DECKSIZE];
  struct card loc_userHand[HANDSIZE];

  int randomIndices[HANDSIZE];
  struct card randomHand[HANDSIZE];

  int randRank;
  //int inputVals[HANDSIZE*2];
  int inputVals[HANDSIZE*2];
  int handType;

  if (my_rank == 0) {
    #ifndef TIME
    printf("Enter hand type (see readme):\n");
    scanf("%d", &handType);
    printf("hand type: %d\n", handType);
    populateHand(handType, inputVals);
    printf("Enter number of cases: \n");
    scanf("%lu", &cases);
    #endif

    #ifdef TIME
    cases = 10000000;
    #endif


    int cases_remainder = cases % comm_sz;
    unsigned long int cases_send[comm_sz];

    for (int i = 0; i < comm_sz; i++) {
      cases_send[i] = (cases / comm_sz);
      if (cases_remainder != 0) {
        cases_send[i]++;
        cases_remainder--;
      }
    }

    loc_cases = cases_send[0];

    for (int i = 1; i < comm_sz; i++) {
      MPI_Send(&cases_send[i], 1, MPI_UNSIGNED_LONG, i, 0, MPI_COMM_WORLD);
    }

    init_deck(loc_deck);

    #ifndef TIME
    struct card userHand[] = {{.suit = inputVals[0], .rank = inputVals[1], .inDeck = -1},
                                {.suit = inputVals[2], .rank = inputVals[3], .inDeck = -1},
                                {.suit = inputVals[4], .rank = inputVals[5], .inDeck = -1},
                                {.suit = inputVals[6], .rank = inputVals[7], .inDeck = -1},
                                {.suit = inputVals[8], .rank = inputVals[9], .inDeck = -1}};
    #endif

    #ifdef TIME
    struct card userHand[] = {{.suit = 1, .rank = 10, .inDeck = -1},
                                {.suit = 1, .rank = 11, .inDeck = -1},
                                {.suit = 1, .rank = 12, .inDeck = -1},
                                {.suit = 1, .rank = 13, .inDeck = -1},
                                {.suit = 1, .rank = 14, .inDeck = -1}};
    #endif


    mark_player_deck(userHand, loc_deck);

    for (int i = 0; i < HANDSIZE; i++) {
      loc_userHand[i] = userHand[i];
    }
  }

  if (my_rank != 0) {
    MPI_Recv(&loc_cases, 1, MPI_UNSIGNED_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }


  MPI_Barrier(MPI_COMM_WORLD);
  local_start = MPI_Wtime();

  // Send Deck
  MPI_Bcast(loc_deck, DECKSIZE, mpi_card, 0, MPI_COMM_WORLD);
  MPI_Bcast(loc_userHand, HANDSIZE, mpi_card, 0, MPI_COMM_WORLD);

  // Monte Carloitize
  for (unsigned long int i = 0; i < loc_cases; i++) {
    for (int j = 0; j < HANDSIZE; j++) {
      randomIndices[j] = get_card(loc_deck);
      randomHand[j] = loc_deck[randomIndices[j]];
    }

    int result = compare_hands(loc_userHand, randomHand);

    if (result == 1) {
      loc_wins++;
    }

    for (int k = 0; k < HANDSIZE; k++) {
      loc_deck[randomIndices[k]].inDeck = 1;
    }
  }

  MPI_Reduce(&loc_wins, &glob_wins, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  local_finish = MPI_Wtime();
  local_elapsed = local_finish - local_start;
  MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

  if (my_rank == 0) {
    #ifndef TIME
    printf("Wins: %d Cases: %lu Probability: %f\n", glob_wins, cases, ((float)glob_wins/cases));
    printf("Elapsed time = %f seconds\n", elapsed);
    #endif

    #ifdef TIME
    printf("%f\n", elapsed);
    #endif
  }

  MPI_Finalize();
}

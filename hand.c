#include <stdio.h>
#include <stdlib.h>
#include <hand.h>
#include <string.h>

void print_hand(struct card hand[HANDSIZE])
{
  for (int i = 0; i < HANDSIZE; i++)
  {
    printf("%s of %s\n", rankName(hand[i].rank), suitName(hand[i].suit));
  }
}

int compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

void sort_hand(struct card hand[HANDSIZE], int rankArray[HANDSIZE])
{
  for (int i = 0; i < HANDSIZE; i++)
  {
    rankArray[i] = hand[i].rank;
  }
  qsort(rankArray, HANDSIZE, sizeof(int), compare);
}

// Check if all the cards in a hand have the same rank
int same_rank(struct card hand[HANDSIZE])
{
  int firstSuit = hand[0].suit;

  if (hand[1].suit == firstSuit &&
      hand[2].suit == firstSuit &&
      hand[3].suit == firstSuit &&
      hand[4].suit == firstSuit) {
        return 1;
      } else {
        return 0;
      }
}

void customHand(int inputVals[HANDSIZE*2])
{
  for (int i = 0; i < HANDSIZE*2; i++) {
    if (i % 2 == 0) {
      printf("Enter a suit:\n");
    } else {
      printf(" and a rank:\n");
    }
    scanf("%d", &inputVals[i]);
  }
}

int populateHand(int handType, int inputVals[])
{
  switch(handType) {
    case 1: // High Card
      memcpy(inputVals, (int [10]){1, 2, 1, 4, 2, 5, 3, 8, 4, 6}, 10*sizeof(int));
      return 1;
    case 2: // Pair
      memcpy(inputVals, (int [10]){1, 2, 1, 4, 2, 7, 3, 12, 4, 7}, 10*sizeof(int));
      return 1;
    case 3: // Two Pair
      memcpy(inputVals, (int [10]){1, 4, 4, 4, 2, 5, 3, 5, 4, 7}, 10*sizeof(int));
      return 1;
    case 4: // Three of a kind
      memcpy(inputVals, (int [10]){1, 5, 2, 5, 3, 5, 3, 8, 4, 6}, 10*sizeof(int));
      return 1;
    case 5: // Straight
      memcpy(inputVals, (int [10]){1, 4, 1, 5, 2, 6, 3, 7, 4, 8}, 10*sizeof(int));
      return 1;
    case 6: // Flush
      memcpy(inputVals, (int [10]){1, 6, 1, 5, 1, 8, 1, 10, 1, 12}, 10*sizeof(int));
      return 1;
    case 7: // Full House
      memcpy(inputVals, (int [10]){2, 5, 3, 5, 4, 5, 2, 6, 1, 6}, 10*sizeof(int));
      return 1;
    case 8: // Four of a kind
      memcpy(inputVals, (int [10]){1, 11, 2, 11, 3, 11, 4, 11, 4, 6}, 10*sizeof(int));
      return 1;
    case 9: // Straight Flush
      memcpy(inputVals, (int [10]){4, 8, 4, 7, 4, 6, 4, 5, 4, 4}, 10*sizeof(int));
      return 1;
    case 10: // Royal Flush
      memcpy(inputVals, (int [10]){2, 14, 2, 13, 2, 12, 2, 11, 2, 10}, 10*sizeof(int));
      return 1;
    default:
      // memcpy(inputVals, (int [10]){1, 2, 2, 3, 2, 4, 3, 5, 4, 7}, 10*sizeof(int));
      customHand(inputVals);
      return 1;
  }
  for (int i = 0; i < 10; i++)
  {
    printf("%d\n", inputVals[i]);
  }
}

int * count_ranks(struct card hand[HANDSIZE])
{
  int * rankCount = calloc(NUMRANKS+1, sizeof(int));

  for (int i = 0; i < HANDSIZE; i++) {
    rankCount[hand[i].rank]++;
  }
  return rankCount;
}

int highest_combination(struct card userHand[HANDSIZE], struct card randomHand[HANDSIZE],
                        int combo, int tieValue)
{
  int * userCounts = count_ranks(userHand);
  int * randomCounts = count_ranks(randomHand);

  for (int i = NUMRANKS; i > 0; i--) {
    // // printf("%d: userCount: %d, randomCount: %d\n",i,  userCounts[i], randomCounts[i]);
    if (userCounts[i] == combo && randomCounts[i] < combo) {
      free(userCounts);
      free(randomCounts);
      return 1;
    } else if (randomCounts[i] == combo && userCounts[i] < combo) {
      free(userCounts);
      free(randomCounts);
      return 0;
    }
  }
  free(userCounts);
  free(randomCounts);
  return tieValue;
}

// Five cards in sequence, not same suit
int is_straight(struct card hand[HANDSIZE], int sortedRanks[HANDSIZE]) {
  int firstRank = sortedRanks[4];

  if (sortedRanks[3] == firstRank - 1 &&
      sortedRanks[2] == firstRank - 2 &&
      sortedRanks[1] == firstRank - 3 &&
      sortedRanks[0] == firstRank - 4 ) {
    // // printf"Is Straight!\n");
    return 1;
  } else {
    return 0;
  }
}

// Five cards in sequence all same suit
int is_straight_flush(struct card hand[HANDSIZE], int sortedRanks[HANDSIZE]) {

  if (same_rank(hand) == 1) {
    // // printf"It might be straight flush!\n");
    return is_straight(hand, sortedRanks);
  } else {
    return 0;
  }
}

/* Poker Hand Checks */
// A, K, Q, J, 10 all same suit
int is_royal_flush(struct card hand[HANDSIZE], int sortedRanks[HANDSIZE]) {
  if (sortedRanks[4] == 14) {
    return is_straight_flush(hand, sortedRanks);
  } else {
    return 0;
  }
}

// 4 cards with same rank
int is_four_kind(struct card hand[HANDSIZE]) {
  int * rankCount = count_ranks(hand);

  for (int i = 1; i <= NUMRANKS; i++) {
    // // printf"Rank %d has %d counts\n", i, rankCount[i]);
    if (rankCount[i] >= 4) {
      free(rankCount);
      return 1;
    }
  }
  free(rankCount);
  return 0;
}

// Three of a kind with a pair
int is_full_house(struct card hand[HANDSIZE]) {
  int * rankCount = count_ranks(hand);
  int three_counter = 0;
  int two_counter = 0;

  for (int i = 1; i <= NUMRANKS; i++) {
    // // printf("%d: Count: %d\n", i, rankCount[i]);
    if (rankCount[i] == 3) {
      three_counter++;
    }
    else if (rankCount[i] == 2) {
      two_counter++;
    }
  }

  if (three_counter == 1 && two_counter == 1) {
    free(rankCount);
    return 1;
  } else {
    free(rankCount);
    return 0;
  }
}

// Five cards with same suit, not in sequence
int is_flush(struct card hand[HANDSIZE]) {
  int suitCnt = 1;
  int firstSuit = hand[0].suit;

  for (int i = 1; i < HANDSIZE; i++) {
    if (hand[i].suit == firstSuit) suitCnt++;
  }

  if (suitCnt == 5) {
    return 1;
  } else {
    return 0;
  }
}

// Three cards of same rank
int is_three_kind(struct card hand[HANDSIZE]) {
  int * rankCount = count_ranks(hand);


  for (int i = 0; i < NUMRANKS; i++) {
    if (rankCount[i] == 3) {
      free(rankCount);
      return 1;
    }
  }
  free(rankCount);
  return 0;
}

// Two different pairs
int is_two_pair(struct card hand[HANDSIZE]) {
  int * rankCount = count_ranks(hand);
  int two_counter = 0;

  for (int i = 0; i < NUMRANKS; i++) {
    if (rankCount[i] == 2) {
      two_counter++;
    }
  }

  if (two_counter == 2) {
    free(rankCount);
    return 1;
  } else {
    free(rankCount);
    return 0;
  }
}

// Two cards of same rank
int is_pair(struct card hand[HANDSIZE]) {
  int * rankCount = count_ranks(hand);

  for (int i = 0; i < NUMRANKS; i++) {
    if (rankCount[i] == 2) {
      free(rankCount);
      return 1;
    }
  }
  free(rankCount);
  return 0;
}

int is_high_card(int userSort[HANDSIZE], int randomSort[HANDSIZE])
{
  for (int i = HANDSIZE - 1; i >= 0; i--) {
    if (userSort[i] > randomSort[i]) {
      return 1;
    } else if (randomSort[i] > userSort[i]) {
      return 0;
    }
  }
  return 0;
}

// Returns 1 if user wins, 0 if user loses
int compare_hands(struct card userHand[HANDSIZE], struct card randomHand[HANDSIZE])
{
  int userSort[HANDSIZE];
  int randomSort[HANDSIZE];
  sort_hand(userHand, userSort);
  sort_hand(randomHand, randomSort);

  int userResult;
  int randomResult;

  // Royal Flush
  userResult = is_royal_flush(userHand, userSort);
  randomResult = is_royal_flush(randomHand, randomSort);
  if (userResult == 1 && randomResult == 1) // Tie
  {
    //printf("Royal Flush: Tie\n");
    return 0;
  }
  else if (randomResult == 1) { // Random wins
    // printf("Royal Flush: Random wins\n");
    return 0;
  }
  else if (userResult == 1) { // User wins
    // printf("Royal Flush: User wins\n");
    return 1;
  }
  else {
    // Straight Flush
    userResult = is_straight_flush(userHand, userSort);
    randomResult = is_straight_flush(randomHand, randomSort);
    if (userResult == 1 && randomResult == 1) // Tie
    {
      // printf("Straight Flush: Checking Tie\n");
      return is_high_card(userSort, randomSort);
    }
    else if (randomResult) { // Random wins
      // printf("Straight Flush: Random Wins\n");
      return 0;
    }
    else if (userResult == 1) { // User wins
      // printf("Straight Flush: User Wins\n");
      return 1;
    }
    else {
      // Four of a kind
      userResult = is_four_kind(userHand);
      randomResult = is_four_kind(randomHand);
      if (userResult == 1 && randomResult == 1) // Tie
      {
        // printf("Four Kind: Checking Tie\n");
        return highest_combination(userHand, randomHand, 4, 0);
      }
      else if (randomResult == 1) { // Random wins
        // printf("Four Kind: Random Wins\n");
        return 0;
      }
      else if (userResult == 1) { // User wins
        // printf("Four Kind: User Wins\n");
        return 1;
      }
      else {
        // Full house
        userResult = is_full_house(userHand);
        randomResult = is_full_house(randomHand);
        if (userResult == 1 && randomResult == 1) // Tie
        {
          // printf("Full House: Checking Tie\n");
          return highest_combination(userHand, randomHand, 3, 0);
        }
        else if (randomResult == 1) { // Random wins
          // printf("Full House: Random Wins\n");
          return 0;
        }
        else if (userResult == 1) { // User wins
          // printf("Full House: User Wins\n");
          return 1;
        }
        else {
          // Flush
          userResult = is_flush(userHand);
          randomResult = is_flush(randomHand);
          if (userResult == 1 && randomResult == 1) // Tie
          {
            // printf("Flush: Random\n");
            return is_high_card(userSort, randomSort);
          }
          else if (randomResult == 1) { // Random wins
            // printf("Flush: Random Wins\n");
            return 0;
          }
          else if (userResult == 1) { // User wins
            // printf("Flush: User Wins\n");
            return 1;
          }
          else {
            // Straight
            userResult = is_straight(userHand, userSort);
            randomResult = is_straight(randomHand, randomSort);
            if (userResult == 1 && randomResult == 1) // Tie
            {
              // printf("Straight: Checking Tie\n");
              return is_high_card(userSort, randomSort);
            }
            else if (randomResult == 1) { // Random wins
              // printf("Straight: Random Wins\n");
              return 0;
            }
            else if (userResult == 1) { // User wins
              // printf("Straight: User Wins\n");
              return 1;
            }
            else {
              // Three of a kind
              userResult = is_three_kind(userHand);
              randomResult = is_three_kind(randomHand);
              if (userResult == 1 && randomResult == 1) // Tie
              {
                // printf("Three Kind: Checking Tie\n");
                return highest_combination(userHand, randomHand, 3, 0);
              }
              else if (randomResult == 1) { // Random wins
                // printf("Three Kind: Random Wins\n");
                return 0;
              }
              else if (userResult == 1) { // User wins
                // printf("Three Kind: User Wins\n");
                return 1;
              }
              else {
                // Two pair
                userResult = is_two_pair(userHand);
                randomResult = is_two_pair(randomHand);
                if (userResult == 1 && randomResult == 1) // Tie
                {
                  // printf("Two Pair: Checking Tie\n");
                  int highestResult = highest_combination(userHand, randomHand, 2, 1);
                  // // printf("Result: %d\n", highestResult);
                  if (highestResult == 1) {
                    return highest_combination(userHand, randomHand, 1, 0);
                  } else {
                    return highestResult;
                  }
                }
                else if (randomResult == 1) { // Random wins
                  // printf("Two Pair: Random Wins\n");
                  return 0;
                }
                else if (userResult == 1) { // User wins
                  // printf("Two Pair: User Wins\n");
                  return 1;
                }
                else {
                  // Pair
                  userResult = is_pair(userHand);
                  randomResult = is_pair(randomHand);
                  if (userResult == 1 && randomResult == 1) // Tie
                  {
                    // printf("Pair: Checking Tie\n");
                    int highestResult = highest_combination(userHand, randomHand, 2, 1);
                    if (highestResult == 1) {
                      return highest_combination(userHand, randomHand, 1, 0);
                    } else {
                      return highestResult;
                    }
                  }
                  else if (randomResult == 1) { // Random wins
                    // printf("Pair: Random Wins\n");
                    return 0;
                  }
                  else if (userResult == 1) { // User wins
                    // printf("Pair: User Wins\n");
                    return 1;
                  }
                  // High Card
                  else {
                    // printf("Checking High Card\n");
                    return is_high_card(userSort, randomSort);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

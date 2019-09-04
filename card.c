#include <stdio.h>
#include <stdlib.h>
#include <card.h>

char * suitName(int suit) {
  switch(suit) {
    case 1:
      return "Clubs";
    case 2:
      return "Diamonds";
    case 3:
      return "Hearts";
    case 4:
      return "Spades";
    default:
      return "Unknown";
  }
}

char * rankName(int rank) {
  switch(rank) {
    case 14:
      return "Ace";
    case 13:
      return "King";
    case 12:
      return "Queen";
    case 11:
      return "Jack";
    case 10:
      return "Ten";
    case 9:
      return "Nine";
    case 8:
      return "Eight";
    case 7:
      return "Seven";
    case 6:
      return "Six";
    case 5:
      return "Five";
    case 4:
      return "Four";
    case 3:
      return "Three";
    case 2:
      return "Two";
    default:
      return "Unknown";
  }
}

int cards_equal(struct card c1, struct card c2)
{
  if (c1.suit == c2.suit && c1.rank == c2.rank)
  {
    return 1;
  } else {
    return 0;
  }
}

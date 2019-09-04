#ifndef _CARD_
#define _CARD_

#define NUMSUITS 4
#define NUMRANKS 14

// inDeck =  1: Card is in deck and can be drawn
// inDeck = -1: Card is out of deck
struct card
{
  int suit;
  int rank;
  int inDeck;
};

char * suitName(int suit);
char * rankName(int rank);
int cards_equal(struct card c1, struct card c2);

#endif

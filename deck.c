#include <stdio.h>
#include <stdlib.h>
#include <deck.h>


void mark_player_deck(struct card hand[HANDSIZE], struct card deck[DECKSIZE])
{
  for (int cIndex = 0; cIndex < HANDSIZE; cIndex++)
  {
    for (int dIndex = 0; dIndex < DECKSIZE; dIndex++)
    {
      if (cards_equal(hand[cIndex], deck[dIndex]) == 1)
      {
        deck[dIndex].inDeck *= -1;
      }
    }
  }
}

void init_deck(struct card deck[DECKSIZE])
{
  static int tr = 1; //marked 1 for true for being in deck
  int index = 0;

  for (int i = 1; i <= NUMSUITS; i++)
  {
    for (int j = 2; j <= NUMRANKS; j++)
    {
      deck[index].suit = i;
      deck[index].rank = j;
      deck[index].inDeck = tr;
      index++;
    }
  }
}

int get_card(struct card deck[DECKSIZE])
{
  int random = lrand48() % DECKSIZE;
  // printf("Rand: %d\n", random);

  if (deck[random].inDeck != 1) {
    return get_card(deck);
  } else {
    deck[random].inDeck = -1;
    return random;
  }
}

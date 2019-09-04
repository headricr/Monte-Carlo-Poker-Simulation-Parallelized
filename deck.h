#ifndef _DECK_
#define _DECK_

#include <hand.h>
#include <card.h>
#define DECKSIZE 52

void mark_player_deck(struct card hand[HANDSIZE], struct card deck[DECKSIZE]);
void init_deck(struct card deck[DECKSIZE]);
int get_card(struct card deck[DECKSIZE]);

#endif

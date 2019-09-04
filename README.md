# Monte Carlo Poker Simulation
Given an initial 5-card hand, calculates the probability of winning using a Monte Carlo simulation.<br />

Compile with 'make poker'<br />
Run with **mpiexec -np x ./poker** (substitute x for number of nodes)<br />

Program will ask for a hand type.  Choose from 10 premade hands or build a custom hand.<br />
## Premade hands:
1  - High Card<br />
2  - Pair<br />
3  - Two Pair<br />
4  - Three of a kind<br />
5  - Straight<br />
6  - Flush<br />
7  - Full House<br />
8  - Four of a kind<br />
9  - Straight Flush<br />
10 - Royal Flush<br />
11 - Custom Hand<br />

## If the user chooses to build a custom hand:
Program will ask for a suit and a rank five times:<br />
Suits range from 1 to 4<br />
Ranks from 2 to 14<br />

### Suits:
1 - Clubs<br />
2 - Diamonds<br />
3 - Hearts<br />
4 - Spades<br />

### Ranks:
2 through 10 - respective values<br />
11 - Jack<br />
12 - Queen<br />
13 - King<br />
14 - Ace<br />

Program also asks for a number of cases, which will be the number of times the user entered hand will be played against a random hand.
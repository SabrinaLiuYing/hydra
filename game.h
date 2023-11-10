#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include "card.h"
#include "head.h"
#include "player.h"
using namespace std;

class Game{
    public:
    Players play;     // A game have players
    Heads allhead;    // A game have heads on the table
    bool testMode;    // check if we will use testing mode
    bool res;         // check if in each round there is a reserve card or not
    bool swapRes;     // check if in each round there is a reserve card and need to be swap with hand card
    void initGame(int playerNum, bool testingmode);   // init a game with playerNum players
    void oneMoveOutputs(size_t whichPlayer, int move);  // output for a move title (Player a, you are holding a)
    bool oneMove(int move, size_t whichPlayer);   // play one move and might outputs some result and return whether the round should be end
    void clearGame();  // clear the memory of the game
    void checkReserve(size_t whichPlayer);  // if there is a reserve, add it into the draw.
    void pushDiscard(size_t whichPlayer);   // add all the discard to the draw with randomly sequences (if the draw is empty with no reserve)
    void outputCardNum(int num);  // out put the cardNum (J for 11, Q for 12, K for 13, A for 1)
    void testingMode(size_t whichPlayer);   // testing mode for testing
};

#endif

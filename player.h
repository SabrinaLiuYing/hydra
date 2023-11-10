#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include "card.h"
using namespace std;

class Player{               // a player have 2 cardSets and a reserve chance
    public:
    Cards discard;
    Cards draw;
    Card reserve;
    void init();            // initilize a player : there is nothing in the discard and draw
    int cardSum();          // return the total number of cards a player has, including draw, discard, and reserve.
    bool isWon();           // check if the card sum is equal to zero which means this player win
    void clearPlayer();     // clear the memory of player
};


class Players{
    public:
    vector<Player> pp;       // pp is a set of players
    void init(int num);      // init the set of players with num players
    int getPlayerNum();      // get the total number of players
    void clearPlayers();     // clear the memory of players
    bool gameOver();         // check if one of the players wins the game
    void playerOutput(size_t whichPlayer, int round, bool res);   // output the imformation of all the players
};

#endif

#ifndef __HEAD_H__
#define __HEAD_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include "card.h"
using namespace std;


class Head : public Cards{   // head is a childern class of Cards
    public:     
    bool lose;               // lose means that this head is taken as discard by some players
};

class Heads{
    public:
    vector<Head> headSet;
    int getHeadsNum();          // get the total number of heads
    int getNumWithoutLose();    // get the number of heads that remain on the desk
    void init();                // initialize the heads that there is no heads on the desk
    void clearHeads();          // clear the memory of heads
    void headsOutputs();        // output the information of all the heads
};

#endif

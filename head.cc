#include "head.h"

// see head.h for details
void Heads::headsOutputs(){
    std::cout << "Heads:" << std::endl;
    // for each heads
    for(size_t ii = 0; ii < headSet.size(); ii++){
        if(! headSet[ii].lose){      // only produce the imfomation for the heads that are on the desk
            std::cout << ii + 1 << ": ";

            // produce the number of the newest card of the head 
            int num = headSet[ii].getLastNum();
            // produce "J", "Q", "K", "A" for the cards that have number of 11, 12, 13, 1
            if(num == 11){
                std::cout << "J";
            }else if (num == 12){
                std::cout << "Q";
            }else if (num == 13){
                std::cout << "k";
            }else if (num == 1){
                std::cout << "A";
            }else{
                std::cout << num;
            }
            
            // produce the type of the newest card of the head and the total number of cards in this head
            std::cout << headSet[ii].getLastType();
            std::cout << " (" << headSet[ii].getNum() << ")" << std::endl;
        }
    }
}

// see head.h for details
int Heads::getHeadsNum(){
    return headSet.size();
}

// see head.h for details
int Heads::getNumWithoutLose(){
    int num = 0;
    for (size_t ii = 0; ii < headSet.size(); ii++){
        if(! headSet[ii].lose){
            num++;
        }
    }
    return num;
}

// see head.h for details
void Heads::init(){
    if(! headSet.empty()){
        clearHeads();
        vector<Head> temp;
        headSet = temp;
    }
}

// see head.h for details
void Heads::clearHeads(){
    if(headSet.empty()){
        return;
    }
    for(size_t ii = 0; ii < headSet.size(); ii++){
        headSet[ii].clearCard();
    }
    headSet.clear();
}
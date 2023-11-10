#include "card.h"

// For class Card

// see card.h for details
int Card::getNum(){
    return num;
}

// see card.h for details
char Card::getType(){
    return type;
}

// For class Cards

// see card.h for details
void Cards::copyCard(Cards cards){
    for(size_t ii = 0; ii < cards.cardSet.size(); ii ++){
        Card t;
        t.type = cards.cardSet[ii].getType();
        t.num = cards.cardSet[ii].getNum();
        cardSet.push_back(t);
    }
}

// see card.h for details
void Cards::basicCards(){
    // basicCards without jockers have number 1-13 (1 for A, 11 for J, 12 for Q, 13 for K) with four suite (S, H, C, D)
    for(int ii = 1; ii <= 13; ii ++){
        for(int jj = 0; jj < 4; jj++){
            Card temp;
            temp.num = ii;
            if(jj == 0){
                temp.type = 'S';
            }else if (jj == 1){
                temp.type = 'H';
            }else if (jj == 2){
                temp.type = 'C';
            }else if (jj == 3){
                temp.type = 'D';
            }
            cardSet.push_back(temp);
        }
    }

    // for joker, we let the number of the card to be 0 at first, and will change in the program.
    Card joker;
    joker.num = 0;
    joker.type = 'J';
    cardSet.push_back(joker);  
    cardSet.push_back(joker);  // there are two jokers in a formal cardSet
}

// see card.h for details
int Cards::getNum(){
    if(cardSet.empty()){
        return 0;
    }
    return cardSet.size();
}

// see card.h for details
void Cards::addCard(Card c){
    vector<Card> temp;
    temp.push_back(c);
    for(size_t i = 0; i < cardSet.size(); i++){
        temp.push_back(cardSet[i]);
    }
    cardSet.clear();
    cardSet = temp;
}

// see card.h for details
void Cards::clearCard(){
    cardSet.clear();
}

// see card.h for details
int Cards::getFirstNum(){
    return cardSet[0].getNum();
}

// see card.h for details
int Cards::getLastNum(){
    return cardSet[cardSet.size()-1].getNum();
}

// see card.h for details
void Cards::removeCard(){
    if(cardSet.empty()){
        return;
    }
    vector<Card> temp;
    for(size_t i = 1; i < cardSet.size(); i++){
        temp.push_back(cardSet[i]);
    }
    cardSet.clear();
    cardSet = temp;
}

// see card.h for details
char Cards::getFirstType(){
    return cardSet[0].getType();
}

// see card.h for details
char Cards::getLastType(){
    return cardSet[cardSet.size()-1].getType();
}

// see card.h for details
void Cards::random(){
    random_shuffle(cardSet.begin(), cardSet.end());
}

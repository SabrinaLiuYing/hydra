#ifndef __CARD_H__
#define __CARD_H__

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Card{
    public:
    int getNum();      // get the card number of a card they are 0-13
    char getType();    // get the card type of a card, they are "S,H,C,D,J"
    int num;           // the number of a card (a number of a joker is 0 at first)
    char type;         // the type of a card
};

class Cards{
    public:
    vector<Card> cardSet;           // cardSet is a set of cards
    void basicCards();              // adding an initial cardsets that contains 0-13 for each "S,H,C,D" and two jokers
    void clearCard();               // clear the memory of cardset
    int getNum();                   // get the number of cards in cardSet
    int getFirstNum();              // get the number of the first (the oldest) card in the cardSet
    char getFirstType();            // get the type of the first (the oldest) card in the cardSet
    int getLastNum();               // get the number of the last card (the one on the top) in the cardSet
    char getLastType();             // get the type of the last card (the one on the top) in the cardSet
    void addCard(Card c);           // add the card c in the begining of the cardSet (the oldest)
    void removeCard();              // remove the first (the oldest) card in the cardSet
    void random();                  // change the sequence of the cards in the cardSet randomly
    void copyCard(Cards cards);     // copy the cardSet of Cards cards to this cardSet 
};


#endif

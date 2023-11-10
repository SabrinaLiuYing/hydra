#include "player.h"

// For class Player

// see player.h for details
void Player::init(){
    //init discard
    if(! discard.cardSet.empty()){
        discard.clearCard();
        vector<Card> tempDis;
        discard.cardSet = tempDis;
    }
    //init draw
    if(! draw.cardSet.empty()){
        draw.clearCard();
        vector<Card> tempDraw;
        draw.cardSet = tempDraw;
    }
}

// see player.h for details
// since each time to check cardSum, the reserve card will go back to the draw,
//       thus we don't need to check the reserve card.
int Player::cardSum(){
    int sum = 0;
    sum += discard.getNum();
    sum += draw.getNum();
    return sum;
}

// see player.h for details
bool Player::isWon(){
    if(cardSum() == 0){
        return true;
    }

    return false;
}

// see player.h for details
void Player::clearPlayer(){
    discard.clearCard();
    draw.clearCard();
}

// see player.h for details
void Players::playerOutput(size_t whichPlayer, int round, bool res){
    std::cout << "Players:" << std::endl;
    // for each players
    for(size_t ii = 0; ii < pp.size(); ii++){
        std::cout << "Player " << ii + 1 << ": ";

        // outputs draw 
        if(whichPlayer == ii){     // for the player that in his round
            std::cout << pp[ii].cardSum() - round;
            std::cout << " (" << pp[ii].draw.getNum() - round << " draw, ";
        }else{                     // for the other players
            std::cout << pp[ii].cardSum();
            std::cout << " (" << pp[ii].draw.getNum() << " draw, ";
        }
        
        // outputs discard
        std::cout << pp[ii].discard.getNum() << " discard)";

        // outputs handing parts for player who is playing in this round
        if(whichPlayer == ii && round != 0){
            std::cout << " + 1 in hand, ";
            std::cout << round - 1 << " remaining, ";
            // check if there is a reserve 
            if(res){
                std::cout << "1 in reserve";
            }else{;
                std::cout << "0 in reserve";
            }
        }

        // outputs a new line for good looking
        std::cout << std::endl;
    }

    // outputs a new line for good looking
    std::cout << std::endl;
}

// see player.h for details
bool Players::gameOver(){
    for(size_t ii = 0; ii < pp.size(); ii++){
        if(pp[ii].isWon()){
            return true;
        }
    }
    return false;
}

// see player.h for details
void Players::init(int num){
    for(int ii = 0; ii < num; ii++){
        Player p;
        p.init();
        pp.push_back(p);
    }
}

// see player.h for details
int Players::getPlayerNum(){
    return pp.size();
}

// see player.h for details
void Players::clearPlayers(){
    for(int ii = 0; ii < getPlayerNum(); ii++){
        pp[ii].clearPlayer();
    }
    pp.clear();
}

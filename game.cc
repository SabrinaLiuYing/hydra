#include "game.h"

// see game.h for details 
void Game::pushDiscard(size_t whichPlayer){
    if(play.pp[whichPlayer].draw.getNum() == 0){
        if(res){
            checkReserve(whichPlayer);
        }else{
            play.pp[whichPlayer].discard.random();
            play.pp[whichPlayer].draw.copyCard(play.pp[whichPlayer].discard);
            play.pp[whichPlayer].discard.clearCard();
        }
    }
}

// see game.h for details 
void Game::outputCardNum(int num){
    if (num == 11){
        std::cout << "a J";
    }else if (num == 12){
        std::cout << "a Q";
    }else if (num == 13){
        std::cout << "a K";
    }else if (num == 1){
        std::cout << "an A";
    }else if (num == 8){
        std::cout << "an 8";
    }else{
        std::cout << "a " << num;
    }
}

// see game.h for details 
void Game::checkReserve(size_t whichPlayer){
    if(res){
        Card resCard;
        resCard.num = play.pp[whichPlayer].reserve.getNum();
        resCard.type = play.pp[whichPlayer].reserve.getType();
        play.pp[whichPlayer].draw.addCard(resCard);
        res = false;
        swapRes = false;
    }
}

// see game.h for details 
bool Game::oneMove(int move, size_t whichPlayer){
    // push discard if draw is empty with no reserve card
    pushDiscard(whichPlayer);

    // doing reserve
    if(move < 0){  // move < 0 means palyer whichPlayer put the hand card into reserve
        int resNum = play.pp[whichPlayer].draw.getFirstNum();
        char resType = play.pp[whichPlayer].draw.getFirstType();
        if(res == false){  // if there is no reserve card before
            res = true;
            play.pp[whichPlayer].reserve.num = resNum;
            play.pp[whichPlayer].reserve.type = resType;
            play.pp[whichPlayer].draw.removeCard();
            std::cout << "You put " ;
            if (resType == 'J'){
                std::cout << "a Jocker";
            }else{
                outputCardNum(resNum);
                std::cout << resType;
            }
            std::cout << " into reserve." << std::endl;
        }else{    // if there is a reserve card, then we swap the hand card with the reserve card
            swapRes = true;
            testingMode(whichPlayer);   // testing mode when swap with the reserve
            Card swapCard;
            swapCard.num = play.pp[whichPlayer].reserve.getNum();
            swapCard.type = play.pp[whichPlayer].reserve.getType();
            play.pp[whichPlayer].reserve.num = resNum;
            play.pp[whichPlayer].reserve.type = resType;
            play.pp[whichPlayer].draw.removeCard();
            play.pp[whichPlayer].draw.addCard(swapCard);
            // output swap
            std::cout << "You swap the reserve " ;
            if (resType == 'J'){
                std::cout << "Jocker with ";
            }else{
                outputCardNum(resNum);
                std::cout << resType << " with ";
            }
            if (play.pp[whichPlayer].draw.getFirstType() == 'J'){
                std::cout << "Jocker." << std::endl;
            }else{
                outputCardNum(play.pp[whichPlayer].draw.getFirstNum());
                std::cout << play.pp[whichPlayer].draw.getFirstType() << "." << std::endl;
            }
        }
        return false; // continue this round
    }

    // if player moves normally
    Card temp;  // copy the first card in the draw
    temp.num = play.pp[whichPlayer].draw.getFirstNum();
    temp.type = play.pp[whichPlayer].draw.getFirstType();
    
    if (allhead.headSet[move].getLastNum() < play.pp[whichPlayer].draw.getFirstNum() && allhead.headSet[move].getLastNum() != 1){
    // if lose
        std::cout << std::endl;  // output a new line for good looking
        std::cout << "You lose in this round." << std::endl;
        std::cout << std::endl;  // output a new line for good looking
        // find the oldest head on the desk, and it lose
        size_t oldest = 0;
        while(allhead.headSet[oldest].lose){
            oldest += 1;
        }
        allhead.headSet[oldest].lose = true;
        // push the oldest head and hand card into discard
        play.pp[whichPlayer].discard.copyCard(allhead.headSet[oldest]);
        play.pp[whichPlayer].discard.cardSet.push_back(temp);
        play.pp[whichPlayer].draw.removeCard();
        // check if there is a reserve, if so, put back reserve on draw
        checkReserve(whichPlayer);
        // produce two new head
        for (int i = 0; i < 2; i++){
            testingMode(whichPlayer);
            Head h;  // creat a new head
            Card c;  // copy the first card in the draw (after removing the hand card that is losed)
            c.num = play.pp[whichPlayer].draw.getFirstNum();
            c.type = play.pp[whichPlayer].draw.getFirstType();
            // if there is a jocker, we automatically regard this card as a card with number 2
            if (c.getType() == 'J'){
                c.num = 2;
            }
            h.cardSet.push_back(c);
            h.lose = false;   // this head is on the desk
            play.pp[whichPlayer].draw.removeCard();
            allhead.headSet.push_back(h);
        }
        return true;   // finish this round
    }else if( allhead.headSet[move].getLastNum() == play.pp[whichPlayer].draw.getFirstNum()){
    // if put the card with the same number
        std::cout << std::endl;     // output a new line for good looking
        std::cout << "You finish this round by putting on the head with the same number." << std::endl;
        std::cout << std::endl;     // output a new line for good looking
        allhead.headSet[move].cardSet.push_back(temp);
        play.pp[whichPlayer].draw.removeCard();
        return true;   // finish this round
    }else{ // move is valid or the number of hand card is 1
        allhead.headSet[move].cardSet.push_back(temp);
        play.pp[whichPlayer].draw.removeCard();
        return false;   // continue this round
    }
}

// see game.h for details 
void Game::clearGame(){
    play.clearPlayers();
    allhead.clearHeads();
}

// see game.h for details
void Game::testingMode(size_t whichPlayer){
    if(! testMode){
        return;
    }
    std::cout << "Do you want to use testing mode (intput Y for yes and N for no)" << std::endl;
    char test;
    std::cin >> test;
    if(test == 'Y'){
    // if we want to use the testing mode
        std::cout << "Card value? (input one of 2-10, J, Q, K, A or Jocker (jocker))" << std::endl;
        // read in card value
        int value = 0;
        char temp;
        string s;
        std::cin >> s;
        if(s == "Jocker" || s == "jocker"){    // Jocker is special as it is a string
            if(swapRes){    // when doing the swap testing mode
                play.pp[whichPlayer].reserve.num = 0;
                play.pp[whichPlayer].reserve.type = 'J';
            }else{          // when doing the initial and each move testing mode
                play.pp[whichPlayer].draw.cardSet[0].num = 0;
                play.pp[whichPlayer].draw.cardSet[0].type = 'J';
            }
            return; // we do not need to read in the type value
        }else{
            if (s == "10"){     // 10 is special as the lenth of string > 1
                value = 10;
            }
            temp = s[0];
        }

        // change the char into int in order to change the value of a card
        if(temp == 'J'){
            value = 11;
        }else if (temp == 'Q'){
            value = 12;
        }else if (temp == 'K'){
            value = 13;
        }else if (temp == 'A'){
            value = 1;
        }else{
            if (value != 10){
                value = temp - '0';
            }
            // invalid situation
            if (value < 2 || value > 10){
                std::cout << "YOUR INTPUT IS INVALID" << std::endl;
                std::cout << std::endl;    // output a new line for good looking
                testingMode(whichPlayer);  // recursion
                return;
            }
        }

        // change the num of the card
        if(swapRes){        // when doing the swap testing mode
            play.pp[whichPlayer].reserve.num = value;
        }else{              // when doing the initial and each move testing mode
            play.pp[whichPlayer].draw.cardSet[0].num = value;
        }
        
        std::cout << "Suit? (input one of S, H, C, D)" << std::endl;
        //read in the suit
        std::cin >> s;
        temp = s[0];
        // invalid situation
        if(s.size() > 1 || (temp != 'S' && temp != 'H' && temp != 'C' && temp != 'D')){
            std::cout << "YOUR INTPUT IS INVALID" << std::endl;
            std::cout << std::endl;     // output a new line for good looking
            testingMode(whichPlayer);   // recursion
            return;
        }

        // change the type of the card
        if(swapRes){        // when doing the swap testing mode
            play.pp[whichPlayer].reserve.type = temp;
        }else{              // when doing the initial and each move testing mode
            play.pp[whichPlayer].draw.cardSet[0].type = temp;
        }
    }else if (test == 'N'){
    // if we do not want to use the testing mode
        return;     // we will use the initial data
    }else{
    // invalid situations
        std::cout << "YOUR INTPUT IS INVALID" << std::endl;
        std::cout << std::endl;     // output a new line for good looking
        testingMode(whichPlayer);   // recursion
        return;
    }
}

// see game.h for details 
void Game::oneMoveOutputs(size_t whichPlayer, int move){
    // output heads information
    allhead.headsOutputs();
    std::cout << std::endl;     // output a new line for good looking
    
    // output player information
    play.playerOutput(whichPlayer, move, res);
    testingMode(whichPlayer);   // testing mode

    // output move information
    std::cout << "Player " << whichPlayer + 1 << ", you are holding ";
    if(play.pp[whichPlayer].draw.getFirstType() == 'J'){
        std::cout << "a Jocker";
    }else{
        outputCardNum(play.pp[whichPlayer].draw.getFirstNum());
        std::cout << play.pp[whichPlayer].draw.getFirstType();
    }
    std::cout << ". Your move? (input 0 if you want to reserve this card)" << std::endl;

}

// see game.h for details 
void Game::initGame(int playerNum, bool tMode){
    //check testMode
    testMode = tMode;
    // initial player
    play.init(playerNum);
    Cards allCard;
    // put all cards together and change the sequence randomly
    for (int i = 0; i < playerNum; i++){
        allCard.basicCards();
    }
    allCard.random();
    // divide the cards for each player
    int cards = 0;
    for (int i = 0; i < playerNum; i++){
        Cards temp;
        for(int j = 0; j < allCard.getNum() / playerNum; j++){
            temp.cardSet.emplace_back(allCard.cardSet[cards]);
            cards += 1;
        }
        play.pp[i].draw = temp;
    }
    allCard.clearCard();

    // initial heads
    size_t whichPlayer = 0;
    res = false;        // there is no reserve card in this round
    swapRes = false;    // there is no need to swap reserve card
    testingMode(whichPlayer); // testing mode
    Head h;
    Card c;
    c.num = play.pp[whichPlayer].draw.getFirstNum();
    c.type = play.pp[whichPlayer].draw.getFirstType();
    if (c.getType() == 'J'){    // if a jocker to be the new header, we let its' num to be 2
        c.num = 2;
    }
    h.cardSet.push_back(c);
    h.lose = false;     // head h is on the desk
    play.pp[0].draw.removeCard();
    allhead.headSet.push_back(h);
}

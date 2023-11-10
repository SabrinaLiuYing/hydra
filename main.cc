#include <iostream>
#include <vector>
#include <algorithm>
#include "card.h"
#include "player.h"
#include "head.h"
#include "game.h"
using namespace std;

int main(int argc, char * argv[]){
    // testingmode
    bool testingmode = false;
    for (int i = 1; i < argc; ++i) {
        string command = argv[i];
        if (command == "-testing") {
            testingmode = true;
        }
    }
    // get the number of players
    std::cout << "How many players?" << std::endl;
    int p;
    std::cin >> p;
    std::cout << std::endl;
    // invalid information
    if (p <= 1){
        std::cout << "ERROR: PLAYER NUMBER IS NOT ENOUGH TO PLAY" << std::endl;
        return 1;
    }

    // init a game gg and output the initial information 
    Game gg;
    gg.initGame(p, testingmode);
    gg.allhead.headsOutputs();
    std::cout << std::endl;
    gg.play.playerOutput(1, 0, false);
    int round = 1;  // there is one head created and round 1
    bool gameover = false;  // gameover shows that if one of the player wins
    
    // start game for each round
    while(1){
        // check if this game is over
        if(gameover){
            break;
        }

        // output players information;
        size_t whichPlayer = round % gg.play.getPlayerNum(); // determine the player in this round
        std::cout << "Player " << whichPlayer + 1 << ", it is your turn." << std::endl;
        std::cout << std::endl;
        int more_move = 0;     // more_move records the number of moves the player remain to play after changing the discard to draw
        int value_ii = 0;       // value_ii records the number of draw cards if it is less than the number of heads
        gg.pushDiscard(whichPlayer);    // check if there is a need to move the discard to draw
        int d_num = gg.play.pp[whichPlayer].draw.getNum();
        int h_num = gg.allhead.getNumWithoutLose();
        if(d_num <  h_num){
            more_move =  h_num - d_num;
            value_ii = d_num;
        }

        //for each move
        for(int ii =  h_num; ii > 0; ii--){
            // prepare for this move
            if(value_ii != 0){
            // check if the draw cards is not enough to play this round, if yes, change ii to value_ii 
                ii = value_ii;
                value_ii = 0;
            }
            gg.pushDiscard(whichPlayer);   // check if there is a need to move the discard to draw

            // output information for each move and read move
            gg.oneMoveOutputs(whichPlayer, ii);
            int move;                   // position of move
            std::cin >> move;           // read in a position of move
            if(cin.eof()){              // error situations
                gameover = true;
                break;
            }
            while(move < 1  || move > gg.allhead.getHeadsNum() || gg.allhead.headSet[move - 1].lose){
            // invalid situations recursion (move on the heads that are not on the table)
                if (move == 0 && gg.allhead.getNumWithoutLose() > 1){
                // situation of reserve which is valid (if the head number > 2)
                    break;
                }
                std::cout << "YOUR MOVE IS INVALID, MOVE AGAIN. Your move is:" << std::endl;
                std::cin >> move;
            }

            // special situation of jocker, player need to determine the value of the Jocker.
            if(gg.play.pp[whichPlayer].draw.getFirstType() == 'J'){
                std::cout << "Joker value?" << std::endl;
                int valueJ = 0;
                char temp;
                string temp_str;
                std::cin >> temp_str;
                if(temp_str == "10"){
                    valueJ = 10;
                }else if(temp_str.size() > 1){
                    std::cout << "INVALID INPUT" << std::endl;
                    ii += 1;
                    continue;
                }
                temp = temp_str[0];
                if (temp == 'J' || temp == 'j'){
                    valueJ = 11;
                }else if(temp == 'Q' || temp == 'q'){
                    valueJ = 12;
                }else if(temp == 'K' || temp == 'k'){
                    valueJ = 13;
                }else if(temp == 'A' || temp == 'a'){
                    valueJ = 1;
                }else{
                    if(valueJ != 10){
                        valueJ = temp - '0';
                        if (valueJ < 1 || valueJ > 13){
                            std::cout << "INVALID INPUT" << std::endl;
                            ii += 1;
                            continue;
                        }
                    }
                }
                gg.play.pp[whichPlayer].draw.cardSet[0].num = valueJ; // change the num of card jocker
            }
            
            // run this move
            if (gg.oneMove(move - 1, whichPlayer)) {
            // if we need to end this move for or place the hand card on the head that have the lasted card with the same number
                gg.checkReserve(whichPlayer);   // if there is a reserve move to draw
                if(gg.play.gameOver()){
                // check if player whichPlayer wins
                    std::cout << "Player " << whichPlayer + 1 << " wins!" << std::endl;
                    gameover = true;
                }
                break;          // end this round
            }

            // if we swap the reserve, we need to add one move for the card that swap to hand
            if(gg.swapRes){
                ii += 1;
                gg.swapRes = false;
            }

            // for the last move in each round
            if(ii == 1){
                gg.checkReserve(whichPlayer);         // if there is a reserve move to draw

                // if draw card is empty, and have more moves to play in this round
                if(more_move > 0){
                    int draw_num = gg.play.pp[whichPlayer].draw.getNum();
                    // if there is a reserve, we will play this reserve first
                    if(draw_num != 0){
                        ii += 1;
                        continue;
                    }
                    gg.pushDiscard(whichPlayer);       // check if there exist discard then move discard to draw
                    // check if the remaining draw cards are less the more_move, if so, more_moves is the number of draw cards
                    if(more_move > gg.play.pp[whichPlayer].draw.getNum()){
                        more_move = gg.play.pp[whichPlayer].draw.getNum();
                    }
                    // outputs for player to know that we change the discard to draw and
                    std::cout << std::endl;  // output a new line for good looking
                    std::cout << "Replace your draw cards with discard cards, and you have " << more_move;
                    std::cout << " moves left in this round" << std::endl;
                    ii = more_move + 1;
                    more_move = 0;
                }
            }

            std::cout << std::endl;  // output a new line for good looking

            //check if playing player wins
            if(gg.play.gameOver()){
                std::cout << "Player " << whichPlayer + 1 << " wins!" << std::endl;
                std::cout << std::endl;  // output a new line for good looking
                gameover = true;
                break;
            }
        }
        
        // after each round, we outputs heads and player information
        gg.allhead.headsOutputs();
        std::cout << std::endl;   // output a new line for good looking
        gg.play.playerOutput(whichPlayer, 0, gg.res);
        round ++;
    }

    gg.clearGame();  // clear the memory of game gg
    std::cout << "GAMEOVER" << std::endl; 
    return 0;
}

//  game.cpp

#include "game.hpp"

using namespace std;

box boxS[10];
bigBox boxB[2] = {{true}, {false}};

//bool endGame;
bool turnFirstPerson;

box chooseBox() {
    return boxS[1];
}
bool chooseDirection () {
    return 0;
}
void moveStone() {
    
}
void distributeStone() {
    
}
void gameOver() {
    
}
void gameLoop() {
    //endGame = false;
    init();
    loadMedia();
    bool quit = false;
    
    turnFirstPerson = true;
    int turn = 0;
    
    while (!quit) {
        
        turn ++;
        if (turn % 2 == 0) {
            turnFirstPerson = false;
        }
        else {
            turnFirstPerson = true;
        }
        ///////////////////////////////////////
        ////////logic game written here////////
        ///////////////////////////////////////
        
        chooseBox();
        chooseDirection();
        moveStone();
        // dai quan
        distributeStone();
        // endGame
        gameOver();
        
        
        //////////////////////////////////////
        ////////SDL library used here/////////
        //////////////////////////////////////
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        
        SDL_RenderClear( gRenderer);
        SDL_RenderCopy( gRenderer, gTable, NULL, NULL);
        //showHand(handPos.x, handPos.y);
        SDL_RenderPresent( gRenderer );
    }
    close();
}

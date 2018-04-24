//
//  game.cpp
//

#include "game.hpp"

bool gEndGame;
bool gTurnFirstPerson;
int gFirstPlayerScore = 0;
int gSecondPlayerScore = 0;

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
    ////////INIT FOR SDL////////
    init();
    loadMedia();
    bool quit = false;
    ////////INIT FOR GAME LOOP////////
    gEndGame = false;
    gTurnFirstPerson = true;
    int turn = 0;
    
    /////////////////////////////////////////////////////
    //////////           GAME LOOP           ////////////
    /////////////////////////////////////////////////////
    while (!quit) {
        turn ++;
        if (turn % 2 == 0) {
            gTurnFirstPerson = false;
        }
        else {
            gTurnFirstPerson = true;
        }
        
        
//        int* a, *b;
//
//        while( SDL_PollEvent( &e ) != 0 )
//        {
//            //User requests quit
//            if( e.type == SDL_QUIT )
//            {
//                quit = true;
//            }
//
//            //Handle button events
//            for( int i = 0; i < TOTAL_BUTTONS; ++i )
//            {
//                gButtons[ i ].handleEvent( &e, a, b );
//            }
//        }
        
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        
        //Render buttons
        for( int i = 0; i < TOTAL_BUTTONS; ++i )
        {
            gButtons[ i ].render();
        }
        
        
        
        
        ///////////////////////////////////////
        /////// logic game written here ///////
        ///////////////////////////////////////
        if (gEndGame) {
            gameOver();
        }
        else {
            chooseBox();
            chooseDirection();
            moveStone();
            // dai quan
            distributeStone();
            
        }
        //////////////////////////////////////
        /////// SDL library used here ////////
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
        showGraphic();
        SDL_RenderPresent( gRenderer );
    }
    close();
}

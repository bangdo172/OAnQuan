//
//  game.cpp
//

#include "game.hpp"

bool gEndGame;
bool gTurnFirstPerson;
int gFirstPlayerScore = 0;
int gSecondPlayerScore = 0;


void chooseBoxAndDirection (int mouseEvent) {
    if (mouseEvent == 1) {
        
    }
    else if (mouseEvent == 2) {
        
    }
}
void moveStone() {
    
}
void distributeStone() {
    
}
void gameOver() {
    
}
void gameLoop() {
    ////////INIT FOR GAME LOOP////////
    gEndGame = false;
    gTurnFirstPerson = true;
    int turn = 0;
    int mouseEvent = 0;
    /////////////////////////////////////////////////////
    //////////           GAME LOOP           ////////////
    /////////////////////////////////////////////////////
    while (! gEndGame) {
        turn ++;
        if (turn % 2 == 0) {
            gTurnFirstPerson = false;
        }
        else {
            gTurnFirstPerson = true;
        }
        std::cout << turn << std::endl;

        ///////////////////////////////////////
        /////// logic game written here ///////
        ///////////////////////////////////////
        if (gEndGame) {
            gameOver();
        }
        else {
            chooseBoxAndDirection(mouseEvent);
            moveStone();
            distributeStone();
        }
        //////////////////////////////////////
        /////// SDL library used here ////////
        //////////////////////////////////////
        ////////INIT FOR SDL////////
        init();
        loadMedia();
        bool quit = false;
        while (! quit) {
            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                int a, b;
                SDL_GetMouseState(&a, &b);
                for( int i = 0; i < TOTAL_BUTTONS; ++i )
                {
                    gButtonsLeft[ i ].handleEvent( &e, a, b, mouseEvent );
                    gButtonsRight[ i ].handleEvent(&e, a, b, mouseEvent);
                }
            }
            SDL_RenderClear( gRenderer);
            SDL_RenderCopy( gRenderer, gTable, NULL, NULL);
            showGraphic();
            
            for( int i = 0; i < TOTAL_BUTTONS; ++i )
            {
                gButtonsLeft[ i ].render();
                gButtonsRight[ i ].render();
            }
            SDL_RenderPresent( gRenderer );
        }
    }
    close();
}

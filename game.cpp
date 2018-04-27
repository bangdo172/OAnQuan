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
    int mouseEvent = 0;
    bool quit = false;
    init();
    loadMedia();
    /////////////////////////////////////////////////////
    //////////           GAME LOOP           ////////////
    /////////////////////////////////////////////////////
    while ((!gEndGame) && (!quit)) {
        if (gTurn % 2 == 0) {
            gTurnFirstPerson = false;
        }
        else {
            gTurnFirstPerson = true;
        }
        std::cout << gTurn << std::endl;

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
        
            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                int a, b;
                SDL_GetMouseState(&a, &b);
                for( int i = gTurn % 2 * 5; i < gTurn % 2 * 5 + 5; ++i )
                {
                    gButtonsLeft[ i ].handleEvent(&e, a, b, mouseEvent);
                    gButtonsRight[ i ].handleEvent(&e, a, b, mouseEvent);
                }
            }
            SDL_RenderClear( gRenderer);
            SDL_RenderCopy( gRenderer, gGround, NULL, NULL);
            SDL_RenderCopy( gRenderer, gTable, NULL, NULL);
            showGraphic();
            
            for( int i = gTurn % 2 * 5; i < gTurn % 2 * 5 + 5; ++i )
            {
                gButtonsLeft[ i ].render();
                gButtonsRight[ i ].render();
            }
            SDL_RenderPresent( gRenderer );
        }
    close();
}

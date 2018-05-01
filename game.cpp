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
    initGraphic();
    //loadMedia();
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
        SDL_RenderCopy( gRenderer, gTable, NULL, NULL);
        showGraphic();
    // render text "game o an quan"; gTextTexture.render(posX of Destination, posY of Destination)
        gTextTexture.render(100, 675);
        for (int i = 0; i < 12; i ++) {
            for (int j = 0; j < 21; j ++) {
                if (boxS[i].numStone == j + 1) {
                    gNumStoneText[j].render(boxS[i].boxSRect.x + 110, boxS[i].boxSRect.y + 110);
                }
            }
            if (boxS[i].numStone >= 21) {
                gNumStoneText[20].render(boxS[i].boxSRect.x, boxS[i].boxSRect.y);
            }
            if (boxS[i].numStone == 0) {
                gNumStoneText[0].render(boxS[i].boxSRect.x , boxS[i].boxSRect.y);
            }
        }
        for( int i = gTurn % 2 * 5; i < gTurn % 2 * 5 + 5; ++i )
        {
            gButtonsLeft[ i ].render();
            gButtonsRight[ i ].render();
        }
        SDL_RenderPresent( gRenderer );
    }
    close();
}

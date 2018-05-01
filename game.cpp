//
//  game.cpp
//

#include "game.hpp"

bool gEndGame;
bool gTurnFirstPerson;
int gFirstPlayerScore = 0;
int gSecondPlayerScore = 0;
int nextBox(int order, bool& left)
{
    if (left)
    {
        if (order == 0)
        {
            left = false;
            order = 11;
        }
        else if (order == 11)
        {
            order = 0;
            left = false;
        }
        else if (order < 6)
        {
            order--;
        }
        else
        {
            order++;
        }
    }
    else
    {
        if (order == 5)
        {
            order = 6;
            left = true;
        }
        else if (order == 6)
        {
            left = true;
            order = 5;
        }
        else if (order < 5)
        {
            order++;
        }
        else
        {
            order--;
        }
    }
    return order;
}
void performancedTurn (int order, bool left) {
    int quantity = boxS[order].numStone;
    boxS[order].numStone = 0;
    int nextOrder = order + 1;
    while (quantity--)
    {
        order = nextBox(order, left);
        boxS[order].numStone++;
    }
    order = nextBox(order, left);
    if (boxS[order].numStone != 0)
    {
        order = nextBox(order, left);
        //SDL_Delay(5000);
        //performancedTurn(order, left);
    }
//    while (boxS[nextOrder].numStone != 0) {
//        
//        while (quantity--)
//        {
//            order = nextBox(order, left);
//            boxS[order].numStone++;
//        }
//        order = nextBox(order, left);
//        if (boxS[order].numStone != 0)
//        {
//            order = nextBox(order, left);
//            //SDL_Delay(5000);
//            //performancedTurn(order, left);
//        }
//        nextOrder = order + 1;
//    }
    
    /*int nextBoxOrder = boxChosen.order;
    if (gTurn % 2 == 1) {
        if (left) {
            while ((nextBoxOrder != 0) && (nextBoxOrder != 6)) {
                int presentOrder = boxChosen.order;
                int numStoneTemp = boxChosen.numStone;
                boxChosen.numStone = 0;
                for (int i = 1; i <= numStoneTemp; i ++) {
                    if (presentOrder == 0) {
                        presentOrder += 12;
                    }
                    boxS[-- presentOrder].numStone --;
                }
                presentOrder --;
                boxChosen = boxS[presentOrder];
                nextBoxOrder = boxChosen.order;
            }
        }
        else {
            while ((nextBoxOrder != 4) && (nextBoxOrder != 10)) {
                int presentOrder = boxChosen.order;
                int numStoneTemp = boxChosen.numStone;
                boxChosen.numStone = 0;
                for (int i = 1; i <= numStoneTemp; i ++) {
                    if (presentOrder == 11) {
                        presentOrder -= 12;
                    }
                    boxS[++ presentOrder].numStone --;
                }
                presentOrder ++;
                boxChosen = boxS[presentOrder];
                nextBoxOrder = boxChosen.order;
            }
        }
    }
    else {
        if (left) {
            while ((nextBoxOrder != 4) && (nextBoxOrder != 10)) {
                int presentOrder = boxChosen.order;
                int numStoneTemp = boxChosen.numStone;
                boxChosen.numStone = 0;
                for (int i = 1; i <= numStoneTemp; i ++) {
                    if (presentOrder == 11) {
                        presentOrder -= 12;
                    }
                    boxS[++ presentOrder].numStone --;
                }
                presentOrder ++;
                boxChosen = boxS[presentOrder];
                nextBoxOrder = boxChosen.order;
            }
        }
        else {
            while ((nextBoxOrder != 0) && (nextBoxOrder != 6)) {
                int presentOrder = boxChosen.order;
                int numStoneTemp = boxChosen.numStone;
                boxChosen.numStone = 0;
                for (int i = 1; i <= numStoneTemp; i ++) {
                    if (presentOrder == 0) {
                        presentOrder += 12;
                    }
                    boxS[-- presentOrder].numStone --;
                }
                presentOrder --;
                boxChosen = boxS[presentOrder];
                nextBoxOrder = boxChosen.order;
            }
        }
    }*/
}

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
            //bool left = false;
            //performancedTurn(boxS[3], left);
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
        SDL_Delay(500);
        //int order = 0;
        performancedTurn(6, true);
        
    }
    close();
}

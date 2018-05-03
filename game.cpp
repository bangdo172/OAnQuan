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
    if (!quantity)
    {
        return;
    }
    while (quantity--)
    {
        handPos.x = boxS[order].boxSRect.x;
        handPos.y = boxS[order].boxSRect.y;
        int nextB = nextBox(order, left);
        do
        {
            showGraphic();
            if (moveHandTo(order, nextB))
            {
                order = nextB;
                boxS[order].numStone++;
                showGraphic();
                SDL_RenderCopy(gRenderer, gHand, NULL, &handPos);
                SDL_RenderPresent( gRenderer );
                break;
            }
            SDL_RenderPresent( gRenderer );
        }
        while (true);
    }
    bool take = false;
    do
    {
        order = nextBox(order, left);
        if ((boxS[order].numStone == 0) && (boxS[order + 1].numStone != 0) && (order != 11) && (order != 5))
        {
            order = nextBox(order, left);
            if (gTurn % 2)
            {
                boxP2.numStone += boxS[order].numStone;
            }
            else
            {
                boxP1.numStone += boxS[order].numStone;
            }
            
            boxS[order].numStone = 0;
            if ((order == 11) && gBigStoneExist[0]) {
                if (gTurn % 2 == 0) {
                    boxP1.numStone += 10;
                }
                else {
                    boxP2.numStone += 10;
                }
                gBigStoneExist[0] = false;
            }
            if ((order == 5) && gBigStoneExist[1]) {
                if (gTurn % 2 == 0) {
                    boxP1.numStone += 10;
                }
                else {
                    boxP2.numStone += 10;
                }
                gBigStoneExist[1] = false;
            }
            take = true;
        }
        else
        {
            break;
        }
    }
    while (true);
    if (!take && boxS[order].numStone != 0 && order != 5 && order != 11)
    {
        //SDL_Delay(5000);
        performancedTurn(order, left);
    }
    
    if (boxS[0].numStone == 0 && boxS[1].numStone == 0 && boxS[2].numStone == 0 && boxS[3].numStone && boxS[4].numStone == 0) {
        for (int i = 0; i < 5; i ++) {
            boxS[i].numStone ++;
        }
        boxP1.numStone -= 5;
    }
    if (boxS[6].numStone == 0 && boxS[7].numStone == 0 && boxS[8].numStone == 0 && boxS[9].numStone && boxS[10].numStone == 0) {
        for (int i = 6; i < 11; i ++) {
            boxS[i].numStone ++;
        }
        boxP1.numStone -= 5;
    }
}

void chooseBoxAndDirection (int mouseEvent) {
    if (mouseEvent == 1) {
        
    }
    else if (mouseEvent == 2) {
        
    }
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
        showGraphic();   // 1
        
        ///render buttons
        for( int i = gTurn % 2 * 5; i < gTurn % 2 * 5 + 5; ++i )
        {
            gButtonsLeft[ i ].render();
            gButtonsRight[ i ].render();
        }
        SDL_RenderPresent( gRenderer );
    }
    close();
}

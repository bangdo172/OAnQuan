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
    // endGame
    // dai dan // chua chay
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
        // show close hand
        showGraphic();
        SDL_RenderCopy(gRenderer, gHand1, NULL, &handPos);
        SDL_RenderPresent( gRenderer );
        SDL_Delay(100);
        
        // move close hand
        do
        {
            showGraphic();
            if (moveHandTo(order, nextB))
            {
                // show open hand
                order = nextB;
                boxS[order].numStone++;
                showGraphic();
                SDL_RenderCopy(gRenderer, gHand2, NULL, &handPos);
                SDL_RenderPresent( gRenderer );
                SDL_Delay(50);
                break;
            }
            SDL_RenderPresent( gRenderer );
            SDL_Delay(10);
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
    
    
}

void chooseBoxAndDirection (int mouseEvent) {
    if (mouseEvent == 1) {
        
    }
    else if (mouseEvent == 2) {
        
    }
}

void distributeStone() {
    if ((gTurn % 2 == 0 ) &&(boxS[0].numStone == 0) && (boxS[1].numStone == 0) && (boxS[2].numStone == 0) && (boxS[3].numStone == 0) && (boxS[4].numStone == 0)) {
        for (int i = 0; i < 5; i ++) {
            boxS[i].numStone ++;
        }
        boxP1.numStone -= 5;
    }
    if ((gTurn % 2 == 1) && (boxS[6].numStone == 0) && (boxS[7].numStone == 0) && (boxS[8].numStone == 0) && (boxS[9].numStone == 0) && (boxS[10].numStone == 0)) {
        for (int i = 6; i < 11; i ++) {
            boxS[i].numStone ++;
        }
        boxP2.numStone -= 5;
    }
}
void gameOver() {
    
    for (int i = 0; i < 12; i ++) {
        if (i < 6) {
            boxP1.numStone += boxS[i].numStone;
        }
        else {
            boxP2.numStone += boxS[i].numStone;
        }
        boxS[i].numStone = 0;
    }
    SDL_RenderClear( gRenderer);
    SDL_RenderCopy(gRenderer, gEndGameBG, NULL, NULL);
    gFont = TTF_OpenFont( "font.ttf", 70 );
    gTextTexture.loadFromRenderedText( ((boxP1.numStone == boxP2.numStone) ? ("2 PLAYERS DRAW!") : ((boxP1.numStone > boxP2.numStone) ? ("Player 1 WIN!") : ("Player 2 WIN!")) ) , textColor ) ;
    gTextTexture.render(250, 250);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(10000);
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
    //
    while ( (!quit)) {
        distributeStone();
        
        if ( ((boxS[5].numStone == 0 && boxS[11].numStone == 0) || boxP1.numStone < 0 || boxP2.numStone < 0) && !(gBigStoneExist[0] || gBigStoneExist[1]) ) {
            gameOver();
            
            break;
        }
        
        while(( SDL_PollEvent( &e ) != 0 ) && (!gEndGame))
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

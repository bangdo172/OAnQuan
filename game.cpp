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
        moveHandTo(boxS[order].order);
        order = nextBox(order, left);
        boxS[order].numStone++;
        //moveHandTo(boxS[order].order);
    }
    bool take = false;
    do
    {
        order = nextBox(order, left);
        if (boxS[order].numStone == 0)
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
        showGraphic();
        // render text "game o an quan"; gTextTexture.render(posX of Destination, posY of Destination)
        
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

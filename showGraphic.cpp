//
//  showGraphic.cpp
//

#include "showGraphic.hpp"

bool init()
{
    bool success = true;
    gWindow = SDL_CreateWindow( "O An Quan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        success = false;
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    gStone = loadTexture( "stone.png" );
    gTable = loadTexture( "table.png" );
    gBigStone = loadTexture("bigStone.jpg");
    gHand = loadTexture("hand.png");
    gLeftArrow = loadTexture("left.png");
    gRightArrow = loadTexture("right.png");
    
    return success;
}

void close()
{
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    SDL_FreeSurface( loadedSurface );
    return newTexture;
}

void showHand (SDL_Rect handPos) {
    handPos.w = 100;
    handPos.h = 100;
    SDL_RenderCopy(gRenderer, gHand, NULL, &handPos);
}

void showStone(SDL_Rect stone) {
    stone.w = 20;
    stone.h = 20;
    SDL_RenderCopy (gRenderer, gStone, NULL, &stone);
}

void showArrow (SDL_Rect leftArrow, SDL_Rect rightArrow) {
    leftArrow.w = 100;
    leftArrow.h = 100;
    rightArrow.w = 100;
    rightArrow.h = 100;
    leftArrow.x = 400;
    leftArrow.y = 400;
    rightArrow.x = leftArrow.x + BOXWIDTH/2;
    rightArrow.y = leftArrow.y ;
    SDL_RenderCopy(gRenderer, gLeftArrow, NULL, &leftArrow);
    SDL_RenderCopy(gRenderer, gRightArrow, NULL, &rightArrow);
}

void showGraphic() {
    showHand(handPos);
    showStone(stone);
    showArrow(leftArrow, rightArrow);
}

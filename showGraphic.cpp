//
//  showGraphic.cpp

#include "showGraphic.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "SDL_ttf.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define POSX1 100
#define POSY1 100
#define BOXWIDTH 100
#define BOXHEIGHT 100

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* gStone = NULL;
SDL_Texture* gTable = NULL;
SDL_Texture* gBigStone = NULL;
SDL_Texture* gHand = NULL;

SDL_Rect handPos;
SDL_Rect stone;

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture( std::string path );

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

void showHand (int hand_X, int hand_Y) {
    handPos.x = hand_X;
    handPos.y = hand_Y;
    SDL_RenderCopy(gRenderer, gHand, NULL, &handPos);
}

void showStone() {
    
}

void initShowGraphic() {
    init();
    loadMedia();
    bool quit = false;
    SDL_Event e;
    handPos.w = 100;
    handPos.h = 100;
    handPos.x = 640;
    handPos.y = 320;
    
    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        
        SDL_RenderClear( gRenderer);
        SDL_RenderCopy( gRenderer, gTable, NULL, NULL);
        showHand(handPos.x, handPos.y);
        SDL_RenderPresent( gRenderer );
    }
    close();
}

void showGraphic() {

}
/*
 void drawBoxStones(box boxS) {
 
 stone.w = 20;
 stone.h = 20;
 stone.x = boxS.posX;
 stone.y = boxS.posY;
 
 SDL_RenderCopy( gRenderer, gStone, NULL, &stone);
 }
 
 void drawBigBoxStones(bigBox& boxBig)
 {
 SDL_Rect bigStone;
 bigStone.w = 40;
 bigStone.h = 40;
 if (boxBig.posLeft == true) {
 bigStone.x = 100;
 }
 else {
 bigStone.x = 1100;
 }
 bigStone.y = 330;
 SDL_RenderCopy(gRenderer, gBigStone, NULL, &bigStone);
 }
*/

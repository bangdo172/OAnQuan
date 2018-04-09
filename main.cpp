//#include "graphic.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "SDL_ttf.h"

using namespace std;
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define POSX1 100
#define POSY1 100
#define BOXWIDTH 100
#define BOXHEIGHT 100                     	

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* gStone = NULL;
SDL_Texture* gTable = NULL;
SDL_Texture* gBigStone = NULL;
SDL_Texture* gHand = NULL;


class box {
public:
    int posX, posY, numStone;
    box(int, int, int);
    box(){};
};

box::box(int x,int y, int num) {
    posX = x;
    posY = y;
    numStone = num;
}

box boxS[10];

class bigBox
{
public:
    int posX, posY, numStone, bigStone;
    bool posLeft;
    bigBox(bool pos) : numStone(0), bigStone(1), posLeft(pos) {};
};
bigBox boxB[2] = {{true}, {false}};

SDL_Rect handPos;

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture( std::string path );

bool init()
{
    bool success = true;
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

SDL_Rect stone;
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
void showGraphic() {
    init();
    loadMedia();
    bool quit = false;
    SDL_Rect handPos;
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
        
        SDL_RenderClear( gRenderer );
        SDL_RenderCopy( gRenderer, gTable, NULL, NULL );
        
        drawBigBoxStones(boxB[0]);
        drawBigBoxStones(boxB[1]);
        SDL_RenderCopy(gRenderer, gHand, NULL, &handPos);
        SDL_RenderPresent( gRenderer );
    }
    close();
}


int main (int argc, char* argv[]) {
    showGraphic();
    return 0;
}




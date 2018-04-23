//
// Game O an quan
// by Bang Do

#include "game.hpp"
#include "box.hpp"
#include "showGraphic.hpp"


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* gStone = NULL;
SDL_Texture* gTable = NULL;
SDL_Texture* gBigStone = NULL;
SDL_Texture* gHand = NULL;
SDL_Texture* gRightArrow = NULL;
SDL_Texture* gLeftArrow = NULL;

SDL_Rect handPos;
SDL_Rect stone;
SDL_Rect rightArrow;
SDL_Rect leftArrow;
SDL_Event e;

box boxS[10];
bigBox boxB[2] = {{true}, {false}};


int main (int argc, char* argv[]) {
    
    gameLoop();
    return 0;
}

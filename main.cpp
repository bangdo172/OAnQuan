//
// Game O an quan
// by Bang Do

#include "game.hpp"
#include "box.hpp"
#include "showGraphic.hpp"


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* gStone1 = NULL;
SDL_Texture* gStone2 = NULL;
SDL_Texture* gStone3 = NULL;
SDL_Texture* gStone4 = NULL;
SDL_Texture* gStone5 = NULL;
SDL_Texture* gStone6 = NULL;
SDL_Texture* gStone7 = NULL;
SDL_Texture* gStone8 = NULL;
SDL_Texture* gStone9 = NULL;
SDL_Texture* gStone10 = NULL;
SDL_Texture* gStone11 = NULL;
SDL_Texture* gStone12 = NULL;
SDL_Texture* gStone13 = NULL;
SDL_Texture* gStone14 = NULL;
SDL_Texture* gStone15 = NULL;
SDL_Texture* gStone16 = NULL;
SDL_Texture* gStone17 = NULL;
SDL_Texture* gStone18 = NULL;
SDL_Texture* gStone19 = NULL;
SDL_Texture* gStone20 = NULL;
SDL_Texture* gStone21 = NULL;

SDL_Texture** gStoneTable = NULL;

//SDL_Texture* gStone;
//void initgStone() {
//    for (int i = 0; i < 21; i ++) {
//
//    }
//}
SDL_Texture* gTable = NULL;
SDL_Texture* gBigStone = NULL;
SDL_Texture* gHand = NULL;
SDL_Texture* gRightArrow = NULL;
SDL_Texture* gLeftArrow = NULL;

TTF_Font *gFont = NULL;

LTexture gTextTexture;
LTexture gTextTexture1;
LTexture gTextTexture2;
LTexture gTextTexture3;
LTexture gTextTexture4;
LTexture gTextTexture5;
LTexture gTextTexture6;
LTexture gTextTexture7;
LTexture gTextTexture8;
LTexture gTextTexture9;
LTexture gTextTexture10;


SDL_Rect gSpriteClipsLeft[ BUTTON_SPRITE_TOTAL ];
SDL_Rect gSpriteClipsRight[ BUTTON_SPRITE_TOTAL ];
LTexture gButtonSpriteSheetTextureLeft;
LTexture gButtonSpriteSheetTextureRight;
LButton gButtonsLeft[ TOTAL_BUTTONS ];
LButton gButtonsRight[ TOTAL_BUTTONS ];

SDL_Rect handPos;
SDL_Rect stone;
SDL_Rect rightArrow;
SDL_Rect leftArrow;
SDL_Event e;

box boxS[10];
bigBox boxB[2] = {{true}, {false}};
int gTurn = 0;


int main (int argc, char* argv[]) {
    
    gameLoop();
    return 0;
}

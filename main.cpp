//
// Game O an quan
// by Bang Do

#include "game.hpp"
#include "box.hpp"
#include "showGraphic.hpp"


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture** gStoneTable = NULL;

SDL_Texture* gTable = NULL;
SDL_Texture* gBigStone = NULL;
SDL_Texture* gHand = NULL;
SDL_Texture* gRightArrow = NULL;
SDL_Texture* gLeftArrow = NULL;

TTF_Font *gFont = NULL;
SDL_Color textColor = { 0, 0, 0 };

LTexture gTextTexture;
LTexture* gNumStoneText;
LTexture gScoreFirstText;
LTexture gScoreSecondText;

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

box boxS[12];

int gTurn = 0;


int main (int argc, char* argv[]) {
    
    gameLoop();
    return 0;
}

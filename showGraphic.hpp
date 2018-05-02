//
//  showGraphic.hpp
//

#ifndef showGraphic_hpp
#define showGraphic_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "SDL_ttf.h"
#include "box.hpp"
#include <algorithm>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Khai bao bien //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define POSX1 100
#define POSY1 100
#define BOXHEIGHT 100
#define BOXWIDTH 100

const int BUTTON_WIDTH = BOXWIDTH/2;
const int BUTTON_HEIGHT = BOXWIDTH;
const int TOTAL_BUTTONS = 10;


extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;


extern SDL_Texture* gTable;
extern SDL_Texture* gBigStone;
extern SDL_Texture* gHand;
extern SDL_Texture* gRightArrow;
extern SDL_Texture* gLeftArrow;

extern TTF_Font* gFont;

extern SDL_Texture** gStoneTable;
extern SDL_Rect rightArrow;
extern SDL_Rect leftArrow;
extern SDL_Rect handPos;
extern SDL_Rect stone;
extern SDL_Event e;
extern void performancedTurn(int order, bool left);
extern SDL_Color textColor;
extern int gTurn;

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Function /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void initGraphic();
void loadMedia();
void close();
void showGraphic();
void moveHandTo(int orderBoxDestination);
SDL_Texture* loadTexture( std::string path );
void updateNumStone();

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Class Texture //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


//Texture wrapper class
class LTexture
{
public:
    LTexture();
    ~LTexture();
    bool loadFromFile( std::string path );
    
#ifdef _SDL_TTF_H
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif
    void free();
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    //Image dimensions
    int mWidth;
    int mHeight;
};

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Class Button ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
class LButton
{
public:
    LButton();
    int orderButton;
    bool left;
    void setPosition( int x, int y );
    void handleEvent( SDL_Event* e, const int& a, const int& b, int& mouseEvent);
    void render();
private:
    SDL_Point mPosition;
    LButtonSprite mCurrentSprite;
};

extern SDL_Rect gSpriteClipsLeft[ BUTTON_SPRITE_TOTAL ];
extern SDL_Rect gSpriteClipsRight[ BUTTON_SPRITE_TOTAL ];

extern LTexture gTextTexture;
extern LTexture* gNumStoneText;
extern LTexture gScoreFirstText;
extern LTexture gScoreSecondText;

extern LTexture gButtonSpriteSheetTextureLeft;
extern LTexture gButtonSpriteSheetTextureRight;
extern LButton gButtonsLeft[ TOTAL_BUTTONS ];
extern LButton gButtonsRight[ TOTAL_BUTTONS ];

#endif /* showGraphic_hpp */




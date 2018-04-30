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


extern SDL_Texture* gStone;
extern SDL_Texture* gStone1;
extern SDL_Texture* gStone2;
extern SDL_Texture* gStone3;
extern SDL_Texture* gStone4;
extern SDL_Texture* gStone5;
extern SDL_Texture* gStone6;
extern SDL_Texture* gStone7;
extern SDL_Texture* gStone8;
extern SDL_Texture* gStone9;
extern SDL_Texture* gStone10;
extern SDL_Texture* gStone11;
extern SDL_Texture* gStone12;
extern SDL_Texture* gStone13;
extern SDL_Texture* gStone14;
extern SDL_Texture* gStone15;
extern SDL_Texture* gStone16;
extern SDL_Texture* gStone17;
extern SDL_Texture* gStone18;
extern SDL_Texture* gStone19;
extern SDL_Texture* gStone20;
extern SDL_Texture* gStone21;

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
extern int gTurn;

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Function /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void initGraphic();
void loadMedia();
void close();
void showGraphic();
SDL_Texture* loadTexture( std::string path );

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
extern LTexture gTextTexture1;
extern LTexture gTextTexture2;
extern LTexture gTextTexture3;
extern LTexture gTextTexture4;
extern LTexture gTextTexture5;
extern LTexture gTextTexture6;
extern LTexture gTextTexture7;
extern LTexture gTextTexture8;
extern LTexture gTextTexture9;
extern LTexture gTextTexture10;
extern LTexture gButtonSpriteSheetTextureLeft;
extern LTexture gButtonSpriteSheetTextureRight;
extern LButton gButtonsLeft[ TOTAL_BUTTONS ];
extern LButton gButtonsRight[ TOTAL_BUTTONS ];

#endif /* showGraphic_hpp */




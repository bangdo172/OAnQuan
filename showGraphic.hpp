
//
//  showGraphic.hpp

#ifndef showGraphic_hpp
#define showGraphic_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "SDL_ttf.h"

bool init();
bool loadMedia();
void close();
void initGraphic();
void showGraphic();

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

SDL_Event e;
#endif /* showGraphic_hpp */

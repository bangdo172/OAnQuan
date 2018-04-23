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

SDL_Texture* loadTexture( std::string path );

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define POSX1 100
#define POSY1 100
#define BOXWIDTH 160
#define BOXHEIGHT 160



extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern SDL_Texture* gStone;
extern SDL_Texture* gTable;
extern SDL_Texture* gBigStone;
extern SDL_Texture* gHand;
extern SDL_Texture* gRightArrow;
extern SDL_Texture* gLeftArrow;

extern SDL_Rect handPos;
extern SDL_Rect stone;
extern SDL_Rect rightArrow;
extern SDL_Rect leftArrow;
extern SDL_Event e;

bool init();
bool loadMedia();
void close();
void showGraphic();

#endif /* showGraphic_hpp */

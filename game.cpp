//
//  game.cpp
//  oanquan
//
//  Created by Bang Do on 4/16/18.
//  Copyright © 2018 Bang Do. All rights reserved.
//

#include "game.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "SDL_ttf.h"
#include "showGraphic.hpp"
#include "box.hpp"
using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define POSX1 100
#define POSY1 100
#define BOXWIDTH 100
#define BOXHEIGHT 100

box boxS[10];
bigBox boxB[2] = {{true}, {false}};

bool endGame;

box chooseBox() {
    return boxS[1];
}
bool chooseDirection () {
    return 0;
}
void moveStone() {
    
}
void gameLoop() {
    endGame = false;
    while (!endGame) {
        chooseBox();
        chooseDirection();
        moveStone();
        // dai quan
        
        // endGame
        
    }
}

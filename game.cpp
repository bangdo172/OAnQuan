//  game.cpp

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
bool turnFirstPerson;

box chooseBox() {
    return boxS[1];
}
bool chooseDirection () {
    return 0;
}
void moveStone() {
    
}
void distributeStone() {
    
}
void gameOver() {
    
}
void gameLoop() {
    endGame = false;
    turnFirstPerson = true;
    int turn = 0;
    while (!endGame) {
        
        turn ++;
        if (turn % 2 == 0) {
            turnFirstPerson = false;
        }
        else {
            turnFirstPerson = true;
        }
        
        chooseBox();
        chooseDirection();
        moveStone();
        // dai quan
        distributeStone();
        // endGame
        gameOver();
    }
}

//
//  box.hpp
//

#ifndef box_hpp
#define box_hpp

#include <stdio.h>
#include "showGraphic.hpp"

// struct of box
struct box {
public:
    SDL_Rect boxSRect;
    int numStone;
    int order;
};

// box on the table
extern box boxS[12];
// box of player 1
extern box boxP1;
// box of player 2
extern box boxP2;
// init Box
void initBox();

#endif /* box_hpp */

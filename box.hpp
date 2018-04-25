//
//  box.hpp
//

#ifndef box_hpp
#define box_hpp

#include <stdio.h>
#include "showGraphic.hpp"
// class of small box

struct box {
public:
    SDL_Rect boxSRect;
    int numStone;
};

struct bigBox
{
public:
    SDL_Rect boxBRect;
    int numStone;
    bool bigStone = true;
    bool posLeft;
};

extern box boxS[10];
extern bigBox boxB[2];

void initBox();
#endif /* box_hpp */

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
    int order;
};

extern box boxS[12];

void initBox();
#endif /* box_hpp */

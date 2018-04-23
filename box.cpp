//
//  box.cpp
//

#include "box.hpp"

void initBox () {
    for (int i = 0; i < 10; i ++) {
        boxS[i].numStone = 5;
    }
    for (int i = 0; i < 5; i ++) {
        boxS[i].boxSRect.x = 200 + i * BOXWIDTH;
        boxS[i].boxSRect.y = 190;
    }
    for (int i = 5; i < 10; i ++) {
        boxS[i].boxSRect.x = 200 + i * BOXWIDTH;
        boxS[i].boxSRect.y = 190 + 160;
    }
    boxB[0].boxBRect.x = 100;
    boxB[0].boxBRect.y = 200;
    boxB[1].boxBRect.x = 1050;
    boxB[1].boxBRect.y = 200;
}

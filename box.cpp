//
//  box.cpp
//

#include "box.hpp"

void initBox () {
    for (int i = 0; i < 12; i ++) {
        boxS[i].order = i;
    }
    for (int i = 0; i < 5; i ++) {
        boxS[i].numStone = 5;
    }
    for (int i = 5; i < 11; i ++) {
        boxS[i].numStone = 5;
    }
    boxS[5].numStone = 0;
    boxS[11].numStone = 0;
     ////// row 1
    boxS[0].boxSRect.x = 265;
    boxS[0].boxSRect.y = 205;
    boxS[1].boxSRect.x = 425;
    boxS[1].boxSRect.y = 205;
    boxS[2].boxSRect.x = 575;
    boxS[2].boxSRect.y = 205;
    boxS[3].boxSRect.x = 730;
    boxS[3].boxSRect.y = 205;
    boxS[4].boxSRect.x = 885;
    boxS[4].boxSRect.y = 205;
    ////// row 2
    boxS[10].boxSRect.x = 265;
    boxS[10].boxSRect.y = 355;
    boxS[9].boxSRect.x = 425;
    boxS[9].boxSRect.y = 355;
    boxS[8].boxSRect.x = 575;
    boxS[8].boxSRect.y = 355;
    boxS[7].boxSRect.x = 730;
    boxS[7].boxSRect.y = 355;
    boxS[6].boxSRect.x = 885;
    boxS[6].boxSRect.y = 355;
    
    // big Boxes
    boxS[5].boxSRect.x = 1035;
    boxS[5].boxSRect.y = 270;
    boxS[11].boxSRect.x = 120;
    boxS[11].boxSRect.y = 270;
    
    // box P1
    boxP1.boxSRect.x = 730;
    boxP1.boxSRect.y = 100;
    boxP1.numStone = 0;
    boxP1.order = 12;

    // box P2
    boxP2.boxSRect.x = 730;
    boxP2.boxSRect.y = 600;
    boxP2.numStone = 0;
    boxP2.order = 12;
}

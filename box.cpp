//
//  box.cpp
//

#include "box.hpp"

void initBox () {
    for (int i = 0; i < 10; i ++) {
        boxS[i].numStone = 5;
    }
//    for (int i = 0; i < 5; i ++) {
//        boxS[i].boxSRect.x = 200 + i * BOXWIDTH;
//        boxS[i].boxSRect.y = 190;
//    }
//    for (int i = 5; i < 10; i ++) {
//        boxS[i].boxSRect.x = 200 + (i - 5) * BOXWIDTH;
//        boxS[i].boxSRect.y = 190 + 160;
//    }
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
    boxS[5].boxSRect.x = 265;
    boxS[5].boxSRect.y = 355;
    boxS[6].boxSRect.x = 425;
    boxS[6].boxSRect.y = 355;
    boxS[7].boxSRect.x = 575;
    boxS[7].boxSRect.y = 355;
    boxS[8].boxSRect.x = 730;
    boxS[8].boxSRect.y = 355;
    boxS[9].boxSRect.x = 885;
    boxS[9].boxSRect.y = 355;
    
    
    
    boxB[0].boxBRect.x = 100;
    boxB[0].boxBRect.y = 200;
    boxB[1].boxBRect.x = 1050;
    boxB[1].boxBRect.y = 200;
}

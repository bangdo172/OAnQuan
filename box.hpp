//
//  box.hpp

#ifndef box_hpp
#define box_hpp

#include <stdio.h>

// class of small box 
class box {
public:
    int posX, posY, numStone;
    box(int, int, int);
    box(){};
};


class bigBox
{
public:
    int posX, posY, numStone;
    bool bigStone = true;
    bool posLeft;
    bigBox(bool pos) : numStone(0), bigStone(1), posLeft(pos) {};
};

#endif /* box_hpp */

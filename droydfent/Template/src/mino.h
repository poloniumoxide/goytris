#ifndef MINO_H
#define MINO_H

#include <vector>

using namespace std;

class Mino {
public:
    int x, y;
    int type;
    // 0 = empty
    // 1 = shadow
    //
    //
    //
    // 10-16: filled minos
    bool live;
    bool shadow;

    Mino(int = 0, int = 0, int = 0);

};

#endif // MY_HEADER_H
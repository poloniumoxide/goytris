#ifndef MINOSET_H
#define MINOSET_H

#include "mino.h"

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class MinoSet {
public:
	vector<Mino> minos;
    int cx; //NOTE: ROTATION CENTER VALUES HERE ARE DOUBLE cuz i dont wanna deal with floats
    int cy;
    int type;
    int ox;
    int oy;
    int neutralx;
    int neutraly;
    int rotation;
    vector<vector<int>> baseminos;

    MinoSet(vector<vector<int>> = {{0, 0}}, int = 0, int = 0, int = 0, int = 0, int = 0);

    void move(int = 0, int = 0, int = 0);
    void reset();
    MinoSet copy();

};

#endif // MY_HEADER_H
#ifndef STACKER_H
#define STACKER_H

#include "controller.h"
#include "bag.h"
#include "minoset.h"
#include "jsonparser.h"
#include "force.h"
#include "mino.h"

#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Stacker {
public:

    vector<vector<Mino>> board;

    Controller control;
    Bag bag;
    MinoSet tetro;
    MinoSet held;
    int xi, yi;
    bool active; //active tetromino?
    int turn;
    vector<vector<int>> clears;

    Texture2D minoskin1;

    Stacker();
    
    void run();
    bool fit(MinoSet, int = 0, int = 0, int = 0);
    bool fit(Mino, int = 0, int = 0);
    bool fit(int = 0, int = 0);
    void spawn();
    void getCommands();
    void hold();
    void move(int);
    void spin(int);
    void harddrop();
    void lock();
    void softdrop(int);
    void clear();
    void draw(int, int, int);


};

#endif // MY_HEADER_H
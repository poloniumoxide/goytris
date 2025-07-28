#ifndef STACKER_H
#define STACKER_H

#include "controller.h"
#include "bag.h"
#include "minoset.h"
#include "jsonparser.h"
#include "force.h"
#include "mino.h"

#include <vector>
#include <cstdlib>

using namespace std;

class Stacker {
public:

    vector<vector<Mino>> board;
    Controller control;
    Bag bag;
    MinoSet tetro;
    int xi, yi;
    bool active = false; //active tetromino?
    int turn;

    Stacker();
    
    void run();
    bool fit(MinoSet, int = 0, int = 0, int = 0);
    bool fit(Mino, int = 0, int = 0);
    void spawn();
    void getCommands();
    void move(int);
    void spin(int);
    void harddrop();
    void lock();
    void softdrop(int);
    void draw();

};

#endif // MY_HEADER_H
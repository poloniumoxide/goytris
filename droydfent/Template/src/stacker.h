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
#include <deque>

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
    deque<vector<int>> clears;
    vector<int> dist;
    json loc;
    bool turn;
    bool hashd;

    Texture2D minoskin1;

    Stacker(json);
    Stacker();
    
    virtual bool run();
    bool fit(MinoSet, int = 0, int = 0, int = 0);
    bool fit(Mino, int = 0, int = 0);
    bool fit(int = 0, int = 0);
    void spawn();
    int calcdist(MinoSet, int = 0, bool = true);
    void getCommands();
    void hold();
    void move(int);
    void spin(int);
    void harddrop();
    void lock();
    int softdrop(int);
    void clear();
    virtual void accept(Force);
    virtual void draw(int, int, int);
    static vector<Mino> booltomino(vector<bool>);
    vector<int> action();


};

#endif // MY_HEADER_H
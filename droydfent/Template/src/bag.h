#ifndef BAG_H
#define BAG_H

#include "minoset.h"
#include "jsonparser.h"

#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <deque>
#include <stdexcept>

using namespace std;

class Bag {
public:

    vector<vector<MinoSet>> bag;
    deque<MinoSet> tbag;
    int it = 0;
    int seed;
    mt19937 rngesus;

    Bag(vector<int> = {0, 1, 2, 3, 4, 5, 6}, int = 7, int = 271000);
    Bag(vector<MinoSet>, int = 7, int = 271000);
    Bag(vector<vector<MinoSet>>, int = 271000);

    void seedrng(int);
    void reset();
    MinoSet next();
    void addbag(int = 1);
    MinoSet view(int = 0);
    int csize();
    int size();

};

#endif // MY_HEADER_H
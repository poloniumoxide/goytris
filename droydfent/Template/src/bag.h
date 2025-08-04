#ifndef BAG_H
#define BAG_H

#include "minoset.h"
#include "jsonparser.h"

#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <deque>

using namespace std;

class Bag {
public:

	int size;
    vector<int> bag;
    deque<int> tbag;
    int it = 0;
    int seed;
    mt19937 rngesus;

    Bag(vector<int> = {0, 1, 2, 3, 4, 5, 6}, int = 271000);

    MinoSet next();
    void addbag(int = 1);
    MinoSet view(int = 0);

};

#endif // MY_HEADER_H
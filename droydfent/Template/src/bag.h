#ifndef BAG_H
#define BAG_H

#include "minoset.h"
#include "jsonparser.h"

#include <algorithm>
#include <random>
#include <vector>

using namespace std;

class Bag {
public:

	int size;
    vector<int> bag;
    vector<int> tbag;
    int it = 0;
    default_random_engine rngesus;

    Bag(vector<int> = {0, 1, 2, 3, 4, 5, 6});

    MinoSet next();

};

#endif // MY_HEADER_H
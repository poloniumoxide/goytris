#include "minoset.cpp"
#include "defaultdata.cpp"

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

    Bag(vector<int> bag_ = {0, 1, 2, 3, 4, 5, 6}) {
        bag=bag_;
        it=bag.size()-1;
        random_device rng;
        default_random_engine rngesus(rng());
    }

    MinoSet next() {
        if (it == bag.size()-1) {
            for (auto x : bag) {
                tbag.push_back(x);
            }
            shuffle(tbag.begin(), tbag.end(), rngesus);
            it = 0;
        }
        it++;

        MinoSet an(tetrominos[tbag[it-1]], 0, 0, it-1+10);
        return an;
    }
};
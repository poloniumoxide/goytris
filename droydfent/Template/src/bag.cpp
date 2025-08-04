#include "bag.h"


    Bag::Bag(vector<int> bag_, int seed_) {
        bag=bag_;
        it=bag.size()-1;
        seed = seed_;
        if (seed == 271000) {
            seed = chrono::system_clock::now().time_since_epoch().count();
        }
        mt19937 rngesus_(seed);
        rngesus = rngesus_;
    }

    MinoSet Bag::next() {
        if (it == bag.size()-1) {
            tbag.clear();
            for (auto x : bag) {
                tbag.push_back(x);
            }
            shuffle(tbag.begin(), tbag.end(), rngesus);
            it = 0;
        }
        it++;

        MinoSet an(D["tetrominos"][tbag[it-1]], D["board"]["xi"], D["board"]["yi"], tbag[it-1]+10, D["tetrominoscenter"][tbag[it-1]][0], D["tetrominoscenter"][tbag[it-1]][1]);
        return an;
    }

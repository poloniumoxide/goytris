#include "bag.h"

    int size;
    vector<int> bag;
    vector<int> tbag;
    int it = 0;
    default_random_engine rngesus;

    Bag::Bag(vector<int> bag_) {
        bag=bag_;
        it=bag.size()-1;
        random_device rng;
        default_random_engine rngesus(rng());
    }

    MinoSet Bag::next() {
        if (it == bag.size()-1) {
            for (auto x : bag) {
                tbag.push_back(x);
            }
            shuffle(tbag.begin(), tbag.end(), rngesus);
            it = 0;
        }
        it++;

        MinoSet an(D["tetrominos"][tbag[it-1]], D["board"]["xi"], D["board"]["yi"], tbag[it-1]+10);
        return an;
    }

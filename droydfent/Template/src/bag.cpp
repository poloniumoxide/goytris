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
        if (tbag.empty()) {
            addbag(1);
        }

        MinoSet an(D["tetrominos"][tbag.front()], D["board"]["xi"], D["board"]["yi"], tbag.front()+10, D["tetrominoscenter"][tbag.front()][0], D["tetrominoscenter"][tbag.front()][1]);
        tbag.pop_front();
        return an;
    }

    void Bag::addbag(int rep) {
        for (int j = 0; j < rep; j++) {
            vector<int> n;
            for (int i = 0; i < bag.size(); i++) {
                n.push_back(bag[i]);
            }
            shuffle(n.begin(), n.end(), rngesus);
            for (int i = 0; i < n.size(); i++) {
                tbag.push_back(n[i]);
            }
        }
    }

    MinoSet Bag::view(int depth) { // 0 indexed depth
        while (tbag.size() < depth+1) {
            addbag(1);
        }
        MinoSet an(D["tetrominos"][tbag[depth]], D["board"]["xi"], D["board"]["yi"], tbag[depth]+10, D["tetrominoscenter"][tbag[depth]][0], D["tetrominoscenter"][tbag[depth]][1]);
        return an;
    }

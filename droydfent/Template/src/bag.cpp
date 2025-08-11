#include "bag.h"


    Bag::Bag(vector<int> bag_, int seed_) {
        
        for (int i = 0; i < bag_.size(); i++) {
            bag.push_back(MinoSet(D["tetrominos"][bag_[i]], 0, 0, bag_[i]+10, D["tetrominoscenter"][bag_[i]][0], D["tetrominoscenter"][bag_[i]][1]));
        }
        
        seedrng(seed_);
        reset();
    }

    Bag::Bag(vector<MinoSet> bag_, int seed_) {
        bag=bag_;
        seedrng(seed_);
        reset();
    }

    void Bag::seedrng(int seed_) {
        seed = seed_;
        if (seed == 271000) {
            seed = chrono::system_clock::now().time_since_epoch().count();
        }
        mt19937 rngesus_(seed);
        rngesus = rngesus_;
    }

    MinoSet Bag::next() {
        if (tbag.empty()) {
            throw std::runtime_error("mcsdiy bag twiiinnnnnn");
        }

        auto ans = tbag.front();
        tbag.pop_front();
        return ans;
    }

    void Bag::reset() {
        tbag.clear();
        vector<MinoSet> n;
        for (int i = 0; i < bag.size(); i++) {
            n.push_back(bag[i]);
        }
        shuffle(n.begin(), n.end(), rngesus);
        for (int i = 0; i < n.size(); i++) {
            tbag.push_back(n[i]);
        }
    }

    void Bag::addbag(int rep) {
        for (int j = 0; j < rep; j++) {
            vector<MinoSet> n;
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
        if (depth >= tbag.size()) {
            throw std::runtime_error("invalid bag depth");
        }
        return tbag[depth];
    }

    int Bag::csize() {
        return tbag.size();
    }

    int Bag::size() {
        return bag.size();
    }

    /*

    MinoSet Bag::viewinf(int depth) { // 0 indexed depth
        while (tbag.size() < depth+1) {
            addbag(1);
        }
        MinoSet an(D["tetrominos"][tbag[depth]], D["board"]["xi"], D["board"]["yi"], tbag[depth]+10, D["tetrominoscenter"][tbag[depth]][0], D["tetrominoscenter"][tbag[depth]][1]);
        return an;
    }*/

#include "bag.h"


    Bag::Bag(vector<int> bag_, int rep, int seed_) {

        
        for (int i = 0; i < rep; i++) {
            vector<MinoSet> n;
            for (int j = 0; j < bag_.size(); j++) {
                n.push_back(MinoSet(D["tetrominos"][bag_[j]], 0, 0, bag_[j]+10, D["tetrominoscenter"][bag_[j]][0], D["tetrominoscenter"][bag_[j]][1]));
            }
            bag.push_back(n);
        }


        
        seedrng(seed_);
        reset();
    }

    Bag::Bag(vector<MinoSet> bag_, int rep, int seed_) {
        
        for (int j = 0; j < rep; j++) {
            vector<MinoSet> cpy;
            for (int i = 0; i < bag_.size(); i++) {
                cpy.push_back(bag_[i].copy());
            }
            bag.push_back(cpy);
        }

        seedrng(seed_);
        reset();

    }

    Bag::Bag(vector<vector<MinoSet>> bag_, int seed_) {
        
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
            addbag(1);
        }

        auto ans = tbag.front();
        tbag.pop_front();
        return ans;
    }

    void Bag::reset() {
        tbag.clear();
        addbag(1);
    }

    void Bag::addbag(int rep) {
        cout << "here"<< endl;
        for (int j = 0; j < rep; j++) {

            vector<MinoSet> n;
            for (int i = 0; i < bag[it].size(); i++) {
                n.push_back(bag[it][i].copy());
            }

            shuffle(n.begin(), n.end(), rngesus);

            for (int i = 0; i < n.size(); i++) {
                tbag.push_back(n[i]);
            }

            it++; it %= bag.size();
        }
        cout << "here!"<< endl;
    }

    MinoSet Bag::view(int depth) { // 0 indexed depth
        while (tbag.size() < depth+1) {
            addbag(1);
        }
        return tbag[depth];
    }

    int Bag::size() {
        return bag.size();
    }


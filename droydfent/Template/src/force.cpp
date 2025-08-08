#include "force.h"

    //FIFO

    Force::Force(double str, double entr, vector<bool> hole) {
        //add this into f
        fnet.push_back({str, entr, hole});
    }

    void Force::merge(Force f) {
        //this is the first one, f is second
        for (int i = 0; i < f.fnet.size(); i++) {
            fnet.push_back(f.fnet[i]);
        }

        f.clear(); 
    }

    void Force::cancel(Force f) {
        // do a - b; this one is a
        // note: if the result is negative, this will be zero
        // the front end will cancel first
        while ((fnet.size() != 0) & (f.fnet.size() != 0)) {
            Component a = fnet.front();
            Component b = f.fnet.front();
            fnet.pop_front();
            f.fnet.pop_front();
            compcancel(a, b);
            if (a.strength != 0) { //check float?
                fnet.push_front(a);
            } //do not use an else here
            if (b.strength != 0) {
                f.fnet.push_front(b);
            }
        }

    }

    void Force::clear() {
        deque<Component> cleared;
        fnet = cleared;
    }

    vector<bool> Force::genholes(int hole, int len) {
        vector<bool> ans(len);
        ans[hole] = true;
        return ans;
    }

    void Force::compcancel(Component& a, Component& b) {
        a.strength -= min(a.strength, b.strength);
        b.strength -= min(a.strength, b.strength);
    }

    //diminish, boost


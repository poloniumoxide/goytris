#include "controller.h"
#include "defaultdata.h"


using namespace std;

    Controller::Controller() {
        held = {0, 0, 0, 0, 0, 0, 0, 0}; //8, l, r, cw, ccw, 180, hold, sd, hd 
        order = {kleft, kright, kcw, kccw, k180, khold, ksd, khd};
        inputs = {};
    }

    void Controller::run() {
        
        for (int i = 0; i < order.size(); i ++) {
            checkheld(order[i], i);
        }
        if (held[kleft] >= das) {
            int p = held[kleft]-das;
            if (p%arr == 0) {
                inputs.push_back(2);
            }
        }
        if (held[kright] >= das) {
            int p = held[kright]-das;
            if (p%arr == 0) {
                inputs.push_back(3);
            }
        }
        if (held[kcw] == 1) {
            inputs.push_back(6);
        }
        if (held[kccw] == 1) {
            inputs.push_back(8);
        }
        if (held[k180] == 1) {
            inputs.push_back(7);
        }
        if (held[khold] == 1) {
            inputs.push_back(9);
        }
        if (held[ksd] > 0) {
            if (sdf == 0) {
                for (int i = 0; i < 40; i++) {
                    inputs.push_back(1);
                }
            } else if (held[ksd]%sdf == 0) {
                inputs.push_back(1);
            }
        }
        if (held[khd] == 1) {
            inputs.push_back(0);
        }

    }

    void Controller::checkheld(int key, int pos) {
        if (IsKeyDown(key)) {
            held[pos]++;
        } else {
            held[pos] = 0;
        }
    }

    int Controller::next() {
        if (!inputs.empty()) {
            int t = inputs.front();
            inputs.pop_front();
            return t;
        } else {
            return 271000;
        }
    }

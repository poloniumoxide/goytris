#include "controller.h"


    Controller::Controller() {
        held = {0, 0, 0, 0, 0, 0, 0, 0}; //8, l, r, cw, ccw, 180, hold, sd, hd 
        inputs = {};
        ste = {
            {"KEY_LEFT" , KEY_LEFT},
            {"KEY_RIGHT" , KEY_RIGHT},
            {"KEY_UP" , KEY_UP},
            {"KEY_DOWN" , KEY_DOWN},
            {"KEY_W" , KEY_W},
            {"KEY_E" , KEY_E},
            {"KEY_Q" , KEY_Q},
            {"KEY_SPACE" , KEY_SPACE}
        };

        kleft = ste[D["keybinds"]["kleft"]];
        kright = ste[D["keybinds"]["kright"]];
        kcw = ste[D["keybinds"]["kcw"]];
        kccw = ste[D["keybinds"]["kccw"]];
        k180 = ste[D["keybinds"]["k180"]];
        khold = ste[D["keybinds"]["khold"]];
        ksd = ste[D["keybinds"]["ksd"]];
        khd = ste[D["keybinds"]["khd"]];

        order = {kleft, kright, kcw, kccw, k180, khold, ksd, khd};

    }

    void Controller::run() {
        
        for (int i = 0; i < order.size(); i ++) {
            checkheld(order[i], i);
        }
        if (held[kleft] >= D["handling"]["das"]) {
            int p = held[kleft]-(int)D["handling"]["das"];
            if (p%(int)D["handling"]["arr"] == 0) {
                inputs.push_back(2);
            }
        }
        if (held[kright] >= D["handling"]["das"]) {
            int p = held[kright]-(int)D["handling"]["das"];
            if (p%(int)D["handling"]["arr"] == 0) {
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
            if ((int)D["handling"]["sdf"] == 0) {
                for (int i = 0; i < 40; i++) {
                    inputs.push_back(1);
                }
            } else if (held[ksd]%(int)D["handling"]["sdf"] == 0) {
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

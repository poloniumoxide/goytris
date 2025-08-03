#include "minoset.h"


    MinoSet::MinoSet(vector<vector<int>> minos_, int cx_, int cy_, int type_) {
        cx = cx_;
        cy = cy_;
        type=type_;
        for (auto x : minos_) {
            minos.push_back(Mino(x[0]+cx, x[1]+cy, type));
        }
    }


    void MinoSet::move(int dx, int dy, int dtheta) {
        for (int i = 0; i < minos.size(); i++) {
            minos[i].move(dx, dy);
        }
        cx += dx; cy += dy;
        for (int i = 0; i < (dtheta % 4); i++) {
            //rotate 90 degrees about cx,cy
            for (auto m : minos) {
                int px = m.x - cy; int py = m.y - cy;
                int npx = py; int npy = -px;
                m.x = cx + npx; m.y = cy + npy;
            }
        }
    }

#include "minoset.h"


    MinoSet::MinoSet(vector<vector<int>> minos_, int cx_, int cy_, int type_, int ox_, int oy_) {
        cx = cx_;  //note: doubled
        cy = cy_;
        ox = ox_;  //offset from cx where the physical rotation center is
        oy = oy_;
        neutralx = cx;
        neutraly = cy;
        rotation = 0;
        type = type_;
        baseminos = minos_;
        for (auto x : minos_) {
            minos.push_back(Mino(x[0]+cx, -x[1]+cy, type));
        }
    }


    MinoSet MinoSet::copy() {
        vector<vector<int>> cpy = baseminos;
        return MinoSet(cpy, cx, cy, type, ox, oy);
    }

    void MinoSet::move(int dx, int dy, int dtheta) {
        for (int i = 0; i < minos.size(); i++) {
            minos[i].move(dx, dy);
        }
        cx += dx; cy += dy;
        rotation += dtheta; rotation %= 4;
        for (int i = 0; i < (dtheta % 4); i++) {
            //rotate 90 degrees about cx,cy
            for (int i = 0; i < minos.size(); i++) {
                int tx = 2 * cx + ox;    int ty = 2 * cy + oy;
                int mx = 2 * minos[i].x; int my = 2 * minos[i].y;
                int px = mx - tx; int py = my - ty;
                int npx = py; int npy = -px;
                minos[i].x = (tx + npx) / 2;
                minos[i].y = (ty + npy) / 2;
            }
        }
    }

    void MinoSet::reset() {
        move(neutralx-cx, neutraly-cy, 4-rotation);
    }



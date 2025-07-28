#include "minoset.h"

using namespace std;


    vector<Mino> minos;
    int cx; //NOTE: ROTATION CENTER VALUES HERE ARE DOUBLE cuz i dont wanna deal with floats
    int cy;
    int type;

    MinoSet::MinoSet(vector<vector<int>> minos_, int cx_, int cy_, int type_) {
        cx = cx_;
        cy = cy_;
        for (auto x : minos_) {
            minos.push_back(Mino(x[0], x[1], type));
        }
        type=type_;
    }


    void MinoSet::move(int dx, int dy, int dtheta) {
        for (auto m : minos) {
            m.x += dx; m.y += dy;
        }
        cx += dx; cy += dy;
        for (int i = 0; i < dtheta % 4; i++) {
            //rotate 90 degrees about cx,cy
            for (auto m : minos) {
                int px = m.x - cy; int py = m.y - cy;
                int npx = py; int npy = -px;
                m.x = cx + npx; m.y = cy + npy;
            }
        }
    }

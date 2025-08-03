#include "mino.h"

    Mino::Mino(int x_, int y_, int type_) {
        x = x_;
        y = y_;
        type = type_;
    }

    void Mino::move(int dx, int dy) {
        x = x + dx;
        y = y + dy;
    }

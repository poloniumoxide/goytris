class Mino {
public:

    int x, y;
    int type;
    // 0 = empty
    // 1 = shadow
    //
    //
    //
    // 10-16: filled minos
    bool live;
    bool shadow;

    Mino(int x_, int y_, int type_ = 0) {
        x = x_;
        y = y_;
        type = type_;
    }

};
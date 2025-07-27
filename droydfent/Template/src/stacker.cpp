#include "mino.cpp"
#include "controller.cpp"
#include "force.cpp"
#include "bag.cpp"
#include "minoset.cpp"

#include <vector>
#include <cstdlib>

using namespace std;

class Stacker {
public:

    int width;
    int height;
    Mino board[height][width];
    Controller control;
    Force atkbar;
    Force defbar;
    Bag bag;
    MinoSet tetro;
    int xi, yi;
    bool active = false; //active tetromino?
    int turn;


    Stacker() {

    }
    
    void run() {
        if (turn <= 0) return; //turn based
        spawn();
        getCommands();
        //run gravity
        //print onto board
        draw();
    }

    bool fit(MinoSet t, int dx = 0, int dy = 0, int dtheta = 0) {
        bool isgoy = false;
        t.move(dx, dy, dtheta);
        for (auto x : t.minos) {
            if (!fit(x)) isgoy = true;
        }
        t.move(-dx, -dy, (4-dtheta)%4);
        return !isgoy
    }

    bool fit(Mino t, int dx = 0, int dy = 0) {
        if ((t.x+dx < 0) | (t.x+dx >= width) | (t.y+dy < 0) | (t.y+dy >= height)) {
            return false;
        }
        return (board[t.y + dy][t.x + dx].type <= 1);
    }

    void spawn() {
        if (active) return;
        active = true;
        tetro = bag.next(xi, yi);
    }

    void getCommands() {
        int t = control.next();
        while (t != 271000) { //271k indicates that it's empty
            // FUCK case users bro you think ur so good huh with your fancy faggot functions shut the hell up real ubermenchen use ifs
            if (t == 0) {  
                harddrop();
            } else if (t == 1) {
                softdrop(control.sdf);
            } else if (t == 2) {
                move(-1);  //forgor if this is left or right
            } else if (t == 3) {
                move(1);
            } else if (t == 4) {
                move(-271000);  //das, arr = 0
            } else if (t == 5) {
                move(271000);
            } else if (t == 6) {
                spin(1);    //forgor which dir
            } else if(t==7) {
                spin(2);    //180
            } else if (t==8) {
                spin(3);    
            }

            t = control.next();
        }
    }

    void move(int v) {
        int final = 0;
        for (int i = 0; i < abs(v); i += v\abs(v)) {
            if (!fit(tetro, i)) {
                break;
            }
            final = i;
        }
        tetro.move(final);
    }

    void spin(int v) {
        if (!fit(tetro, 0, 0, v)) {
            return;
        }
        tetro.move(0, 0, v);
    }

    void harddrop() {
        int final = 0;
        int v = 271000;
        for (int i = 0; i < abs(v); i += v\abs(v)) {
            if (!fit(tetro, 0, i)) {
                break;
            }
            final = i;
        }
        tetro.move(0, final);
        lock();
    }

    void lock() {

        for (auto m : tetro.minos) {
            board[m.y][m.x] = m;
        }
        active = false;
    }

    void softdrop(int v) {
        int final = 0;
        for (int i = 0; i < abs(v); i += v\abs(v)) {
            if (!fit(tetro, 0, i)) {
                break;
            }
            final = i;
        }
        tetro.move(0, final);
    }

    void draw() {
        //how?
    }

};
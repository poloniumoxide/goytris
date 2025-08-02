#include "stacker.h"

    Stacker::Stacker(){
        vector<Mino> row(D["board"]["width"]);
        vector<vector<Mino>> board_(D["board"]["height"], row);
        for (int i = 0; i < D["board"]["height"]; i++) {
            for (int j = 0; j < D["board"]["width"]; j++) {
                Mino m(j, i, 0);
                board_[i][j] = m;
            }
        }
        board = board_;
        Texture2D minoskin1 = LoadTexture("assets/GlassMaster.png");

    }
    
    
    void Stacker::run() {
        if (turn <= 0) return; //turn based
        spawn();
        getCommands();
        //run gravity
        //print onto board
    }

    bool Stacker::fit(MinoSet t, int dx, int dy, int dtheta) {
        bool isgoy = false;
        t.move(dx, dy, dtheta);
        for (auto x : t.minos) {
            if (!fit(x)) isgoy = true;
        }
        t.move(-dx, -dy, (4-dtheta)%4);
        return !isgoy;
    }

    bool Stacker::fit(Mino t, int dx, int dy) {
        if ((t.x+dx < 0) | (t.x+dx >= D["board"]["width"]) | (t.y+dy < 0) | (t.y+dy >= D["board"]["height"])) {
            return false;
        }
        return (board[t.y + dy][t.x + dx].type <= 1);
    }

    void Stacker::spawn() {
        if (active) return;
        active = true;
        tetro = bag.next(xi, yi);
    }

    void Stacker::getCommands() {
        int t = control.next();
        while (t != 271000) { //271k indicates that it's empty
            // FUCK case users bro you think ur so good huh with your fancy faggot functions shut the hell up real ubermenchen use ifs
            if (t == 0) {  
                harddrop();
            } else if (t == 1) {
                softdrop(1);
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

    void Stacker::move(int v) {
        int final = 0;
        for (int i = 0; i < abs(v); i += v/abs(v)) {
            if (!fit(tetro, i)) {
                break;
            }
            final = i;
        }
        tetro.move(final);
    }

    void Stacker::spin(int v) {
        if (!fit(tetro, 0, 0, v)) {
            return;
        }
        tetro.move(0, 0, v);
    }

    void Stacker::harddrop() {
        int final = 0;
        int v = 271000;
        for (int i = 0; i < abs(v); i += v/abs(v)) {
            if (!fit(tetro, 0, i)) {
                break;
            }
            final = i;
        }
        tetro.move(0, final);
        lock();
    }

    void Stacker::lock() {

        for (auto m : tetro.minos) {
            board[m.y][m.x] = m;
        }
        active = false;
    }

    void Stacker::softdrop(int v) {
        int final = 0;
        v=-v;
        for (int i = 0; i < abs(v); i += v/abs(v)) {
            if (!fit(tetro, 0, i)) {
                break;
            }
            final = i;
        }
        tetro.move(0, final);
    }

    void Stacker::draw(int x, int y, int sz) {
        //temporary; should use assets later
        DrawRectangleLines(x, y, (int)D["board"]["width"]*sz, (int)D["board"]["height"]*sz, WHITE);
        for (int i = 0; i < D["board"]["height"]; i++) {
            for (int j = 0; j < D["board"]["width"]; j++) {
                int col = board[i][j].type;
                Rectangle source = {0, (float)(0+i*minoskin1.width/12), (float)(minoskin1.width/12), (float)(minoskin1.height)};
                Rectangle dest = {(float)(x+sz*j), (float)(y+sz*i), (float)sz, (float)sz};
                Vector2 empty = {0, 0};
                DrawTexturePro(minoskin1, source, dest, empty, 0, WHITE);
            }
        }

    }
    

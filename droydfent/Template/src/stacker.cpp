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

        held = MinoSet({{271000, 271000}});

        Texture2D minoskin1_ = LoadTexture("/Users/ericyang/Desktop/goytris/droydfent/Template/assets/GlassMaster.png");
        minoskin1 = minoskin1_;
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

    bool Stacker::fit(int x, int y) {
        
        if ((x < 0) | (x >= D["board"]["width"]) | (y < 0) | (y >= D["board"]["height"])) {
            return false;
        }
        return (board[y][x].type <= 1);
    
    }

    void Stacker::spawn() {
        if (active) return;
        active = true;
        tetro = bag.next();
    }

    void Stacker::getCommands() {
        control.run();
        int t = control.next();
        while (t != 271000) { //271k indicates that it's empty
            // FUCK case users bro you think ur so good huh with your fancy faggot functions shut the hell up real ubermenchen use ifs
            if (t == 0) {  
                harddrop();
            } else if (t == 1) {
                softdrop(-1);
            } else if (t == 2) {
                move(-1);  //forgor if this is left or right
            } else if (t == 3) {
                move(1);
            } else if (t == 4) {
                move(-1);  //das, arr = 0
            } else if (t == 5) {
                move(1);
            } else if (t == 6) {
                spin(1);    //forgor which dir
            } else if (t == 7) {
                spin(2);    //180
            } else if (t == 8) {
                spin(3);    
            } else if (t == 9) {
                hold();
            }

            break;

            t = control.next();
        }
    }
    
    void Stacker::hold() {
        tetro.reset();
        if (held.minos[0].x == 271000) {
            held = tetro;
            active = false;
        } else {
            swap(held, tetro);
            tetro.reset();
        }
    }

    void Stacker::move(int v) {
        int final = 0;
        for (int i = 0; abs(i) <= abs(v); i += v/abs(v)) {
            if (!fit(tetro, i, 0)) {
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
        int v = -271000;
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

        for (int i = 0; i < tetro.minos.size(); i++) {
            board[tetro.minos[i].y][tetro.minos[i].x] = tetro.minos[i];
        }

        active = false;

        clear();
    }

    void Stacker::softdrop(int v) {
        int final = 0;
        for (int i = 0; i <= abs(v); i += v/abs(v)) {
            if (!fit(tetro, 0, i)) {
                break;
            }
            final = i;
        }
        tetro.move(0, final);
    }

    void Stacker::clear() { //call this whenever the board is modified
        int final = 0;
        bool pc = true;

        vector<int> clr(0);

        for (int i = 0; i < D["board"]["height"]; i++) {
            bool rowfull = true;
            for (int j = 0; j < D["board"]["width"]; j++) {
                if (fit(j, i)) {
                    rowfull = false;
                    pc = false;
                    break;
                }
            }
            if (rowfull) {
                clr.push_back(i);
                for (int j = 0; j < D["board"]["width"]; j++) {  //remove the blocks
                    Mino m(j, i, 0);
                    board[i][j] = m;
                }
            }
        }

        //shift it down

        int itr = 0;

        for (int i = 0; i < clr.size(); i++) {
            while (itr < clr[i]) {
                swap(board[itr], board[itr-i]); //any swap lovers in chat
                cout << "SWAPPEDNIGE" << endl;
                itr++;
            }
            itr++;
        }

        while (itr < D["board"]["height"]) {
            swap(board[itr], board[itr-clr.size()]);
            itr++;
        }

    }

    void Stacker::draw(int x, int y, int sz) {
        //temporary; should use assets later
        DrawRectangleLines(x, y, (int)D["board"]["width"]*sz, (int)D["board"]["height"]*sz, WHITE);
        for (int i = 0; i < D["board"]["height"]; i++) {
            for (int j = 0; j < D["board"]["width"]; j++) {

                int ti = (int)D["board"]["height"] - i - 1;

                int col = board[i][j].type - 10;
                if (col < 0) continue;
                Rectangle source = {(float)col*(float)minoskin1.width/12.0f, 0, (float)(minoskin1.width/12), (float)(minoskin1.height)};
                Rectangle dest = {(float)(x+sz*j), (float)(y+sz*ti), (float)sz, (float)sz};
                Vector2 empty = {0, 0};
                DrawTexturePro(minoskin1, source, dest, empty, 0, WHITE);
            }
        }

        //draw active mino

        if (active) {

            for (Mino m : tetro.minos) {
                //cout << m.x << "OLD" << m.y << endl;
                int ti = (int)D["board"]["height"] - m.y - 1;
                int col = m.type - 10;
                Rectangle source = {(float)col*(float)minoskin1.width/12.0f, 0, (float)(minoskin1.width/12), (float)(minoskin1.height)};
                Rectangle dest = {(float)(x+sz*m.x), (float)(y+sz*ti), (float)sz, (float)sz};
                Vector2 empty = {0, 0};
                DrawTexturePro(minoskin1, source, dest, empty, 0, WHITE);
            }

            //rotation centers

            float mx = tetro.cx * 2 + tetro.ox;
            float tmy =(tetro.cy * 2 + tetro.oy);

            mx /= 2; tmy /= 2;

            float my = (float)D["board"]["height"] - tmy - 1;

            mx += 0.5; my += 0.5;

            DrawRectangle(x + (mx*sz) - sz/8, y + (my*sz) - sz/8, sz/4, sz/4, BLUE);

        }

        
        //draw hold

        if (held.minos[0].x != 271000) {
            for (Mino m : held.minos) {
                int col = m.type - 10;
                Rectangle source = {(float)col*(float)minoskin1.width/12.0f, 0, (float)(minoskin1.width/12), (float)(minoskin1.height)};
                Rectangle dest = {(float)(x-(sz*(8-m.x))), (float)(y + sz*(36-m.y)), (float)sz, (float)sz};
                Vector2 empty = {0, 0};
                DrawTexturePro(minoskin1, source, dest, empty, 0, WHITE);
            }
        }

        //draw preview

        for (int i = 0; i < (int)D["board"]["preview"]; i++) {
            auto temp = bag.view(i);
            for (Mino m : temp.minos) {
                int col = m.type - 10;
                Rectangle source = {(float)col*(float)minoskin1.width/12.0f, 0, (float)(minoskin1.width/12), (float)(minoskin1.height)};
                Rectangle dest = {(float)(x+(sz*((int)D["board"]["width"]+m.x-2))), (float)(y + sz*(36-m.y+(4*i))), (float)sz, (float)sz};
                Vector2 empty = {0, 0};
                DrawTexturePro(minoskin1, source, dest, empty, 0, WHITE);
            }
        }


    }
    

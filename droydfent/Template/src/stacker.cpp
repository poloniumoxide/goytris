#include "stacker.h"

    Stacker::Stacker(json loc_){


        loc = loc_;

        vector<Mino> row(loc["board"]["width"]);
        vector<vector<Mino>> board_(loc["board"]["height"], row);
        for (int i = 0; i < loc["board"]["height"]; i++) {
            for (int j = 0; j < loc["board"]["width"]; j++) {
                Mino m(j, i, 0);
                board_[i][j] = m;
            }
        }
        board = board_;


        active = false;
        turn = true;


        held = MinoSet({{271000, 271000}});

        Texture2D minoskin1_ = LoadTexture((string(GetApplicationDirectory()).substr(0, string(GetApplicationDirectory()).size() - 4) + "assets/GlassMaster.png").c_str());
        minoskin1 = minoskin1_;

        vector<int> dist_(4); dist = dist_; // dist from edge

        bag = Bag({0, 1, 2, 3, 4, 5, 6}, 7, 271000);

    }

    Stacker::Stacker() {

    }


    
    
    void Stacker::run() {
        if (turn == false) return; //turn based
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

    
        if ((t.x+dx < 0) | (t.x+dx >= loc["board"]["width"]) | (t.y+dy < 0) | (t.y+dy >= loc["board"]["height"])) {
            return false;
        }

        return (board[t.y + dy][t.x + dx].type <= 1);

    
    }

    bool Stacker::fit(int x, int y) {
        
        if ((x < 0) | (x >= loc["board"]["width"]) | (y < 0) | (y >= loc["board"]["height"])) {
            return false;
        }
        return (board[y][x].type <= 1);
    
    }

    void Stacker::spawn() {
        
        if (active) return;
        active = true;
        cout << "yay" << endl;
        
        if (true) {

            tetro = bag.next();
            //set sizes and presets

            tetro.move(loc["board"]["xi"], loc["board"]["yi"]);
        }
    }

    int Stacker::calcdist(MinoSet piece, int dir, bool store) {
            
        //messy ahh implementation maybe clean up later

        int final = 0;
        int dx = 0; int dy = 0;
        dir %= 4;
        if (dir == 0) {
            dy = 271000;
        } else if (dir == 1) {
            dx = 271000;
        } else if (dir == 2) {
            dy = -271000;
        } else if (dir == 3) {
            dx = -271000;
        }
        
        int v = dx+dy;
        for (int i = 0; abs(i) <= abs(v); i += v/abs(v)) {
            if (dx != 0) {
                if (!fit(piece, i, 0)) {
                    break;
                }
            } else {
                if (!fit(piece, 0, i)) {
                    break;
                }
            }
            final = i;
        }


        if (store) {
            dist[dir] = final;    
        }
        return final;

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


            t = control.next();
        }
    }
    
    void Stacker::hold() {
        tetro.reset();
        tetro.move(loc["board"]["xi"], loc["board"]["yi"]);
        if (held.minos[0].x == 271000) {
            held = tetro;
            active = false;
        } else {
            swap(held, tetro);
            tetro.reset();
        }
        tetro.reset();
        tetro.move(loc["board"]["xi"], loc["board"]["yi"]);
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
        if (fit(tetro, 0, 0, v)) {
            tetro.move(0, 0, v);
            return;
        }
        
        int table = 0;
        if (tetro.type-10 == 0) table = 1; //use special table for i pieces

        //D["kicks"][loc["kicks"]]

        for (int i = 0; i < D["kicks"][loc["kicks"]][table].size(); i++) {

            tetro.rotation %= 4;

            vector<int> cur = D["kicks"][loc["kicks"]][table][tetro.rotation%4][i];

            vector<int> fin = D["kicks"][loc["kicks"]][table][(tetro.rotation+v)%4][i];

            vector<int> dif = {cur[0] - fin[0], cur[1] - fin[1]};

            if (fit(tetro, dif[0], dif[1], v)) {
                tetro.move(dif[0], dif[1], v);
                return;
            }
        }
        
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

        for (int i = 0; i < 4; i++) {
            calcdist(tetro, i, true);
        }

        for (int i = 0; i < tetro.minos.size(); i++) {
            board[tetro.minos[i].y][tetro.minos[i].x] = tetro.minos[i];
        }

        active = false;

        clear();
    }

    int Stacker::softdrop(int v) {
        int final = 0;
        for (int i = 0; abs(i) <= abs(v); i += v/abs(v)) {
            if (!fit(tetro, 0, i)) {
                break;
            }
            final = i;
        }
        tetro.move(0, final);
        return final;
    }

    void Stacker::clear() { //call this whenever the board is modified
        int final = 0;
        bool ispc = true;

        vector<int> clr(0);


        for (int i = 0; i < loc["board"]["height"]; i++) {
            bool rowfull = true;
            for (int j = 0; j < loc["board"]["width"]; j++) {
                if (fit(j, i)) {
                    rowfull = false;
                    ispc = false;
                    break;
                }
            }
            if (rowfull) {
                clr.push_back(i);
                for (int j = 0; j < loc["board"]["width"]; j++) {  //remove the blocks
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
                itr++;
            }
            itr++;
        }

        while (itr < loc["board"]["height"]) {
            swap(board[itr], board[itr-clr.size()]);
            itr++;
        }

        int spin = 0;
        if (dist[0] + dist[1] + dist[2] + dist[3] == 0) {
            spin = 2;
            //immobile spin rule
        }

        //note: maybe can implement 3-corner rule for tsm and neo-tsds?

        int pc = 0;
        if (ispc) {
            pc = 1;
        }

        //implement color clear?

        clears.push_back({(int)clr.size(), tetro.type, spin, pc}); // first slot: # lines cleared, 2nd slot: piece used, 3rd slot: spin, 4th: pc

        //entity will take from clears vec and turn it into atk 

    }

    void Stacker::accept(Force f) { //take in garbage lines to the board (directly injects them, does not make it to garbage queue cuz stacker doesnt manage that)
        //btw does not take into account the accept 8 lines only per piece thing, just does it all

        //NOTE: MAKE SURE F HAS ONLY INTEGER STRENGTH!! ENTITY SHOULD SANITIZE THIS!!!
        for (int i = 0; i < f.fnet.size(); i++) {
            //shift board up
            int disp = f.fnet[i].strength; //convert double to int
            
            for (int i = (int)loc["board"]["height"] - disp - 1; i >= 0; i--) {
                swap(board[i], board[i+disp]);
            }

            for (int i = 0; i < disp; i++) {
                auto g = booltomino(f.fnet[i].holes);
                board[i] = g;
            }

            while (!fit(tetro)) {
                tetro.move(0, 1);
            }

        }

        //also try to not call this unless a piece is placed.
        //this moves the piece up if it is touching the bottom

    }

    void Stacker::draw(int x, int y, int sz) {
        //temporary; should use assets later
        DrawRectangleLines(x, y, (int)loc["board"]["width"]*sz, (int)loc["board"]["height"]*sz, WHITE);
        for (int i = 0; i < loc["board"]["height"]; i++) {
            for (int j = 0; j < loc["board"]["width"]; j++) {

                int ti = (int)loc["board"]["height"] - i - 1;

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

            int dist = softdrop(-271000);

            for (Mino m : tetro.minos) {
                int ti = (int)loc["board"]["height"] - m.y - 1;
                int col = m.type - 10;
                Rectangle source = {(float)col*(float)minoskin1.width/12.0f, 0, (float)(minoskin1.width/12), (float)(minoskin1.height)};
                Rectangle dest = {(float)(x+sz*m.x), (float)(y+sz*ti), (float)sz, (float)sz};
                Vector2 empty = {0, 0};
                DrawTexturePro(minoskin1, source, dest, empty, 0, DARKGRAY);
            }
            
            tetro.move(0, -dist);

            for (Mino m : tetro.minos) {
                int ti = (int)loc["board"]["height"] - m.y - 1;
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

            float my = (float)loc["board"]["height"] - tmy - 1;

            mx += 0.5; my += 0.5;

            DrawRectangle(x + (mx*sz) - sz/8, y + (my*sz) - sz/8, sz/4, sz/4, BLUE);

            //draw shadows

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

        for (int i = 0; i < (int)loc["board"]["preview"]; i++) {
            auto temp = bag.view(i);
            temp.move(loc["board"]["xi"], loc["board"]["yi"]);
            for (Mino m : temp.minos) {
                int col = m.type - 10;
                Rectangle source = {(float)col*(float)minoskin1.width/12.0f, 0, (float)(minoskin1.width/12), (float)(minoskin1.height)};
                Rectangle dest = {(float)(x+(sz*((int)loc["board"]["width"]+m.x-2))), (float)(y + sz*(36-m.y+(4*i))), (float)sz, (float)sz};
                Vector2 empty = {0, 0};
                DrawTexturePro(minoskin1, source, dest, empty, 0, WHITE);
            }
        }



    }

    vector<Mino> Stacker::booltomino(vector<bool> holes) {
        vector<Mino> ans(holes.size());
        for (int i = 0; i < holes.size(); i++) {
            int t = 0;
            if (!holes[i]) {
                t = 18;
            }
            Mino m(i, 0, t);
            ans[i] = m;
        }
        return ans;
    }

    vector<int> Stacker::action() {
        
        if (clears.empty()) {
            return {};
        }

        auto ans = clears.front();
        clears.pop_front();
        return ans;

    }
    

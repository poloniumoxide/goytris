#include "entity.h"

Entity::Entity(string preset) : atkbar(0, 0), defbar(0, 0) {
    
    name = preset;
    auto loc_ = D["entities"][name];
    loc = loc_;
    stack = Stacker(loc);
    
    tick = 0;

    buildatktable(D["attacks"][loc["atktable"]]);

    speed = loc["speed"];
    maxspeedbar = loc["maxspeedbar"];
    speedbar = loc["speedbar"];
    hp = loc["hp"];
    maxhp = loc["maxhp"];

}

void Entity::buildatktable(json loc) {
    vector<int> v1(3);
    vector<vector<int>> v2(3, v1);
    vector<vector<vector<int>>> v3(7, v2);
    atktable = vector<vector<vector<vector<int>>>>(7, v3);
    //loc : D["attacks"]["default"]
    for (int i = 0; i < 7; i++) { //lines
        for (int j = 0; j < 7; j++) { //piece
            for (int k = 0; k < 3; k++) { //spin
                for (int l = 0; l < 3; l++) { //pc
                    int ans = loc["base"][k][i];
                    ans += (int)loc["pc"][l];
                    atktable[i][j][k][l] = ans;
                }
            }
        }
    }
}

void Entity::run() {
    sentstack();
    stack.run();
    draw();
    sendstack();
    tick++;
}

void Entity::sentstack() {
    
    /*
    if (tick % 60 == 0) {
        Force f(1, 0, {false, false, false, false, false, false, true, false, false, false});
        stack.accept(f);
    }*/

    stack.accept(defbar);
    defbar.clear();

}

void Entity::sendstack() { //process clears from stack
    vector<int> clear = stack.action();
    while (clear.size() != 0) { //indicates that there are still stuff in stack's actions
        //apply attack table, artifacts, cards and other stuff come later

        //cout << "start" << endl;
        //determine entropy?

        uniform_int_distribution<int> coldist(0, 9);
        
        /*
        cout << clear.size() << clear[0] << " " << clear[1] << " " << clear[2] << " " << clear[3] << " " <<endl;
        cout << atktable[clear[0]][clear[1]][clear[2]][clear[3]] << endl;
        cout << coldist(rngesus) << endl;
        */

        Force f(atktable[clear[0]][clear[1]][clear[2]][clear[3]], 0, Force::genholes(coldist(rngesus), 10));

        //cout << "end" << endl;

        atkbar.merge(f);

        clear = stack.action();

        
    }
}

void Entity::draw() {
    stack.draw(300, -500, 32);
}

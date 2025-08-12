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
    cout << "nick gurr" << endl;

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
                    cout << "nick gurr2" << endl;
                    ans += (int)loc["pc"][l];
                    cout << "nick gurr3" << endl;
                    atktable[i][j][k][l] = ans;
                    cout << "nick gurr4" << endl;
                }
            }
        }
    }
    cout << "nick gurr!" << endl;
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

void Entity::sendstack() { //process clears
    vector<int> clear = stack.action();
    while (clear.size() != 0) {
        //apply attack table, atk stats, relics, whatevuh

        vector<int> atktable = {0, 1, 2, 4};

        Force f(atktable[clear[0]], 0, {false, false, false, false, false, false, true, false, false, false});

        atkbar.merge(f);

        clear = stack.action();
    }
}

void Entity::draw() {
    stack.draw(300, -500, 32);
}

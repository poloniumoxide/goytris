#include "entity.h"

Entity::Entity(string preset) : atkbar(0, 0), defbar(0, 0) {
    
    name = preset;
    auto loc_ = D["entities"][name];
    loc = loc_;
    stack = Stacker(loc);

    buildatktable(D["attacks"][loc["atktable"]]);

    speed = loc["speed"];
    maxspeedbar = loc["maxspeedbar"];
    speedbar = loc["speedbar"];
    hp = loc["hp"];
    maxhp = loc["maxhp"];
    turns = 0;

    for (int i = 0; i < loc["deck"].size(); i++) {
        deck.push_back(Card(loc["deck"][i]));
    }

    //initialize string to function


    strtofunc["sevenbag"] = bind(&Entity::sevenbag, this, placeholders::_1, placeholders::_2);

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

    
    drawstack(300, -500, 32);

    if (turns <= 0) {
        return;
    }

    sentstack();

    if (stack.run()) {
        turns--;
    }

    if (turns <= 0) {
        unplay(last);
    }

    sendstack();

}

void Entity::tick() {
    speedbar += speed;
}

bool Entity::canturn() {
    return (speedbar >= maxspeedbar);
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

void Entity::selectcard(int index) {
    last = hand[index];
    play(hand[index]);
}

void Entity::startturn() {
    //put hand to discard; draw a new hand from draw pile
    for (int i = 0; i < hand.size(); i++) {
        discard.push_back(hand[i]);
    }
    hand.clear();

    int drawn = 0;

    for (int i = 0; i < handsize; i++) {
        if (draw.size() == 0) break;
        hand.push_back(draw[draw.size() - 1]);
        draw.pop_back();
        drawn++;
    }

    if (draw.size() == 0) {
        shuffle(discard.begin(), discard.end(), rngesus);
        for (int i = 0; i < discard.size(); i++) {
            draw.push_back(discard[i]);
        }
        discard.clear();
    }

    for (int i = 0; i < min(handsize - drawn, (int)draw.size()); i++) {
        hand.push_back(draw[draw.size() - 1]);
        draw.pop_back();
    }

    //note: theres a chance drawn < handsize

}

void Entity::reset() {
    //resets to a state at the start of combat
    hand.clear();
    discard.clear();
    draw.clear();
    for (int i = 0; i < deck.size(); i++) {
        draw.push_back(deck[i]);   
    }
    exhaust.clear();
    turns = 0;
    speedbar = loc["speedbar"];
    stack = Stacker(loc);
}

void Entity::drawstack(int x, int y, int sz) { //draws the stack
    stack.draw(x, y, sz);
}

void Entity::drawhand(int x, int y, int sz) {
    //draws the hand of cards to the screen. it doesnt actually draw cards from the draw pile
}

void Entity::drawgoober(int x, int y, int sz) {
    //draws the goobericon
}

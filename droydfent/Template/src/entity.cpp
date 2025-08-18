#include "entity.h"

Entity::Entity(string preset) : atkbar(0, 0), defbar(0, 0) {
    
    name = preset;
    auto loc_ = D["entities"][name];
    loc = loc_;

    if (loc["control"] != "human") {
        stack = Facker(loc);
        bot = true;
    } else {
        stack = Stacker(loc); 
        bot = false;
    }
    

    buildatktable(D["attacks"][loc["atktable"]]);

    speed = loc["speed"];
    maxspeedbar = loc["maxspeedbar"];
    speedbar = loc["speedbar"];
    hp = loc["hp"];
    maxhp = loc["maxhp"];
    turns = 0;
    drawsperturn = loc["drawsperturn"];
    handsize = loc["handsize"];

    for (int i = 0; i < loc["deck"].size(); i++) {
        deck.push_back(Card(loc["deck"][i]));
    }

    for (int i = 0; i < deck.size(); i++) {
        draw.push_back(deck[i]);   
    }

    goober = LoadTexture((string(GetApplicationDirectory()).substr(0, string(GetApplicationDirectory()).size() - 4) + "assets/entities/" + name + ".png").c_str());

    //initialize string to function


    //strtofunc["sevenbag"] = bind(&Entity::sevenbag, this, placeholders::_1, placeholders::_2);
    //cout << "INIT" << endl;

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

    if (!bot) {
        drawstack(300, 800, 32);    
    }
    
    if (turns <= 0) {
        return;
    }

    sentstack();

    if (stack.run()) {
        turns--;
        if (bot) turns = 0;
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
        //determine entropy?

        uniform_int_distribution<int> coldist(0, 9);

        Force f(atktable[clear[0]][clear[1]][clear[2]][clear[3]], 0, Force::genholes(coldist(rngesus), 10));

        atkbar.merge(f);

        clear = stack.action();

        
    }
}

void Entity::selectcard(int index) {
    target = hand[index].target;
    last = hand[index];
    play(hand[index]);
}

void Entity::startturn() {
    //put hand to discard; draw a new hand from draw pile
    for (int i = 0; i < hand.size(); i++) {
        discard.push_back(hand[i]);
    }
    hand.clear();

    drawtohand(drawsperturn);


}

void Entity::drawtohand(int n) {
    
    int drawn = 0;

    n = min(handsize - (int)hand.size(), n);
   

    for (int i = 0; i < n; i++) {
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

    for (int i = 0; i < min(n - drawn, (int)draw.size()); i++) {
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

string Entity::gettarget() {
    return target;
}

void Entity::drawstack(int x, int y, int sz) { //draws the stack
    stack.draw(x, y, sz);
    drawbars(x, y, sz);
}

void Entity::drawhand(int x, int y, int sz, int selected) {
    //draws the hand of cards to the screen. it doesnt actually draw cards from the draw pile
    for (int i = 0; i < hand.size(); i++) {
        bool highlight = false;
        if (selected == i) {
            highlight = true;
        }
        hand[i].draw(x+100*i, y, sz, highlight);
    }
}

void Entity::drawgoober(int x, int y, int sz, bool selected) {
    //draws the goobericon
    Rectangle source = {0, 0, (float)(goober.width), (float)(goober.height)};
    Rectangle dest = {(float)x, (float)y, (float)(goober.width), (float)(goober.height)};
    Vector2 empty = {0, 0};

    if (selected) {
        DrawTexturePro(goober, source, dest, empty, 0, RED);
    } else {
        DrawTexturePro(goober, source, dest, empty, 0, WHITE);
    }

    

    /*
    if (selected) {
        DrawTexturePro(texture, source, dest, empty, 0, RED);
    } else {
        DrawTexturePro(texture, source, dest, empty, 0, WHITE);
    }*/

}

void Entity::drawbars(int x, int y, int sz){
    //x, y represent bottom left
    float k = defbar.getstrength();
    
    DrawRectangle(x-sz, y-k*sz, sz, k*sz, RED);

    k = atkbar.getstrength();

    DrawRectangle(x+sz*10, y-k*sz, sz, k*sz, RED);

}

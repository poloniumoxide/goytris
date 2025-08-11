#include "entity.h"

Entity::Entity(string preset) : atkbar(0, 0), defbar(0, 0) {
    
    name = preset;
    auto loc_ = D["entities"][name];
    loc = loc_;
    stack = Stacker(loc);
    tick = 0;

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

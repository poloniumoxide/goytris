#include "entity.h"

Entity::Entity() : atkbar(0, 0), defbar(0, 0) {
    stack = Stacker();
    tick = 0;
}

void Entity::run() {
    sent();
    stack.run();
    draw();
    send();
    tick++;
}

void Entity::sent() {
    if (tick % 60 == 0) {
        Force f(1, 0, {false, false, false, false, false, false, false, false, false, true});
        stack.accept(f);
    }
}

void Entity::send() {

}

void Entity::draw() {
    stack.draw(300, -500, 32);
}

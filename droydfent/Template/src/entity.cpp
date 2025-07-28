#include "entity.h"

Entity::Entity() : atkbar(0, 0), defbar(0, 0) {
    stack = Stacker();
}

void Entity::run() {
    sent();
    stack.run();
    send();
}

void Entity::sent() {

}

void Entity::send() {

}

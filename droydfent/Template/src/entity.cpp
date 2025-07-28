#include "entity.h"

using namespace std;

Entity::Entity() : atkbar(0, 0), defbar(0, 0) {

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

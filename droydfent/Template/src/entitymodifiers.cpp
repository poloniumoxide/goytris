#include "entity.h"

void Entity::play(Card c) {
    strtofunc[c.name](0, Force());
}

void Entity::unplay(Card c) {
    strtofunc[c.name](1, Force());
}


void Entity::addturns(int add) {
    turns += add;
}

Force Entity::sevenbag(int type, Force f) {
    if (type == 0) {
        addturns(7);
    } else if (type == 1) {

    } else if (type == 2) {

    } else if (type == 3) {

    }

    return Force();
}
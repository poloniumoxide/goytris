#include "entity.h"

void Entity::play(Card c) {
    strtofunc[c.name]();
}

void Entity::unplay(Card c) {
    strtofunc[c.unname]();
}


void Entity::addturns(int turns) {
    turns += 7;
}

void Entity::sevenbag() {
    addturns(7);
}

void Entity::unsevenbag() {
    //do nothing tho
}
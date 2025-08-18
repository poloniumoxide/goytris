#include "entity.h"

void Entity::play(Card c) {
    strtofunc(c.name, 0, Force());
    //sevenbag(0, Force());
    //map literally does not work; strtofunc[c.name](0, Force()); runs it in like a different object (static?) or something
    
}

void Entity::strtofunc(string card, int type, Force f) {
    if (card == "sevenbag") {
        sevenbag(type, f);
    } else if (card == "fourteenbag") {

    }
}

void Entity::unplay(Card c) {
    strtofunc(c.name, 1, Force());
}


void Entity::addturns(int add) {
    turns += add;
}

void Entity::speedcost(int spd) {
    speedbar -= spd;
    speedbar = max(speedbar, 0);
}

Force Entity::sevenbag(int type, Force f) {
    if (type == 0) {
        addturns(7);
        speedcost(10000);
    } else if (type == 1) {

    } else if (type == 2) {

    } else if (type == 3) {

    }

    return Force();
}
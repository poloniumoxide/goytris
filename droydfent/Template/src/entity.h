#ifndef ENTITY_H
#define ENTITY_H

#include "stacker.h"
#include "force.h"

#include <vector>

using namespace std;

class Entity {
public:
    int hp;
    vector<int> attack_table;
    Stacker stack;
    Force atkbar;
    Force defbar;

    Entity();

    void run();
    void send();
    void sent();
};

#endif // MY_HEADER_H
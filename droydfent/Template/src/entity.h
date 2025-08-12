#ifndef ENTITY_H
#define ENTITY_H

#include "stacker.h"
#include "force.h"
#include "card.h"

#include <vector>

using namespace std;

class Entity {
public:

    int tick;
    Stacker stack;
    Force atkbar;
    Force defbar;
    string name;
    json loc;

    int speed;
    int maxspeedbar;
    int speedbar;
    int hp;
    int maxhp;

    vector<vector<vector<vector<int>>>> atktable;
    
    float entropy;

    vector<Card> hand;

    Entity(string = "default");

    void run();
    void sendstack();
    void sentstack();
    void draw();
    void buildatktable(json);
};

#endif // MY_HEADER_H
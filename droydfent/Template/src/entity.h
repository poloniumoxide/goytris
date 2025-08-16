#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>
#include <functional>
#include <string>
#include <random>
#include <algorithm>

#include "stacker.h"
#include "force.h"
#include "card.h"
#include "global.h"

using namespace std;

class Entity {
public:

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

    vector<function<Force(Force)>> atkfuncs;
    
    float entropy;

    vector<Card> deck;
    vector<Card> hand;
    vector<Card> discard;
    vector<Card> draw;
    vector<Card> exhaust;

    int handsize;

    int turns;

    Card last;

    Entity(string = "default");

    void run();
    void reset();
    void sendstack();
    void sentstack();
    
    void tick();
    bool canturn();

    void selectcard(int);

    void drawstack(int, int, int);
    void drawhand(int, int, int);
    void drawgoober(int, int, int);

    void buildatktable(json);

    void startturn(); //used to cycle hand

    //card based fundamentals

    map<string, function<Force(int, Force)>> strtofunc;

    void play(Card);
    void unplay(Card);

    void addturns(int = 7);

    //cards

    Force sevenbag(int = 0, Force = Force());


};

#endif
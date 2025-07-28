#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "jsonparser.h"

#include <deque>
#include <vector>
#include <map>
#include <raylib.h>
#include <raymath.h>

using namespace std;

class Controller {
public:

    deque<int> inputs;
    vector<int> held;
    vector<int> order;
    map<string, int> ste;
    int kleft, kright, kcw, kccw, k180, khold, ksd, khd;

    Controller();

    void run();
    void checkheld(int = 0, int = 0);
    int next();

};

#endif
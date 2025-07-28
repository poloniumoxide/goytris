#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "defaultdata.h"

#include <deque>
#include <vector>

using namespace std;

class Controller {
public:

    deque<int> inputs;
    vector<int> held;
    vector<int> order;

    Controller();

    void run();
    void checkheld(int = 0, int = 0);
    int next();

};

#endif
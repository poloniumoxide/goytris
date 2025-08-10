#ifndef MENU_H
#define MENU_H

#include <vector>
#include <iostream>
#include <string>
#include <map>

#include "global.h"
#include "jsonparser.h"
#include "button.h"

using namespace std;

class Menu {
public:

    string name;

    map<string, Button> buttons;
    string current;

    Menu(string);

    void run();

    inline const static vector<int> possible_keys = {KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_Z, KEY_X};

};

#endif
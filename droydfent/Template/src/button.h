#ifndef BUTTON_H
#define BUTTON_H

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <raylib.h>
#include <stdexcept>
#include "jsonparser.h"

#define MAGIC_ENUM_RANGE_MIN -256
#define MAGIC_ENUM_RANGE_MAX 512

#include "magic_enum.hpp"

using namespace std;

class Button {
public:

    string name;
    string menuname;
	map<int, string> neighbors;
	int x, y;
	Texture2D buttonskin;

    Button(string = "main", string = "start"); //enum(key) to action (button name, gamestate name)
    Button(int, int); //used to make cyclic menus
    string interact(int);
    void draw(bool = false);
    void run();

};

#endif
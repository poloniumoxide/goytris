#ifndef CARD_H
#define CARD_H

#include <vector>
#include <iostream>
#include <functional>
#include <map>
#include "raylib.h"

using namespace std;

class Card {
public:

	string name;
	string unname;

	Texture2D texture;

    Card(string = "sevenbag");

    void draw();

};

#endif
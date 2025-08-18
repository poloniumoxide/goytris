#ifndef CARD_H
#define CARD_H

#include <vector>
#include <iostream>
#include <functional>
#include <map>
#include "raylib.h"
#include "jsonparser.h"

using namespace std;

class Card {
public:

	string name;
	string unname;

	string target;
	string type;

	Texture2D texture;

    Card(string = "sevenbag");

    void draw(int, int, int, bool = false);

};

#endif
#ifndef CARD_H
#define CARD_H

#include <vector>
#include <iostream>
#include <functional>

#include "bag.h"

using namespace std;

class Card {
public:

	function<void()> entityf;
	function<void()> entityr;

	string name;

    Card(string);

};

#endif
#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include <iostream>

#include "entity.h"
#include "menu.h"

using namespace std;

class Stage {
public:

	string name;

	string stagestate;

	vector<Entity> players;
	vector<Entity> enemies; 

	Entity* focus;
	string targetting;

	Menu selector;

	Stage(string = "vsgoy", vector<Entity> = {Entity("default")});

	void run();
	void playerstarthand();
	vector<vector<int>> entitypositions(bool, int);

};

#endif
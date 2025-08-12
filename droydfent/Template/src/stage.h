#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include <iostream>

#include "entity.h"

using namespace std;

class Stage {
public:

	string name;

	string stagestate;

	Entity player;
	vector<Entity> enemies; 


	Stage(string = "vsgoy", Entity = Entity("default"));

	void run();

};

#endif
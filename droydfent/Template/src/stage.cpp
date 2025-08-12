#include "stage.h"

    Stage::Stage(string preset, Entity player_) {
    	name = preset;
    	player = player_;

    	auto loc = D["stages"][name];

    	for (int i = 0; i < loc["enemies"].size(); i++) {
    		enemies.push_back(Entity(loc["enemies"][i]));
    	}

    }

    void Stage::run() {
    	
    	player.run();

    	for (int i = 0; i < enemies.size(); i++) {
    		enemies[i].run();
    	}


    }

#include "stage.h"

    Stage::Stage(string preset, vector<Entity> player_) {
    	name = preset;
    	players = player_;

    	auto loc = D["stages"][name];

    	for (int i = 0; i < loc["enemies"].size(); i++) {
    		enemies.push_back(Entity(loc["enemies"][i]));
    	}

    	stagestate = "neutral";

    }

    void Stage::run() {

    	if (stagestate == "neutral") {
    		
	    	for (int i = 0; i < players.size(); i++) {
    			players[i].tick();
    		}

	    	for (int i = 0; i < enemies.size(); i++) {
    			enemies[i].tick();
    		}

    		for (int i = 0; i < players.size(); i++) {
    			if (players[i].canturn()) {
    				focus = players[i];
    				playerstarthand();
    			}
    		}

	    	for (int i = 0; i < enemies.size(); i++) {
    			if (enemies[i].canturn()) {
    				focus = enemies[i];
    				stagestate = "enemystack";
    				focus.startturn();
    			}
    		}

    	} else if (stagestate == "playerselecthand") {

    		for (int i = 0; i < focus.hand.size(); i++) {
    			focus.hand[i].draw();
    		}
    		selector.run();

    		if (selector.signal) {
    			focus.selectcard(stoi(selector.current));
    		}

    	} else if (stagestate == "playerselectenemy") {

    	} else if (stagestate == "playerstack") {

    	} else if (stagestate == "enemystack") {

    	}

    }

    void Stage::playerstarthand() {
    	stagestate = "playerselecthand";
    	focus.startturn(); // cycle hand
 		selector = Menu(focus.hand.size());
    }

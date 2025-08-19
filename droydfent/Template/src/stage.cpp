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


    	//draw the goobers in the background

    	auto v = entitypositions(true, players.size());
    	for (int i = 0; i < v.size(); i++) {
    		bool highlight = false;
    		
    		if ((targetting == "1player") && (stoi(selector.current) == i) && (stagestate == "playerselectenemy")) {
    			highlight = true;
    		}

    		players[i].drawgoober(v[i][0], v[i][1], 1, highlight);
    	}

    	v = entitypositions(false, enemies.size());
    	for (int i = 0; i < v.size(); i++) {
    		bool highlight = false;
    		
    		if ((targetting == "1enemy") && (stoi(selector.current) == i) && (stagestate == "playerselectenemy")) {
    			highlight = true;
    		}

    		enemies[i].drawgoober(v[i][0], v[i][1], 1, highlight);
    	}

    	if (stagestate == "neutral") {
    		
	    	for (int i = 0; i < players.size(); i++) {
    			players[i].tick();
    		}

	    	for (int i = 0; i < enemies.size(); i++) {
    			enemies[i].tick();
    		}

    		for (int i = 0; i < players.size(); i++) {
    			if (players[i].canturn()) {
    				focus = &players[i];
    				stagestate = "playerselecthand";
    				focus->startturn(); // cycle hand
 					selector = Menu(focus->hand.size());
    				return;
    			}
    		}

	    	for (int i = 0; i < enemies.size(); i++) {
    			if (enemies[i].canturn()) {
    				focus = &enemies[i];
    				stagestate = "enemystack";
    				focus->startturn();

    				//temp just always target p1

    				focus->selectcard(0);

    				focus->targets.clear();
    				focus->targets = {&players[0]};

    				return;
    			}
    		}


    	} else if (stagestate == "playerselecthand") {

    		focus->drawhand(100, 500, 100, stoi(selector.current));

    		selector.run();

    		if (selector.signal) {
    			focus->selectcard(stoi(selector.current));
    			
    			targetting = focus->gettarget();
    			
    			if (targetting == "1enemy") {
    				selector = Menu(enemies.size());
    			} else if (targetting == "1player") {
    				selector = Menu(players.size());
    			} else { //all allies, all enemies and all allies+enemies dont need menu
    				stagestate = "playerstack";
    				return;
    			}

    			stagestate = "playerselectenemy";

    		}

    	} else if (stagestate == "playerselectenemy") {

    		selector.run();

    		if (selector.signal) {
    			focus->targets.clear();
    			if (targetting == "1enemy") {
    				//act on the card: focus->action(&enemies[i]);
    				//for (auto p : focus->targets) {
    				//	delete p;
    				//}

    				focus->targets = {&enemies[stoi(selector.current)]};
    			} else if (targetting == "1player") {
    				//for (auto p : focus->targets) {
    				//	delete p;
    				//}
    				focus->targets = {&players[stoi(selector.current)]};
    			}//add other things (aoe)
    			stagestate = "playerstack";
    		}

    	} else if (stagestate == "playerstack") {

    		if (focus->turns <= 0) {
    			stagestate = "neutral";
    		}

    		cout << "playerrun" << endl;

    		focus->run();

    		cout << "playerran" << endl;

    	} else if (stagestate == "enemystack") {


    		if (focus->turns <= 0) {
    			stagestate = "neutral";
    		}

    		cout << "enemyrun" << endl;

    		focus->run();

    		cout << "enemyran" << endl;

    	}

    }

    void Stage::playerstarthand() {
    	stagestate = "playerselecthand";
    	focus->startturn(); // cycle hand
 		selector = Menu(focus->hand.size());
    }

    vector<vector<int>> Stage::entitypositions(bool side, int n) {

    	//side == true for player side
    	vector<vector<int>> ans;

    	vector<vector<int>> base = {{800, 500}, {600, 600}, {650, 350}, {1200, 500}, {1400, 600}, {1350, 350}};

    	for (int i = 0; i < n; i++) {
    		int offset = i/3;  offset *= 200;
    		
    		if (side) {
    			offset = -offset;
    		}

    		int side2 = 0; 

    		if (!side) {
    			side2 = 3;
    		}
    		
    		ans.push_back({base[i%3 + side2][0] + offset, base[i%3 + side2][1]});
    	}
    	
    	return ans;

    }

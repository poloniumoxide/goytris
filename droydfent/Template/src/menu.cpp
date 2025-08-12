#include "menu.h"

    Menu::Menu(string preset) {
    	
    	name = preset;

    	auto loc = D["menu"][name];

    	current = " ";

    	for (auto itr = loc.begin(); itr != loc.end(); itr++) {

    		if (current == " ") {
    			current = itr.key();
    		}

			buttons.insert({itr.key(), Button(preset, itr.key())});

		}

    }

    void Menu::run() {

        if (!(gamestate == name)) {
        	return;
        }

        //get inputs

        for (int i = 0; i < possible_keys.size(); i++) {
        	if (IsKeyPressed(possible_keys[i])) {
        		string temp = buttons[current].interact(possible_keys[i]);
        		if (temp[0] == 'M') {
        			gamestate = temp.substr(1);
        		} else if (temp[0] == 'B') {
        			current = temp.substr(1);
        		} else {

        		}
        		break;
        	}
        }

        
        for (auto itr = buttons.begin(); itr != buttons.end(); itr++) {
        	if (itr->first == current) {
        		itr->second.draw(true);
        	}
        	itr->second.draw(false);
        }

    }


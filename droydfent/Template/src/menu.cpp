#include "menu.h"

    Menu::Menu(string preset) {
    	
    	name = preset;
    	D["menu"]["preset"];

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
        		current = buttons[current].interact(possible_keys[i]);
        		break;
        	}
        }

        
        for (auto itr = buttons.begin(); itr != buttons.end(); itr++) {
        	itr->second.run();
        }

    }


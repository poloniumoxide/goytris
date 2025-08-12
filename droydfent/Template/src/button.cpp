#include "button.h"


	Button::Button(string menu, string preset) {
		
		name = preset;
		menuname = menu;
		
		auto loc = D["menu"][menuname][name];

		for (auto itr = loc["neighbors"].begin(); itr != loc["neighbors"].end(); itr++) {
			
			auto ekey = magic_enum::enum_cast<KeyboardKey>(itr.key());
			if (!ekey.has_value()){
				throw runtime_error(itr.key());
			}
			neighbors.insert({(int)ekey.value(), itr.value()});
		
		}

		x = loc["x"];
		y = loc["y"];

		buttonskin = LoadTexture((string(GetApplicationDirectory()).substr(0, string(GetApplicationDirectory()).size() - 4) + "assets/" + menuname + "_menu/" + name + ".png").c_str());
		
	}

	string Button::interact(int key) {
		if (neighbors.find(key) == neighbors.end()) {
			return " ";
		}
		return neighbors[key];
	}

	void Button::run() {
		draw();
	}

	void Button::draw(bool selected) {
		cout << selected << endl;
		if (!selected) {
			DrawTexture(buttonskin, x, y, WHITE);	
		} else {
			DrawTexture(buttonskin, x, y, RED);
		}
		
	}


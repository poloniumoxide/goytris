#include "button.h"


	Button::Button(string menu, string preset) {
		
		name = preset;
		menuname = menu;
		
		auto loc = D["menu"][menuname][name];

		for (auto itr = loc.begin(); itr != loc.end(); itr++) {
			
			auto ekey = magic_enum::enum_cast<KeyboardKey>(itr.key());
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

	void Button::draw() {
		DrawTexture(buttonskin, x, y, WHITE);
	}


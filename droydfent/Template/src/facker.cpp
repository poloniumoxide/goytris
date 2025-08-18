#include "facker.h"

    Facker::Facker(json loc_) {
        loc = loc_;
        maxheight = loc["board"]["yi"];
    	height = 0;

    	name = loc["control"];

    	//cout << "negroni" << endl; 

    	//strtofunc["littlegoy"] = bind(&Facker::littlegoy, this);
    }


    void Facker::draw(int x, int y, int sz) {
    	return;
    }

    bool Facker::run() {
    	//strtofunc(name);
    	cout << "ran" << endl;
    	return true;
    }

    void Facker::strtofunc(string func) {
    	if (func == "littlegoy") {
    		littlegoy();
    	}
    }

    void Facker::littlegoy() {
    	clears.push_back({4, 10, 0, 0});
    	height -= 4;
    	height = max(0, height);
    }

    void Facker::accept(Force f) {
    	
    	for (int i = 0; i < f.fnet.size(); i++) {
            //shift board up
            int disp = f.fnet[i].strength; //convert double to int
            
            height += disp;
        }

    }

#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <filesystem>


#include "jsonparser.h"
#include "entity.h"
#include "menu.h"

using namespace std;
using json = nlohmann::json;

double TFPS = (double)D["game"]["fps"];
double FRAME = (1.0F)/TFPS;


int main()
{
	InitWindow(1000, 1000, "stacka");


	//SetTargetFPS(60);
	
    string workingdir = GetApplicationDirectory();

    for (int i = 0; i < 4; i++) {
    	workingdir.pop_back();
    }

    ChangeDirectory(workingdir.c_str());

	Entity thegoy = Entity("default");
	thegoy.reset();
	thegoy.startturn();
	thegoy.selectcard(0);

	Menu mainmenu("main");

	while (!WindowShouldClose()) {
        	BeginDrawing();
            ClearBackground(BLACK);
            //thelooper
            
            mainmenu.run();
            if (gamestate == "goy") {
            	thegoy.run();
            }
    
        	EndDrawing();
        	float temp = GetFrameTime();
        	//cout << temp << endl;
        	if (temp < FRAME){
        		WaitTime(FRAME-temp);
        	}

        	if (gamestate == "quit") {
        		break;
        	}
    	}
   	 CloseWindow();
   	 return 0;
}

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

using namespace std;
using json = nlohmann::json;

double TFPS = (double)D["game"]["fps"];
double FRAME = (1.0F)/TFPS;


int main()
{
	InitWindow(1000, 1000, "stacka");

	ChangeDirectory(GetApplicationDirectory());

	cout << GetWorkingDirectory() << endl;

	//SetTargetFPS(60);
	
    //GetWorkingDirectory();
	
/*
	cout << "POOm" << endl;
	ifstream temp("/Users/ericyang/Desktop/goytris/droydfent/Template/src/defaultdata.json");

	if (!temp.is_open()) {
		cout << "NIGGER" << endl;
	}
	

	cout << "yo" << temp.rdbuf() << endl;

	//json E{json::parse(temp)};

*/	
	Entity thegoy = Entity();

	while (!WindowShouldClose()) {
        	BeginDrawing();
            	ClearBackground(BLACK);
            	//thelooper
            	thegoy.run();
    
        	EndDrawing();
        	float temp = GetFrameTime();
        	if (temp < FRAME){
        		WaitTime(FRAME-temp);
        	}
    	}
   	 CloseWindow();
   	 return 0;
}

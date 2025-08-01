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

int main()
{
	InitWindow(1000, 1000, "george droyd's fentanyl");
	cout << "v1" << endl;

	ChangeDirectory(GetApplicationDirectory());

	cout << GetWorkingDirectory() << endl;
	
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
	cout << "v2" << endl;

	while (!WindowShouldClose()) {
        	BeginDrawing();
            	ClearBackground(BLACK);
            	//thelooper
            	thegoy.run();
    
        	EndDrawing();
    	}
   	 CloseWindow();
   	 return 0;
}

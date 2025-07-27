#include <raylib.h>
#include <raymath.h>

#include <vector>

using namespace std;

int main()
{
	InitWindow(400, 224, "george droyd's fentanyl");

	vector<int> vectortest = {0, 1, 2};
	
	while (!WindowShouldClose()) {
        	BeginDrawing();
            	ClearBackground(RAYWHITE);
    
        	EndDrawing();
    	}
   	 CloseWindow();
   	 return 0;
}

#include <raylib.h>
#include <raymath.h>

int main()
{
	InitWindow(400, 224, "george droyd's fentanyl");
	
	while (!WindowShouldClose()) {
        	BeginDrawing();
            	ClearBackground(RAYWHITE);
    
        	EndDrawing();
    	}
   	 CloseWindow();
   	 return 0;
}
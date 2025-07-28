#ifndef DATA_H
#define DATA_H

#include <vector>
#include <raylib.h>
#include <raymath.h>

using namespace std;

vector<int> srskick = {};

vector<int> srsxkick = {};

int xi = 0;
int yi = 0;

int height = 40;
int width = 10;

//handling

int das = 6;
int arr = 1;
int sdf = 1;

//keybinds

int kleft = KEY_LEFT;
int kright = KEY_RIGHT;
int kcw = KEY_UP;
int kccw = KEY_DOWN;
int k180 = KEY_W;
int khold = KEY_E;
int ksd = KEY_Q;
int khd = KEY_SPACE;

vector<vector<vector<int>>> tetrominos = 
	{{{1, 0}, {2, 0}, {3, 0}, {4, 0}},
	{{1, 0}, {1, 1}, {2, 0}, {2, 1}},
	{{0, 0}, {0, 1}, {1, 1}, {2, 1}},
	{{2, 0}, {0, 1}, {1, 1}, {2, 1}},
	{{0, 1}, {1, 1}, {1, 0}, {2, 0}},
	{{0, 0}, {1, 0}, {1, 1}, {2, 1}},
	{{1, 0}, {0, 1}, {1, 1}, {2, 1}}};

int ioljszt = 0;

#endif
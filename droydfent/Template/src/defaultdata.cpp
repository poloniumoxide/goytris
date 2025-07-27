#include <vector>

using namespace std;

vector<int> srskick = {};

vector<int> srsxkick = {};

int xi = 0;
int yi = 0;

int height = 40;
int width = 10;

vector<vector<vector<int>>> tetrominos = 
	{{{1, 0}, {2, 0}, {3, 0}, {4, 0}},
	{{1, 0}, {1, 1}, {2, 0}, {2, 1}},
	{{0, 0}, {0, 1}, {1, 1}, {2, 1}},
	{{2, 0}, {0, 1}, {1, 1}, {2, 1}},
	{{0, 1}, {1, 1}, {1, 0}, {2, 0}},
	{{0, 0}, {1, 0}, {1, 1}, {2, 1}},
	{{1, 0}, {0, 1}, {1, 1}, {2, 1}}};

int ioljszt = 0;

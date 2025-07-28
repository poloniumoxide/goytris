#ifndef FORCE_H
#define FORCE_H

#include <vector>

using namespace std;

class Force {
public:

    vector<vector<int>> f;

    int length;
    int strength;

    Force(int, int);

    void merge(Force);

    void cancel(Force);


};

#endif // MY_HEADER_H
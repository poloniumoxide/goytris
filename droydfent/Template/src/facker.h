#ifndef FACKER_H
#define FACKER_H

#include "stacker.h"

using namespace std;

class Facker : public Stacker {
public:

    Facker(json);

    int maxheight;
    int height;

    string name;

    json loc;

    bool run() override;

    void draw(int = 0, int = 0, int = 0) override;

    void accept(Force) override;

    void strtofunc(string);

    //map<string, function<void()>> strtofunc;

    //ai functions

    void littlegoy();

};

#endif
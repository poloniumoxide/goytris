#ifndef FORCE_H
#define FORCE_H

#include <vector>
#include <deque>

using namespace std;

class Force {
public:

    struct Component {
        double strength;
        double entropy;
        vector<bool> holes; // default: 10 long
        vector<float> attributes; // used in amplifying and cancelling; 4 long
    };

    deque<Component> fnet;

    int length;
    int strength;

    Force(double = 0, double = 0, vector<bool> = {false, false, false, false, false, false, false, false, false, false});

    void merge(Force);
    void cancel(Force);
    void clear();

    double getstrength();

    static vector<bool> genholes(int, int = 10);
    static void compcancel(Component&, Component&);

};

#endif
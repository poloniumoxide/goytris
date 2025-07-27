#include "force.cpp"
#include "stacker.cpp"

#include <vector>

using namespace std;

class Entity {
public:

    int hp;
    vector<int> attack_table;
    Stacker stack;
    Force atkbar;
    Force defbar;

    void run() {
        sent();
        stack.run();
        send();
    }

    void sent() {
        //calculate what sent becomes
        //give it off to stacker
    }

    void send() {
        //take the clears from stacker, add them into attack lines
    }
};
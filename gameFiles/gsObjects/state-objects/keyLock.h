#ifndef dwr_state_keylock
#define dwr_state_keylock
#include "../../instance.h"

class Key : public Instance{
    private:
        std::string lName;
    public:
        Key(double X, double Y, std::string lock);
        Key(double X, double Y, std::string lock, bool perm);
        void collided(Instance* o, double deltaTime);
};

class Lock : public Instance{

};

#endif